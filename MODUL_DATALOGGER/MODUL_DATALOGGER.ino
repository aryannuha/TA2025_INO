// === [ESP32 Data Logger with RTC, SD Card, and Async UDP] ===

#include <WiFi.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <RTClib.h>
#include <AsyncUDP.h>
#include <ArduinoJson.h>

// ==== WiFi Configuration ====
const char* ssid = "Workshop 3";
const char* password = "eForacimenyan";

IPAddress staticIP(192, 168, 1, 240);      // IP statis ESP32
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(192, 168, 1, 1);
IPAddress dns2(0, 0, 0, 0);

// ========================== DEKLARASI VARIABEL UNTUK MENERIMA DATA DARI FORMAT JSON YANG DIKIRIM WSN =======================================================
String kodeModul_R;
int kodeVariabel_R;
float data_R;
int kodeAlarm_R;
String berita_R;
// ========================== AKHIR DEKLARASI VARIABEL UNTUK MENERIMA DATA DARI FORMAT JSON ==================================================================

// ========================= DEKLARASI STRUCTURE UNTUK SUHU INDOOR ===========================================================================================
struct struct_data_sensor_suhu {
  String kodeModul;
  int kodeVariabel;
  float data;
  int kodeAlarm;
  String berita;
};
struct_data_sensor_suhu suhuData;
// ========================= AKHIR DEKLARASI STRUCTURE UNTUK SUHU INDOOR =====================================================================================

// ========================= DEKLARASI STRUCTURE UNTUK KELEMBABAN INDOOR =====================================================================================
struct struct_data_sensor_kelembaban {
  String kodeModul;
  int kodeVariabel;
  float data;
  int kodeAlarm;
  String berita;
};
struct_data_sensor_kelembaban kelembabanData;
// ========================= AKHIR DEKLARASI STRUCTURE UNTUK KELEMBABAN INDOOR ===============================================================================

// ========================= DEKLARASI STRUCTURE UNTUK SUHU OUTDOOR ==========================================================================================
struct struct_data_sensor_suhu_out {
  String kodeModul;
  int kodeVariabel;
  float data;
  int kodeAlarm;
  String berita;
};
struct_data_sensor_suhu suhuOutData;
// ========================= AKHIR DEKLARASI STRUCTURE UNTUK SUHU OUTDOOR ====================================================================================

// ========================= DEKLARASI STRUCTURE UNTUK KELEMBABAN OUTDOOR ====================================================================================
struct struct_data_sensor_kelembaban_out {
  String kodeModul;
  int kodeVariabel;
  float data;
  int kodeAlarm;
  String berita;
};
struct_data_sensor_kelembaban kelembabanOutData;
// ========================= AKHIR DEKLARASI STRUCTURE UNTUK KELEMBABAN OUTDOOR ==============================================================================

// ========================= DEKLARASI STRUCTURE UNTUK CO2 ===================================================================================================
struct struct_data_sensor_co2{
  String kodeModul;
  int kodeVariabel;
  float data;
  int kodeAlarm;
  String berita;
};
struct_data_sensor_co2 co2Data;
// ========================= AKHIR DEKLARASI STRUCTURE UNTUK CO2 =============================================================================================

// ========================= DEKLARASI STRUCTURE UNTUK KECEPATAN ANGIN =======================================================================================
struct struct_data_sensor_ws{
  String kodeModul;
  int kodeVariabel;
  float data;
  int kodeAlarm;
  String berita;
};
struct_data_sensor_ws windspeedData;
// ========================= AKHIR DEKLARASI STRUCTURE UNTUK KECEPATAN ANGIN =================================================================================

// ========================= DEKLARASI STRUCTURE UNTUK CURAH HUJAN ===========================================================================================
struct struct_data_sensor_rf{
  String kodeModul;
  int kodeVariabel;
  float data;
  int kodeAlarm;
  String berita;
};
struct_data_sensor_rf rainfallData;
// ========================= AKHIR DEKLARASI STRUCTURE UNTUK CURAH HUJAN =====================================================================================

