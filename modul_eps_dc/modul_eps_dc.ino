// PROGRAM SENSOR INA219 PEMBACAAN ARUS DC
// MAC: F4:65:0B:54:E3:98

// DEKLARASI LIBRARY
#include <Wire.h>
#include <Adafruit_INA219.h>
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
IPAddress staticIP(192,168,0,241);
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

// DEFINISI PIN SCL DAN SDA
#define SCL 22
#define SDA 21
// AKHIR DEFINISI PIN

// DEKLARASI VARIABEL GLOBAL RAWDATA
float busVoltage, voltage_kalibrasi, current_kalibrasi, 
      power, power_kalibrasi, current, shuntVoltage;
// AKHIR DEKLARASI VARIABEL 

// =============================================== STRUTCTURE UNTUK INA TEGANGAN ==========================================================================
struct struct_data_sensor_tegangan{
  String kodeModul;
  int kodeVariabel;
  float data;
  int kodeAlarm;
  String berita;
};
struct_data_sensor_tegangan teganganData;
// =============================================== AKHIR STRUCTURE ===========================================================================================

// =============================================== STRUTCTURE UNTUK INA ARUS ==========================================================================
struct struct_data_sensor_arus{
  String kodeModul;
  int kodeVariabel;
  float data;
  int kodeAlarm;
  String berita;
};
struct_data_sensor_arus arusData;
// =============================================== AKHIR STRUCTURE ===========================================================================================

// =============================================== STRUTCTURE UNTUK INA TEGANGAN ==========================================================================
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
  float Va1 = 3.3;
  float Va2 = 4.96;
  float Vu1 = 3.3;
  float Vu2 = 4.962;
// nlai kalibrasi arus
  float Ca1 = 0.01; // Arus alat
  float Ca2 = 0.02;
  float Cu1 = 0.01; // Arus ukur
  float Cu2 = 0.02;
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

// DEKLARASI GLOBAL OBJEK
Adafruit_INA219 ina219;
WiFiClientSecure espClient;
AsyncUDP udp;
// AKHIR DEKLARASI GLOBAK OBJEK

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial); // Tunggu serial terbuka

  Wire.begin(SDA, SCL); // SDA = 21, SCL = 22 (default ESP32)

  if (!ina219.begin()) {
    Serial.println("Gagal mendeteksi INA219. Cek koneksi I2C.");
    while (1);
  }

  Serial.println("INA219 Terdeteksi.");

  // Inisialisasi wifi
  setup_wifi();  
}

void loop() {
  // Deklarasi variabel baca millis sekarang
  unsigned long currentMillis = millis();

  // Update pembacaan sesuai interval
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // Update waktu terakhir pembacaan

    // Panggil fungsi baca Ina
    readIna();    

    // Panggil fungsi proses
    proses();

    // kirim semua data
    sendData();

    // Panggil fungsi menampilkan pembacaan di serial monitor
    displaySerial();
  }
}
