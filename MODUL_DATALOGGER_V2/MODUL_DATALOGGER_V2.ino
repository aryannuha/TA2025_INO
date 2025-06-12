/*
 Nama File      : MODUL_DATALOGGER_V2.ino
 Tanggal Update : 12 Juni 2025
 MAC Address    : 8C:4F:00:27:EA:E0
 IP Address     : 192.168.0.240
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
   1. Program ini merupakan program untuk menerima data dari modul rida-M melalui UDP, menyimpan data tersebut ke dalam matriks, dan menyimpannya ke dalam file CSV di SD Card.
   2. Program ini juga menyediakan server web untuk mengakses data yang telah disimpan.
   3. Program ini menggunakan RTC untuk menyimpan waktu dan tanggal saat data diterima.
   4. Program ini menggunakan WiFi untuk menghubungkan ESP32 ke jaringan lokal.
   5. Program ini menggunakan ArduinoJson untuk memparsing data yang diterima dari modul rida-M.
   6. Program ini menggunakan AsyncUDP untuk menerima data dari modul rida-M secara asinkron.
   7. Program ini menggunakan WebServer untuk menyediakan akses ke data yang telah disimpan.
   8. Program ini menggunakan SPI untuk berkomunikasi dengan SD Card.
   9. Program ini menggunakan Wire untuk berkomunikasi dengan RTC.
   10. Program ini menggunakan RTClib untuk mengakses RTC.
*/

#include <WiFi.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <RTClib.h>
#include <AsyncUDP.h>
#include <ArduinoJson.h>
#include <WebServer.h>

// ==== WiFi Configuration ====
const char* ssid = "Workshop 3";
const char* password = "eForacimenyan";

IPAddress staticIP(192, 168, 0, 240);      // IP statis ESP32
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(192, 168, 0, 1);
IPAddress dns2(0, 0, 0, 0);

// ========================== DEKLARASI VARIABEL UNTUK FLAG KETIKA ADA DATA BARU =============================================================================
volatile bool dataBaruTersedia = false;
bool processingData = false;
// ========================== AKHIR DEKLARASI VARIABEL UNTUK FLAG ============================================================================================

// rida-M matrix structure - sensor data storage
#define MAX_MODULES 10
#define MAX_VARIABLES_PER_MODULE 23

// Data structure representing our row-indexed matrix
struct SensorData {
  String kodeModul;
  int kodeVariabel;
  float kodeData;
  int kodeAlarm;
  String berita;
};
SensorData dataMatrix[MAX_MODULES][MAX_VARIABLES_PER_MODULE];

// Module mapping for quick access
String moduleNames[MAX_MODULES];
int numModules = 0;

// ==== SD Card Config ====
#define SD_CS 5

unsigned long previousMillis = 0;
const long interval = 60000;

// Statistics for monitoring data loss
unsigned long packetsReceived = 0;
unsigned long packetsProcessed = 0;
unsigned long lastStatsTime = 0;

// ==== RTC ====
RTC_DS3231 rtc;

// ==== UDP ====
AsyncUDP udp;
const int UDP_PORT = 1234;

// ==== WebServer ====
WebServer server(80);

// ==== File ====
String filename = "/log.csv";

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Initialize data matrix first
  initializeDataMatrix();

  setup_wifi();

  // panggil fungsi setupSD() untuk mengecek file dan menulis kolom jika belum ada
  setupSD_Card();

  // Routing web
  server.on("/", handleRoot);
  server.on("/download", handleDownload);
  server.on("/data", HTTP_GET, handleApiData);

  server.begin();
  Serial.println("Server dimulai");

  // panggil fungsi read() untuk menerima data UDP
  read();

  // MENJAGA SISTEM TIDAK WATCHDOG RESET
  yield();
}

void loop() {
  unsigned long currentMillis = millis();

  if(dataBaruTersedia && !processingData){
    processingData = true;

    // MEMANGGIL FUNGSI displaySerial()
    // displaySerial();
    
    // reset flag
    dataBaruTersedia = false;
    processingData = false;
  }

  if(currentMillis - previousMillis >= interval){
    // MENGISI previousMillis DENGAN currentMillis
    previousMillis = currentMillis;

    saveDataToSD();
  }

  if (currentMillis - lastStatsTime > 30000) {
    printStatistics();
    lastStatsTime = currentMillis;
  }
  server.handleClient();
}