// ========================= DEKLARASI STRUCTURE UNTUK PAR ===================================================================================================
struct struct_data_sensor_par{
  String kodeModul;
  int kodeVariabel;
  float data;
  int kodeAlarm;
  String berita;
};
struct_data_sensor_rf parData;
// ========================= AKHIR DEKLARASI STRUCTURE UNTUK PAR =============================================================================================

// =============================================== STRUTCTURE UNTUK INA TEGANGAN ==========================================================================
struct struct_data_sensor_tegangandc{
  String kodeModul;
  int kodeVariabel;
  float data;
  int kodeAlarm;
  String berita;
};
struct_data_sensor_tegangandc tegangandcData;
// =============================================== AKHIR STRUCTURE ===========================================================================================

// =============================================== STRUTCTURE UNTUK INA ARUS ==========================================================================
struct struct_data_sensor_arusdc{
  String kodeModul;
  int kodeVariabel;
  float data;
  int kodeAlarm;
  String berita;
};
struct_data_sensor_arusdc arusdcData;
// =============================================== AKHIR STRUCTURE ===========================================================================================

// =============================================== STRUTCTURE UNTUK INA TEGANGAN ==========================================================================
struct struct_data_sensor_dayadc{
  String kodeModul;
  int kodeVariabel;
  float data;
  int kodeAlarm;
  String berita;
};
struct_data_sensor_dayadc dayadcData;
// =============================================== AKHIR STRUCTURE ===========================================================================================

// =============================================== STRUTCTURE UNTUK PZEM TEGANGAN ==========================================================================
struct struct_data_sensor_teganganac{
  String kodeModul;
  int kodeVariabel;
  float data;
  int kodeAlarm;
  String berita;
};
struct_data_sensor_teganganac teganganacData;
// =============================================== AKHIR STRUCTURE ===========================================================================================

// =============================================== STRUTCTURE UNTUK PZEM ARUS ==========================================================================
struct struct_data_sensor_arusac{
  String kodeModul;
  int kodeVariabel;
  float data;
  int kodeAlarm;
  String berita;
};
struct_data_sensor_arusac arusacData;
// =============================================== AKHIR STRUCTURE ===========================================================================================

// =============================================== STRUTCTURE UNTUK PZEM DAYA ==========================================================================
struct struct_data_sensor_dayaac{
  String kodeModul;
  int kodeVariabel;
  float data;
  int kodeAlarm;
  String berita;
};
struct_data_sensor_dayaac dayaacData;
// =============================================== AKHIR STRUCTURE ===========================================================================================

// ========================== DEKLARASI VARIABEL UNTUK FLAG KETIKA ADA DATA BARU =============================================================================
bool dataBaruTersedia = false;
// ========================== AKHIR DEKLARASI VARIABEL UNTUK FLAG ============================================================================================

// ==== SD Card Config ====
#define SD_CS 5

unsigned long previousMillis = 0;
const long interval = 1000;

// ==== RTC ====
RTC_DS3231 rtc;

// ==== UDP ====
AsyncUDP udp;
const int UDP_PORT = 1234;

// ==== File ====
String filename = "/log.csv";

void setup() {
  Serial.begin(115200);
  delay(1000);

  setup_wifi();

  // panggil fungsi setupSD() untuk mengecek file dan menulis kolom jika belum ada
  setupSD_Card();

  // panggil fungsi read() untuk menerima data UDP
  read();
}

void loop() {
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis >= interval){
    // MENGISI previousMillis DENGAN currentMillis
    previousMillis = currentMillis;

    // SAAT ADA DATA JSON BARU JALANKAN FUNGSI-FUNGSI DI BAWAH
    if(dataBaruTersedia){
      // MEMANGGIL FUNGSI parsing()
      parsing();

      // MEMANGGIL FUNGSI proses()
      proses();

      // MEMANGGIL FUNGSI sendData()
      // sendData();

      // MEMANGGIL FUNGSI displaySerial()
      displaySerial();

      // SET FLAG MENJADI FALSE HINGGA ADA DATA BARU
      dataBaruTersedia = false;
    }
  }
}
