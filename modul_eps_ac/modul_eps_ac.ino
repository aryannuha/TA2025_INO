// PROGRAM SENSOR PZEM PEMBACAAN PARAMETER AC
// MAC: F4:65:0B:5B:06:68

// DEKLARASI LIBRARY
#include <PZEM004Tv30.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <AsyncUDP.h>
#include <ArduinoJson.h>
// AKHIR DEKLARASI LIBRARY

// =========================== DEKLARASI SSID DAN PASSWORD WIFI, SESUAIKAN DENGAN SSID DAN PASSWORD ANDA ===================================================
const char* ssid = "Workshop 3";
const char* password = "eForacimenyan";
// =========================== AKHIR DEKLARASI SSID DAN PASSWORD WIFI ======================================================================================

// =========================== SETTING JARINGAN LOKAL DENGAN PARAMETER IP STATIC, GATEWAY, SUBNET, PRIMARY DNS, SECONDARY DNS ==============================
// =========================== PASTIKAN IP ADDRESS FORMATNYA SAMA DENGAN NETWORK ADDRESS ROUTER, BEGITU JUGA UNTUK PARAMETER JARINGAN YANG LAIN ============
IPAddress staticIP(192,168,0,242);
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

// DEKLARASI VARIABEL GLOBAL RAWDATA
float rawVoltage, rawCurrent, rawPower, voltage_kalibrasi,
      current_kalibrasi, power_kalibrasi;
// AKHIR DEKLARASI VARIABEL 

// =============================================== STRUTCTURE UNTUK PZEM TEGANGAN ==========================================================================
struct struct_data_sensor_tegangan{
  String kodeModul;
  int kodeVariabel;
  float data;
  int kodeAlarm;
  String berita;
};
struct_data_sensor_tegangan teganganData;
// =============================================== AKHIR STRUCTURE ===========================================================================================

// =============================================== STRUTCTURE UNTUK PZEM ARUS ==========================================================================
struct struct_data_sensor_arus{
  String kodeModul;
  int kodeVariabel;
  float data;
  int kodeAlarm;
  String berita;
};
struct_data_sensor_arus arusData;
// =============================================== AKHIR STRUCTURE ===========================================================================================

// =============================================== STRUTCTURE UNTUK PZEM DAYA ==========================================================================
struct struct_data_sensor_daya{
  String kodeModul;
  int kodeVariabel;
  float data;
  int kodeAlarm;
  String berita;
};
struct_data_sensor_daya dayaData;
// =============================================== AKHIR STRUCTURE ===========================================================================================

// ========================== DEKLARASI VARIABEL KALIBRASI ===================================================================================================
// nilai kalibrasi tegangan
  float Va1 = 100;
  float Va2 = 228;
  float Vu1 = 100;
  float Vu2 = 230;
// nlai kalibrasi arus
  float Ca1 = 0.01; // Arus alat
  float Ca2 = 0.02;
  float Cu1 = 0.01; // Arus ukur
  float Cu2 = 0.021;
// ========================== AKHIR DEKLARASI VARIABEL KALIBRASI =============================================================================================

// ========================== DEKLARASI JUMLAH DATA UNTUK FILTRASI SIMPLE MOVING AVERAGE =====================================================================
#define WINDOW_SIZE 5   
// ========================== AKHIR DEKLARASI JUMLAH DATA UNTUK FILTRASI =====================================================================================

// ========================== DEKLARASI VARIABEL UNTUK MENYIMPAN DATA SEBANYAK WINDOW SIZE ===================================================================
float voltageWindow[WINDOW_SIZE];
float currentWindow[WINDOW_SIZE];
float powerWindow[WINDOW_SIZE];
int bufferIndex = 0;
int count = 0;
float avgVoltage, avgCurrent, avgPower;
// ================================================= AKHIR DEKLARASI VARIABEL UNTUK MENYIMPAN DATA SEBANYAK WINDOW SIZE =====================================

// ========================= DEKLARASI VARIABEL UNTUK UPDATE SESUAI INTERVAL =================================================================================
unsigned long previousMillis = 0;
const long interval = 1000;
// ========================= AKHIR DEKLARASI VARIABEL UNTUK UPDATE SESUAI INTERVAL ===========================================================================

// Inisialisasi PZEM 
PZEM004Tv30 pzem(Serial2, 16, 17);

// DEKLARASI GLOBAL OBJEK
WiFiClientSecure espClient;
AsyncUDP udp;
// AKHIR DEKLARASI GLOBAK OBJEK

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  Serial.println("PZEM-004T 10A Terkalibrasi");

  // Inisialisasi wifi
  setup_wifi();  
}

void loop() {
  // Deklarasi variabel baca millis sekarang
  unsigned long currentMillis = millis();

  // Update pembacaan sesuai interval
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // Update waktu terakhir pembacaan

    // Panggil fungsi baca PZEM
    readPzem();    

    // Panggil fungsi proses
    proses();

    // kirim semua data
    sendData();

    // Panggil fungsi menampilkan pembacaan di serial monitor
    displaySerial();
  }
}
