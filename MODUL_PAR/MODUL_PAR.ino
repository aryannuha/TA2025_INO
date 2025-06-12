/* 
 Nama File      : MODUL_PAR.ino
 Tanggal Update : 09 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 MAC            : CC:DB:A7:2E:27:08
 IP Address     : 192.168.0.236
 Penjelasan     : 
    1. Program ini digunakan untuk membaca data PAR dari sensor PAR yang terhubung ke ESP32.
    2. Data yang dibaca akan dikirim ke beberapa tujuan melalui protokol UDP.
    3. Program ini juga menyimpan data PAR dalam EEPROM untuk keperluan regresi linear.
    4. Program ini menggunakan beberapa library seperti ModbusMaster, WiFi, HTTPClient, AsyncUDP, ArduinoJson, dan EEPROM.
    5. Program ini juga menyediakan fungsi untuk kalibrasi, filtrasi, dan regresi linear.
*/

// ============================================ DEKLARASI LIBRARY YANG DIBUTUHKAN ==========================================================================
#include <ModbusMaster.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <AsyncUDP.h>
#include <ArduinoJson.h>
#include <EEPROM.h>
// ============================================ AKHIR DEKLARASI LIBRARY =====================================================================================

// =========================== DEKLARASI SSID DAN PASSWORD WIFI, SESUAIKAN DENGAN SSID DAN PASSWORD ANDA ===================================================
const char* ssid = "Workshop 3";
const char* password = "eForacimenyan";
// =========================== AKHIR DEKLARASI SSID DAN PASSWORD WIFI ======================================================================================

// =========================== SETTING JARINGAN LOKAL DENGAN PARAMETER IP STATIC, GATEWAY, SUBNET, PRIMARY DNS, SECONDARY DNS ==============================
// =========================== PASTIKAN IP ADDRESS FORMATNYA SAMA DENGAN NETWORK ADDRESS ROUTER, BEGITU JUGA UNTUK PARAMETER JARINGAN YANG LAIN ============
IPAddress staticIP(192, 168, 0, 236);
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

// Magic number to check if EEPROM has been initialized
#define ADDR_MAGIC 32
#define MAGIC_NUMBER 0x12345678

// ================================================== DEKLARASI VARIABEL UNTUK RAWDATA PAR =============================================================
float parValue = 0;
// ================================================== AKHIR DEKLARASI VARIABEL ===============================================================================

// =============================================== STRUTCTURE UNTUK PAR ==========================================================================
struct struct_data_sensor_par{
  String kodeModul;
  int kodeVariabel;
  float data;
  int kodeAlarm;
  String berita;
};
struct_data_sensor_par parData;
// =============================================== AKHIR STRUCTURE ===========================================================================================

// ========================== DEKLARASI VARIABEL KALIBRASI ===================================================================================================
float yPar;
float awal_ukurPar, awal_sensorPar,
      akhir_ukurPar, akhir_sensorPar;
float aPar;
float cPar;
// ========================== AKHIR DEKLARASI VARIABEL KALIBRASI =============================================================================================

// ========================== DEKLARASI JUMLAH DATA UNTUK FILTRASI SIMPLE MOVING AVERAGE =====================================================================
#define WINDOW_SIZE 5   
// ========================== AKHIR DEKLARASI JUMLAH DATA UNTUK FILTRASI =====================================================================================

// ========================== DEKLARASI VARIABEL UNTUK MENYIMPAN DATA SEBANYAK WINDOW SIZE ===================================================================
float parWindow[WINDOW_SIZE];
int bufferIndex = 0;
int count = 0;
float avgPar;
// ================================================= AKHIR DEKLARASI VARIABEL UNTUK MENYIMPAN DATA SEBANYAK WINDOW SIZE =====================================

// ========================== DEKLARASI VARIABEL REGRESI LINEAR ==============================================================================================
float a, b;
float sum_x = 0, sum_y = 0, sum_xy = 0, sum_x_squared = 0;
int n = 0;
static float time_counter = 1; 
static unsigned long last_reading = 0;
float predicted_value[5];
// ========================== AKHIR DEKLARASI REGRESI LINEAR =================================================================================================

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

  // Load ML data from EEPROM
  loadMLDataFromEEPROM();
}

void loop() {
  // Deklarasi variabel baca millis sekarang
  unsigned long currentMillis = millis();

  // Update pembacaan sesuai interval
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // Update waktu terakhir pembacaan

    // Panggil fungsi baca PAR
    readPar();    

    // Panggil fungsi proses
    proses();

    // kirim semua data
    sendData();

    // Panggil fungsi menampilkan pembacaan di serial monitor
    // displaySerial();
  }

  if (currentMillis - last_reading >= 60000){
    last_reading = currentMillis;

    // PANGGIL FUNGSI add_data_point()
    add_data_point(time_counter, parData.data);

    // PANGGIL FUNGSI displayDebug()
    displayDebug();

    // PANGGIL FUNGSI showPredict()
    showPredict();
    
    // UPDATE WAKTU DATA WAKTU
    time_counter += 1.0; // Increment time

    // Save to EEPROM periodically (every hour = 60 readings)
    if (n % 60 == 0) {
      saveMLDataToEEPROM();
    }

    // reset_regression();
  }
}

