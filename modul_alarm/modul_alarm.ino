// 25 April 2025
// Program MODUL ALARM
// Pesan dibaca dari modul yang terdapat di MCS yang dikirim secara lokal via UDP dengan JSON 
// Pesan tersebut diparsing sehingga dapat dimasukkan ke dalam Struct
// kodeAlarm menjadi kondisi untuk menampilkan pesan dan bunyi Buzzer
// MAC ADDRESS ALARM MCS_INDOOR : 8C:4F:00:27:B9:98
// MAC ADDRESS ALARM WMS : F4:65:0B:55:A1:4C
// MAC ADDRESS ALARM FMS : F4:65:0B:54:AB:3C

// ====================================== DEKLARASI LIBRARY =================================================================================================
// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <AsyncUDP.h>
#include <ArduinoJson.h>
// =========================== AKHIR DEKLARASI LIBRARY DAN HEADER ============================================================================================

// ========================================================= DEKLARASI PIN BUZZER ============================================================================
#define buzzPin 4    //Connect Buzzer on Digital Pin4
// ======================================================== AKHIR DEKLARASI PIN BUZZER =======================================================================

// =========================== DEKLARASI SSID DAN PASSWORD WIFI, SESUAIKAN DENGAN SSID DAN PASSWORD ANDA =====================================================
const char* ssid = "Workshop 3";
const char* password =  "eForacimenyan";
// =========================== AKHIR DEKLARASI SSID DAN PASSWORD WIFI ========================================================================================
 
// =========================== SETTING JARINGAN LOKAL DENGAN PARAMETER IP STATIC, GATEWAY, SUBNET, PRIMARY DNS, SECONDARY DNS ================================
// =========================== PASTIKAN IP ADDRESS FORMATNYA SAMA DENGAN NETWORK ADDRESS ROUTER, BEGITU JUGA UNTUK PARAMETER JARINGAN YANG LAIN ==============
IPAddress staticIP(192, 168, 0, 239);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(192, 168, 0, 1);
IPAddress dns2(0, 0, 0, 0);
// ========================== AKHIR SETTING JARINGAN LOKAL ===================================================================================================

// ========================== DEKLARASI VARIABEL UNTUK MENERIMA DATA DARI FORMAT JSON YANG DIKIRIM WSN =======================================================
String kodeModul_R;
int kodeVariabel_R;
float data_R;
int kodeAlarm_R;
String berita_R;
// ========================== AKHIR DEKLARASI VARIABEL UNTUK MENERIMA DATA DARI FORMAT JSON ==================================================================

// ========================== DEKLARASI VARIABEL UNTUK FLAG KETIKA ADA DATA BARU =============================================================================
bool dataBaruTersedia = false;
// ========================== AKHIR DEKLARASI VARIABEL UNTUK FLAG ============================================================================================

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

// ========================= DEKLARASI VARIABEL UNTUK UPDATE SESUAI INTERVAL =================================================================================
unsigned long previousMillis = 0;
const long interval = 1000;
// ========================= AKHIR DEKLARASI VARIABEL UNTUK UPDATE SESUAI INTERVAL ===========================================================================

// ========================================= DEKLARASI VARIABEL UNTUK GANTI TAMPILAN LCD =====================================================================
int displayMode = 0;
unsigned long displayChangeMillis = 0;
const long displayChangeInterval = 3000;  // Change display every 3 seconds
// ===========================================================================================================================================================

// ========================= DEKLARASI OBJEK DARI MASING-MASING LIBRARY ======================================================================================
WiFiClientSecure espClient;
AsyncUDP udp;
// LiquidCrystal_I2C lcd(0x27, 20, 4);
// ========================= AKHIR DEKLARASI OBJEK DARI MASING-MASING LIBRARY ================================================================================

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // setting pin buzzer sebagai output
  pinMode(buzzPin, OUTPUT);

  // inisialisasi wifi
  setup_wifi();

  // panggil fungsi baca
  read();

  // Initialize LCD
  // lcd.init();
  // lcd.backlight();
  // lcd.clear();
  // lcd.setCursor(0, 0);
  // lcd.print("DISPLAY ALARM");

  delay(2000);

  // lcd.clear();
}

void loop() {
  // deklarasi millis
  unsigned long currentMillis = millis();

// upload program setiap interval
  if(currentMillis - previousMillis >= interval){
    // isi variabel previousMillis dengan waktu currentMillis
    previousMillis = currentMillis;

    if(dataBaruTersedia){
      // panggil fungsi proses
      proses();

    // panggil fungsi sendData
      // sendData();

      dataBaruTersedia = false;
    }
  }
}
