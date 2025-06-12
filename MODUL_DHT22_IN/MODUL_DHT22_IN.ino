/* 
 Nama File      : MODUL_DHT22_IN.ino
 Tanggal Update : 09 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 MAC            : F4:65:0B:54:9C:74
 IP Address     : 192.168.0.231
 Penjelasan     : 
    1. Program ini digunakan untuk membaca data suhu dan kelembaban dari sensor DHT22 yang terhubung ke ESP32.
    2. Data yang dibaca akan dikirim ke beberapa tujuan melalui protokol UDP.
    3. Program ini juga menyimpan data suhu dan kelembaban dalam EEPROM untuk keperluan regresi linear.
    4. Program ini menggunakan beberapa library seperti DHT, WiFi, HTTPClient, AsyncUDP, ArduinoJson, dan EEPROM.
    5. Program ini juga menyediakan fungsi untuk kalibrasi, filtrasi, dan regresi linear.
*/

// ============================================ DEKLARASI LIBRARY YANG DIBUTUHKAN ==========================================================================
#include <DHT.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <AsyncUDP.h>
#include <ArduinoJson.h>
#include <EEPROM.h>
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

// ========================== EEPROM ADDRESSES FOR STORING ML DATA ========================================================================================
#define EEPROM_SIZE 512
// Temperature regression data addresses
#define ADDR_A 0
#define ADDR_B 4
#define ADDR_SUM_X 8
#define ADDR_SUM_Y 12
#define ADDR_SUM_XY 16
#define ADDR_SUM_X_SQUARED 20
#define ADDR_N 24
#define ADDR_TIME_COUNTER 28

// Humidity regression data addresses
#define ADDR_A_HUMID 32
#define ADDR_B_HUMID 36
#define ADDR_SUM_X_HUMID 40
#define ADDR_SUM_Y_HUMID 44
#define ADDR_SUM_XY_HUMID 48
#define ADDR_SUM_X_SQUARED_HUMID 52
#define ADDR_N_HUMID 56
#define ADDR_TIME_COUNTER_HUMID 60

// Magic number to check if EEPROM has been initialized
#define ADDR_MAGIC 64
#define MAGIC_NUMBER 0x12345678

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

// ========================== DEKLARASI VARIABEL REGRESI LINEAR ==============================================================================================
float a, b, a_humid, b_humid;
float sum_x = 0, sum_y = 0, sum_xy = 0, sum_x_squared = 0,
      sum_x_humid = 0, sum_y_humid = 0, sum_xy_humid = 0, sum_x_squared_humid = 0;
int n = 0, n_humid = 0;
static float time_counter = 1, time_counter_humid = 1; 
static unsigned long last_reading = 0;
float predicted_value_temp[5], predicted_value_humidity[5];
// ========================== AKHIR DEKLARASI REGRESI LINEAR =================================================================================================

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

  // Load ML data from EEPROM
  loadMLDataFromEEPROM();
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

  if (currentMillis - last_reading >= 60000){
    last_reading = currentMillis;

    // PANGGIL FUNGSI add_data_point()
    add_data_point_temp(time_counter, suhuData.data);
    add_data_point_humid(time_counter_humid, kelembabanData.data);

    // PANGGIL FUNGSI displayDebug()
    displayDebug();

    // PANGGIL FUNGSI showPredict()
    showPredict();
    
    // UPDATE WAKTU DATA WAKTU
    time_counter += 1.0; // Increment time
    time_counter_humid += 1.0; // Increment time

    // Save to EEPROM periodically (every hour = 60 readings)
    if (n % 60 == 0 || n_humid % 60 == 0) {
      saveMLDataToEEPROM();
    }

    // reset_regression();
  }
}

