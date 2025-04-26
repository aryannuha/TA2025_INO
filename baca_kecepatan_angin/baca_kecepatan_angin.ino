// 25 APRIL 2025
// AUTHOR : AMMAR ARYAN NUHA
// PROGRAM AKUISISI DATA KECEPATAN ANGIN,
// KIRIM KE RIDAM CLOUD A, RIDAM LOCAL A, ALARM, DAN DATALOGGER
// MENGIRIM DATA DALAM FORMAT JSON MELALUI JARINGAN LOKAL DENGAN PROTOKOL UDP
// SENSOR KECEPATAN ANGIN DIHUBUNGKAN DENGAN ESP32 PADA PIN RX2 DAN TX2 PADA GPIO16 DAN GPIO17
// PEMBACAAN RAW DATA DISIMPAN PADA VARIABEL windspeed
// TERSEDIA FUNGSI KALIBRASI DAN FILTRASI JIKA DIBUTUHKAN
// UNTUK SAAT INI RAW DATA LANGSUNG DIMASUKKAN KE DALAM STRUCT
// MAC ADDRESS KECEPATAN ANGIN F4:65:0B:54:C9:90

// ============================================ DEKLARASI LIBRARY YANG DIBUTUHKAN ==========================================================================
#include <ModbusMaster.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <AsyncUDP.h>
#include <ArduinoJson.h>
// ============================================ AKHIR DEKLARASI LIBRARY =====================================================================================

// =========================== DEKLARASI SSID DAN PASSWORD WIFI, SESUAIKAN DENGAN SSID DAN PASSWORD ANDA ===================================================
const char* ssid = "Workshop 3";
const char* password = "eForacimenyan";
// =========================== AKHIR DEKLARASI SSID DAN PASSWORD WIFI ======================================================================================

// =========================== SETTING JARINGAN LOKAL DENGAN PARAMETER IP STATIC, GATEWAY, SUBNET, PRIMARY DNS, SECONDARY DNS ==============================
// =========================== PASTIKAN IP ADDRESS FORMATNYA SAMA DENGAN NETWORK ADDRESS ROUTER, BEGITU JUGA UNTUK PARAMETER JARINGAN YANG LAIN ============
IPAddress staticIP(192, 168, 0, 234);
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

// ================================================== DEFINISI PIN DAN BAUDRATE ==============================================================================
#define RXD2 16
#define TXD2 17
#define WS_BAUD 4800
// ================================================== AKHIR DEFINISI PIN DAN BAUDRATE ========================================================================

// ================================================== DEKLARASI VARIABEL UNTUK RAWDATA WINDSPEED =============================================================
float windSpeed = 0;
// ================================================== AKHIR DEKLARASI VARIABEL ===============================================================================

// =============================================== STRUTCTURE UNTUK KECEPATAN ANGIN ==========================================================================
struct struct_data_sensor_ws{
  String kodeModul;
  int kodeVariabel;
  float data;
  int kodeAlarm;
  String berita;
};
struct_data_sensor_ws windspeedData;
// =============================================== AKHIR STRUCTURE ===========================================================================================

// ========================== DEKLARASI VARIABEL KALIBRASI ===================================================================================================
float yWind;
float awal_ukurWind, awal_sensorWind,
      akhir_ukurWind, akhir_sensorWind;
float aWind;
float cWind;
// ========================== AKHIR DEKLARASI VARIABEL KALIBRASI =============================================================================================

// ========================== DEKLARASI JUMLAH DATA UNTUK FILTRASI SIMPLE MOVING AVERAGE =====================================================================
#define WINDOW_SIZE 5   
// ========================== AKHIR DEKLARASI JUMLAH DATA UNTUK FILTRASI =====================================================================================

// ========================== DEKLARASI VARIABEL UNTUK MENYIMPAN DATA SEBANYAK WINDOW SIZE ===================================================================
float windWindow[WINDOW_SIZE];
int bufferIndex = 0;
int count = 0;
float avgWind;
// ================================================= AKHIR DEKLARASI VARIABEL UNTUK MENYIMPAN DATA SEBANYAK WINDOW SIZE =====================================

// ========================= DEKLARASI VARIABEL UNTUK UPDATE SESUAI INTERVAL =================================================================================
unsigned long previousMillis = 0;
const long interval = 1000;
// ========================= AKHIR DEKLARASI VARIABEL UNTUK UPDATE SESUAI INTERVAL ===========================================================================

// ========================================== GLOBAL OBJEK MASING-MASING LIBRARY =============================================================================
WiFiClientSecure espClient;
ModbusMaster node; //object node for class ModbusMaster
HardwareSerial wsSerial(2);
AsyncUDP udp;
// ========================================== AKHIR GLOBAL OBJEK =============================================================================================

void setup() {
  // Inisialisasi Serial
  Serial.begin(115200); 

  // Serial begin untuk modbus
  wsSerial.begin(WS_BAUD, SERIAL_8N1, RXD2, TXD2);

  // Slave address: the factory default is 01H (set according to the need, 00H to FCH)
  node.begin(1, wsSerial);
 
  // Inisialisasi wifi
  setup_wifi();   
}

void loop() {
  // Deklarasi variabel baca millis sekarang
  unsigned long currentMillis = millis();

  // Update pembacaan sesuai interval
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // Update waktu terakhir pembacaan

    // Panggil fungsi baca Kecepatan Angin
    readAngin();    

    // Panggil fungsi proses
    proses();

    // kirim semua data
    sendData();

    // Panggil fungsi menampilkan pembacaan di serial monitor
    // displaySerial();
  }
}

