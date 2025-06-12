/* 
 Nama File      : MODUL_RAINFALL.ino
 Tanggal Update : 09 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 MAC            : F4:65:0B:59:DA:08
 IP Address     : 192.168.0.235
 Penjelasan     : 
    1. Program ini digunakan untuk membaca data curah hujan dari sensor yang terhubung ke ESP32.
    2. Data yang dibaca akan dikirim ke beberapa tujuan melalui protokol UDP.
    3. Program ini juga menyimpan data curah hujan dalam EEPROM untuk keperluan regresi linear.
    4. Program ini menggunakan beberapa library seperti WiFi, HTTPClient, AsyncUDP, ArduinoJson, dan EEPROM.
    5. Program ini juga menyediakan fungsi untuk kalibrasi, filtrasi, dan regresi linear.
    6. Program ini juga menyediakan fungsi untuk menghitung curah hujan berdasarkan jumlah tip yang terdeteksi.
*/

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
#include <EEPROM.h>
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

unsigned long lastTipTime = 0;
unsigned long hujanTimeout = 10 * 60 * 1000; // 10 menit
unsigned long lastCheck = 0;
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

  // Load ML data from EEPROM
  loadMLDataFromEEPROM();
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

  if (currentMillis - last_reading >= 60000){
    last_reading = currentMillis;

    // PANGGIL FUNGSI add_data_point()
    add_data_point(time_counter, rainfallData.data);

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

