/* 
 Nama File      : MODUL_RIDAM_CLOUD_A.ino
 Tanggal Update : 09 Juni 2025
 MAC Address    : EC:64:C9:5E:A6:C8
 IP Address     : 192.168.0.237
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
   1. Program ini digunakan untuk menerima data dari WSN (Wireless Sensor Network) dengan format JSON melalui protokol UDP.
   2. Data yang diterima kemudian diparsing dan disimpan pada struktur data yang telah didefinisikan.
   3. Data yang tersimpan pada struktur data kemudian dikirim ke cloud menggunakan protokol MQTT.
   4. Program ini juga mengirim data ke Google Sheets menggunakan Google Apps Script.
   5. Program ini menggunakan library WiFi, PubSubClient, HTTPClient, AsyncUDP, dan ArduinoJson.
   6. Program ini juga mengatur koneksi WiFi, MQTT, dan Google Apps Script.
   7. Program ini juga mengatur jaringan lokal dengan IP static, gateway, subnet, primary DNS, dan secondary DNS.
   8. Program ini juga mengatur credential untuk protokol komunikasi MQTT.
   9. Program ini juga mengatur URL untuk Google Apps Script.
   10. Program ini juga mengatur variabel untuk flag ketika ada data baru tersedia.
   11. Program ini juga mengatur struktur data untuk menyimpan data dari WSN.
   12. Program ini juga mengatur variabel untuk update sesuai interval.
   13. Program ini juga mengatur variabel untuk statistik monitoring data loss.
   14. Program ini juga mengatur objek dari masing-masing library yang digunakan.
   15. Program ini juga menginisialisasi data matrix pada saat setup.
   16. Program ini juga mengatur koneksi WiFi, MQTT, dan Google Apps Script pada saat setup.
   17. Program ini juga mengatur loop untuk menjaga koneksi MQTT, mengirim data, dan mengupdate data sesuai interval.
*/

// ====================================== DEKLARASI LIBRARY =================================================================================================
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <HTTPClient.h>
#include <AsyncUDP.h>
#include <ArduinoJson.h>
// =========================== AKHIR DEKLARASI LIBRARY DAN HEADER ============================================================================================

// =========================== DEKLARASI SSID DAN PASSWORD WIFI, SESUAIKAN DENGAN SSID DAN PASSWORD ANDA =====================================================
const char* ssid = "Workshop 3";
const char* password =  "eForacimenyan";
// =========================== AKHIR DEKLARASI SSID DAN PASSWORD WIFI ========================================================================================
 
// =========================== SETTING JARINGAN LOKAL DENGAN PARAMETER IP STATIC, GATEWAY, SUBNET, PRIMARY DNS, SECONDARY DNS ================================
// =========================== PASTIKAN IP ADDRESS FORMATNYA SAMA DENGAN NETWORK ADDRESS ROUTER, BEGITU JUGA UNTUK PARAMETER JARINGAN YANG LAIN ==============
IPAddress staticIP(192, 168, 0, 237);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(192, 168, 0, 1);
IPAddress dns2(0, 0, 0, 0);
// ========================== AKHIR SETTING JARINGAN LOKAL ===================================================================================================

// ========================== SETTING CREDENTIAL UNTUK PROTOKOL KOMUNIKASI MQTT ==============================================================================
// ========================== GANTI DENGAN CREDENTIAL MQTT ANDA ==============================================================================================
const char* mqtt_server = "9a59e12602b646a292e7e66a5296e0ed.s1.eu.hivemq.cloud";
const int mqtt_port = 8883; 
const char* mqtt_user = "testing";
const char* mqtt_password = "Testing123";
// ========================== AKHIR SETTING CREDENTIAL PROTOKOL KOMUNIKASI MQTT

// ========================== URL UNTUK GOOGLE APPS SCRIPT =================================================================================================
const char* scriptUrl = "https://script.google.com/macros/s/AKfycbwH5VD__Vxotn2JnmuDVP1QMO-a3A-qt2t_Uya0uOnz2qL0peUH-pslnXjrJRE5UTq1/exec";
// ========================== AKHIR URL GOOGLE APPS SCRIPT =================================================================================================

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

// ========================= DEKLARASI VARIABEL UNTUK UPDATE SESUAI INTERVAL =================================================================================
unsigned long previousMillis = 0;
const long interval = 60000;
// ========================= AKHIR DEKLARASI VARIABEL UNTUK UPDATE SESUAI INTERVAL ===========================================================================

// Statistics for monitoring data loss
unsigned long packetsReceived = 0;
unsigned long packetsProcessed = 0;
unsigned long lastStatsTime = 0;

// ========================= DEKLARASI OBJEK DARI MASING-MASING LIBRARY ======================================================================================
WiFiClientSecure espClient;
PubSubClient client(espClient);
AsyncUDP udp;
// ========================= AKHIR DEKLARASI OBJEK DARI MASING-MASING LIBRARY ================================================================================

void setup() {
  // INISIALISASI SERIAL
  Serial.begin(115200);

  // Initialize data matrix first
  initializeDataMatrix();

  // PANGGIL FUNGSI setup_wifi()
  setup_wifi();

  // PANGGIL FUNGSI read()
  read();

  // MENGGUNAKAN SERTIFIKAT ROOT UNTUK MQTT
  espClient.setInsecure();  

  // SETTING MQTT SERVER DAN PORT
  client.setServer(mqtt_server, mqtt_port); 

  // MENJAGA SISTEM TIDAK WATCHDOG RESET
  yield();
}

void loop() {
  // MEMULAI MILLIS
  unsigned long currentMillis = millis();

  // LOOP MQTT
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if(dataBaruTersedia && !processingData){
    processingData = true;

    // MEMANGGIL FUNGSI displaySerial()
    // displaySerial();
    
    // reset flag
    dataBaruTersedia = false;
    processingData = false;
  }

  // UPLOAD PROGRAM SETIAP INTERVAL
  if(currentMillis - previousMillis >= interval){
    // MENGISI previousMillis DENGAN currentMillis
    previousMillis = currentMillis;

    // Kirim ini pertama
    client.publish("mcs/kodeData0000", "1", false);
    delay(10);

    // MEMANGGIL FUNGSI sendData()
    sendData();

    // MEMANGGIL FUNGSI BARU UNTUK GOOGLE SHEETS
    sendToSpreadsheet();

    Serial.println("1");
  }

  if (currentMillis - lastStatsTime > 30000) {
    printStatistics();
    lastStatsTime = currentMillis;
  }

  // Prevent watchdog reset
  yield();
}
