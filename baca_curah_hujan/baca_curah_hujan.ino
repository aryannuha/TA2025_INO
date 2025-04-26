// 25 APRIL 2025
// AUTHOR : AMMAR ARYAN NUHA
// PROGRAM AKUISISI DATA CURAH HUJAN,
// KIRIM KE RIDAM CLOUD A, RIDAM LOCAL A, ALARM, DAN DATALOGGER
// MENGIRIM DATA DALAM FORMAT JSON MELALUI JARINGAN LOKAL DENGAN PROTOKOL UDP
// SENSOR CURAH HUJAN DIHUBUNGKAN DENGAN ESP32 PADA PIN GPIO4
// PEMBACAAN RAW DATA DISIMPAN PADA VARIABEL jumlah_tip DAN rainfall
// TERSEDIA FUNGSI KALIBRASI DAN FILTRASI JIKA DIBUTUHKAN
// UNTUK SAAT INI RAW DATA LANGSUNG DIMASUKKAN KE DALAM STRUCT
// MAC ADDRESS CURAH HUJAN F4:65:0B:59:DA:08

//Curah hujan adalah jumlah air yang jatuh di permukaan tanah selama periode tertentu yang diukur dengan satuan tinggi milimeter (mm) di atas permukaan horizontal.
//Curah hujan 1 mm adalah jumlah air hujan yang jatuh di permukaan per satuan luas (m2) dengan volume sebanyak 1 liter tanpa ada yang menguap, meresap atau mengalir.
// Lebih lengkap silahkan dipelajari lebih lanjut disini https://www.climate4life.info/2015/12/hujan-1-milimeter-yang-jatuh-di-jakarta.html

//Perhitungan rumus
//Tinggi curah hujan (cm) = volume yang dikumpulkan (mL) / area pengumpulan (cm2)
//Luas kolektor (Corong) 8,4cm x 3,7cm = 31,08 cm2
//Koleksi per ujung tip kami dapat dengan cara menuangkan 100ml air ke kolektor kemudian menghitung berapa kali air terbuang dari tip,
//Dalam perhitungan yang kami lakukan air terbuang sebanyak 70 kali. 100ml / 70= 1.42mL per tip.
//Jadi 1 tip bernilai 1.42 / 31.08 = 0,04cm atau 0.40 mm curah hujan.

// PENTING
// Nilai kalibrasi yang kami lakukan berlaku untuk semua sensor curah hujan yang kami jual tentu Anda dapat melakukan kalibrasi ulang sendiri jika dibutuhkan.

// ============================================ DEKLARASI LIBRARY YANG DIBUTUHKAN ==========================================================================
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <AsyncUDP.h>
#include <ArduinoJson.h>
// ============================================ AKHIR DEKLARASI LIBRARY ====================================================================================

// =========================== DEKLARASI SSID DAN PASSWORD WIFI, SESUAIKAN DENGAN SSID DAN PASSWORD ANDA ===================================================
const char* ssid = "Workshop 3";
const char* password = "eForacimenyan";
// =========================== AKHIR DEKLARASI SSID DAN PASSWORD WIFI ======================================================================================

// =========================== SETTING JARINGAN LOKAL DENGAN PARAMETER IP STATIC, GATEWAY, SUBNET, PRIMARY DNS, SECONDARY DNS ==============================
// =========================== PASTIKAN IP ADDRESS FORMATNYA SAMA DENGAN NETWORK ADDRESS ROUTER, BEGITU JUGA UNTUK PARAMETER JARINGAN YANG LAIN ============
IPAddress staticIP(192, 168, 0, 235);
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

// ==================================== DEKLARASI VARIABEL UNTUK MEMBACA CURAH HUJAN =========================================================================
const int pin_interrupt = 4; 
long int jumlah_tip = 0;
long int temp_jumlah_tip = 0;
float rainfall = 0.00;
float milimeter_per_tip = 0.40;
volatile boolean flag = false;
// =================================== AKHIR DEKLARASI VARIABEL UNTUK CURAH HUJAN ============================================================================

// ========================== DEKLARASI STRUCTURE UNTUK CURAH HUJAN ==========================================================================================
struct struct_data_sensor_rf{
  String kodeModul;
  int kodeVariabel;
  float data;
  int kodeAlarm;
  String berita;
};
struct_data_sensor_rf rainfallData;
// ========================== AKHIR STRUCT CURAH HUJAN ======================================================================================================

// ========================== DEKLARASI JUMLAH DATA UNTUK FILTRASI SIMPLE MOVING AVERAGE =====================================================================
#define WINDOW_SIZE 5   
// ========================== AKHIR DEKLARASI JUMLAH DATA UNTUK FILTRASI =====================================================================================

// ========================== DEKLARASI VARIABEL UNTUK MENYIMPAN DATA SEBANYAK WINDOW SIZE ===================================================================
float rainfallWindow[WINDOW_SIZE];
int bufferIndex = 0;
int count = 0;
float avgRainfall;
// ========================== AKHIR DEKLARASI VARIABEL UNTUK MENYIMPAN DATA SEBANYAK WINDOW SIZE =============================================================

// ========================== DEKLARASI VARIABEL KALIBRASI ===================================================================================================
float yRainfall;
float awal_ukurRainfall, awal_sensorRainfall,
      akhir_ukurRainfall, akhir_sensorRainfall;
float aRainfall;
float cRainfall;
// ========================== AKHIR DEKLARASI VARIABEL KALIBRASI =============================================================================================

// ========================= DEKLARASI VARIABEL UNTUK UPDATE SESUAI INTERVAL =================================================================================
unsigned long previousMillis = 0;
const long interval = 1000;
// ========================= AKHIR DEKLARASI VARIABEL UNTUK UPDATE SESUAI INTERVAL ===========================================================================

// ========================= DEKLARASI OBJEK UNTUK MASING-MASING LIBRARY =====================================================================================
WiFiClientSecure espClient;
AsyncUDP udp;
// ========================= AKHIR DEKLARASI OBJEK ===========================================================================================================

void setup() {
  // INISIALISASI SERIAL
  Serial.begin(115200); 

  // INISIALISASI PIN INTERRUPT
  pinMode(pin_interrupt, INPUT);
  attachInterrupt(digitalPinToInterrupt(pin_interrupt), hitung_curah_hujan, FALLING); // Akan menghitung tip jika pin berlogika dari HIGH ke LOW

  // PANGGIL FUNGSI setup_wifi()
  setup_wifi();
}

void loop() {
  // Deklarasi variabel baca millis sekarang
  unsigned long currentMillis = millis();

  // Update pembacaan sesuai interval
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // Update waktu terakhir pembacaan

    // Panggil fungsi baca Kecepatan Angin
    readHujan();    

    // Panggil fungsi proses
    proses();

    // kirim semua data
    sendData();

    // Panggil fungsi menampilkan pembacaan di serial monitor
    // displaySerial();
  }
}

