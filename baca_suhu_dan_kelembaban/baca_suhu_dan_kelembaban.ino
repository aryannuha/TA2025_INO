// 25 APRIL 2025
// AUTHOR : AMMAR ARYAN NUHA
// PROGRAM AKUISISI DATA SUHU DAN KELEMBABAN UDARA INDOOR DHT22,
// KIRIM KE RIDAM CLOUD A, RIDAM LOCAL A, ALARM, DAN DATALOGGER
// MENGIRIM DATA DALAM FORMAT JSON MELALUI JARINGAN LOKAL DENGAN PROTOKOL UDP
// SENSOR DHT22 DIHUBUNGKAN DENGAN ESP32 PADA PIN GPIO4
// PEMBACAAN RAW DATA DISIMPAN PADA VARIABEL rawTemp DAN rawHumidity
// TERSEDIA FUNGSI KALIBRASI DAN FILTRASI JIKA DIBUTUHKAN
// UNTUK SAAT INI RAW DATA LANGSUNG DIMASUKKAN KE DALAM STRUCT
// MAC ADDRESS T&H INDOOR F4:65:0B:54:9C:74

// ============================================ DEKLARASI LIBRARY YANG DIBUTUHKAN ==========================================================================
#include <DHT.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <AsyncUDP.h>
#include <ArduinoJson.h>
// ============================================ AKHIR DEKLARASI LIBRARY ====================================================================================

// ============================================ DEFINISIKAN PIN DHT22 DAN TIPE DHT =========================================================================
#define DHT_PIN 4
#define DHT_TYPE DHT22
// ============================================ AKHIR DEKLARASI PIN DHT22 ==================================================================================

// =========================== DEKLARASI SSID DAN PASSWORD WIFI, SESUAIKAN DENGAN SSID DAN PASSWORD ANDA ===================================================
const char* ssid = "Workshop 3";
const char* password = "eForacimenyan";
// =========================== AKHIR DEKLARASI SSID DAN PASSWORD WIFI ======================================================================================

// =========================== SETTING JARINGAN LOKAL DENGAN PARAMETER IP STATIC, GATEWAY, SUBNET, PRIMARY DNS, SECONDARY DNS ==============================
// =========================== PASTIKAN IP ADDRESS FORMATNYA SAMA DENGAN NETWORK ADDRESS ROUTER, BEGITU JUGA UNTUK PARAMETER JARINGAN YANG LAIN ============
IPAddress staticIP(192, 168, 0, 231);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(192, 168, 0, 1);
IPAddress dns2(0, 0, 0, 0);
// ========================== AKHIR SETTING JARINGAN LOKAL ===================================================================================================

// ========================== DEKLARASI IP DESTINASI =========================================================================================================
IPAddress destinationIP(192, 168, 0, 237); // RIDAM CLOUD A
IPAddress destinationIP2(192, 168, 0, 238); // RIDAM LOCAL A
IPAddress destinationIP3(192, 168, 0, 239); // ALARM MCS
IPAddress destinationIP4(192, 168, 0, 240); // DATALOGGER MCS
// ========================== AKHIR DEKLARASI IP DESTINASI IP ================================================================================================

// ========================== DEKLARASI VARIABEL UNTUK MENYIMPAN RAW DATA DHT22 ==============================================================================
float rawTemp = 0;
float rawHumidity = 0;
// ========================== AKHIR DEKLARASI VARIABEL RAW DATA DHT22 ========================================================================================

// ========================== DEKLARASI STRUCTURE UNTUK SUHU INDOOR ==========================================================================================
struct struct_data_sensor_suhu {
  String kodeModul;
  int kodeVariabel;
  float data;
  int kodeAlarm;
  String berita;
};
struct_data_sensor_suhu suhuData;
// ========================== AKHIR STRUCTURE SUHU INDOOR ====================================================================================================

// ========================== DEKLARASI STRUCTURE UNTUK KELEMBABAN INDOOR ====================================================================================
struct struct_data_sensor_kelembaban {
  String kodeModul;
  int kodeVariabel;
  float data;
  int kodeAlarm;
  String berita;
};
struct_data_sensor_kelembaban kelembabanData;
// ========================= AKHIR STRUCTURE KELEMBABAN INDOOR ===============================================================================================

// ========================== DEKLARASI VARIABEL KALIBRASI ===================================================================================================
float ySuhu, yKelembaban;
float awal_ukurSuhu, awal_sensorSuhu,
      akhir_ukurSuhu, akhir_sensorSuhu;
float awal_ukurKelembaban, awal_sensorKelembaban,
      akhir_ukurKelembaban, akhir_sensorKelembaban;
float aSuhu, aKelembaban;
float cSuhu, cKelembaban;
// ========================== AKHIR DEKLARASI VARIABEL KALIBRASI =============================================================================================

// ========================== DEKLARASI JUMLAH DATA UNTUK FILTRASI SIMPLE MOVING AVERAGE =====================================================================
#define WINDOW_SIZE 5   
// ========================== AKHIR DEKLARASI JUMLAH DATA UNTUK FILTRASI =====================================================================================

// ========================== DEKLARASI VARIABEL UNTUK MENYIMPAN DATA SEBANYAK WINDOW SIZE ===================================================================
float tempWindow[WINDOW_SIZE];
float humWindow[WINDOW_SIZE];
int bufferIndex = 0;
int count = 0;
float avgTemp, avgHum;
// ========================== AKHIR DEKLARASI VARIABEL UNTUK MENYIMPAN DATA SEBANYAK WINDOW SIZE =============================================================

// ========================= DEKLARASI VARIABEL UNTUK UPDATE SESUAI INTERVAL =================================================================================
unsigned long previousMillis = 0;
const long interval = 1000;
// ========================= AKHIR DEKLARASI VARIABEL UNTUK UPDATE SESUAI INTERVAL ===========================================================================

// ========================= DEKLARASI OBJEK UNTUK MASING-MASING LIBRARY =====================================================================================
DHT dht(DHT_PIN,DHT_TYPE);
WiFiClientSecure espClient;
AsyncUDP udp;
// ========================= AKHIR DEKLARASI OBJEK ===========================================================================================================

void setup() {
  // INISIALISASI SERIAL
  Serial.begin(115200); 
  // ttSerial.begin(TH_BAUD, SERIAL_8N1, RXD2, TXD2);
 
  // INISIALISASI DHT22
  dht.begin();     
  
  // INISIALISASI WIFI
  setup_wifi();   
}

void loop() {
  // DEKLARASI VARIABEL MILLIS SESUAI DENGAN WAKTU millis() SEKARANG
  unsigned long currentMillis = millis();

  // UPDATE PEMBACAAN SESUAI INTERVAL
  if (currentMillis - previousMillis >= interval) {
    // UPDATE WAKTU TERAKHIR PEMBACAAN
    previousMillis = currentMillis; 

    // PANGGIL FUNGSI readDHT()
    readDHT();    

    // PANGGIL FUNGSI proses()
    proses();

    // PANGGIL FUNGSI sendData()
    sendData();

    // PANGGIL FUNGSI displaySerial()
    // displaySerial();
  }
}

