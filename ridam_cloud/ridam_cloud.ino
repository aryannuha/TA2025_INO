// 25 APRIL 2025
// AUTHOR : AMMAR ARYAN NUHA
// PROGRAM RIDAM CLOUD A
// MENERIMA DATA DARI WSN DENGAN FORMAT JSON DENGAN PROTOKOL UDP
// PADA VARIABEL kodeModul_R, kodeVariabel_R, data_R, kodeAlarm_R, berita_R
// DATA YANG DITERIMA KEMUDIAN DIPARSING UNTUK DISIMPAN PADA MASING-MASING STRUCT
// SESUAI DENGAN PARAMETER WSN
// DATA YANG TERDAPAT PADA STRUCT DIKIRIM KE CLOUD DENGAN PROTOKOL MQTT
// MELALUI BUFFER MQTT UNTUK DIUBAH MENJADI STRING TERLEBIH DAHULU

// ====================================== DEKLARASI LIBRARY =================================================================================================
#include <DHT.h>
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

// ========================== DEKLARASI VARIABEL BUFFER KIRIM KE MQTT ========================================================================================
// SUHU INDOOR
char kodeModulSuhuIn_str[10], kodeVariabelSuhuIn_str[10], kodeDataSuhuIn_str[10], 
      kodeAlarmSuhuIn_str[10], beritaSuhuIn_str[50];

// KELEMBABAN INDOOR
char kodeModulKelembabanIn_str[10], kodeVariabelKelembabanIn_str[10], kodeDataKelembabanIn_str[10],
      kodeAlarmKelembabanIn_str[10], beritaKelembabanIn_str[50];

// SUHU OUTDOOR
char kodeModulSuhuOut_str[10], kodeVariabelSuhuOut_str[10], kodeDataSuhuOut_str[10], 
      kodeAlarmSuhuOut_str[10], beritaSuhuOut_str[50];

// KELEMBABAN OUTDOOR
char kodeModulKelembabanOut_str[10], kodeVariabelKelembabanOut_str[10], kodeDataKelembabanOut_str[10],
      kodeAlarmKelembabanOut_str[10], beritaKelembabanOut_str[50];

// CO2
char kodeModulCo2_str[10], kodeVariabelCo2_str[10], kodeDataCo2_str[10],
      kodeAlarmCo2_str[10], beritaCo2_str[50];

// KECEPATAN ANGIN
char kodeModulWindspeed_str[10], kodeVariabelWindspeed_str[10], kodeDataWindspeed_str[10],
      kodeAlarmWindspeed_str[10], beritaWindspeed_str[50];

// CURAH HUJAN
char kodeModulRainfall_str[10], kodeVariabelRainfall_str[10], kodeDataRainfall_str[10],
      kodeAlarmRainfall_str[10], beritaRainfall_str[50];

// PAR
char kodeModulPar_str[10], kodeVariabelPar_str[10], kodeDataPar_str[10],
      kodeAlarmPar_str[10], beritaPar_str[50];
// ========================= AKHIR DEKLARASI VARIABEL BUFFER KIRIM KE MQTT ===================================================================================

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

// ========================= DEKLARASI VARIABEL UNTUK UPDATE SESUAI INTERVAL =================================================================================
unsigned long previousMillis = 0;
const long interval = 1000;
// ========================= AKHIR DEKLARASI VARIABEL UNTUK UPDATE SESUAI INTERVAL ===========================================================================

// ========================= DEKLARASI OBJEK DARI MASING-MASING LIBRARY ======================================================================================
WiFiClientSecure espClient;
PubSubClient client(espClient);
AsyncUDP udp;
// ========================= AKHIR DEKLARASI OBJEK DARI MASING-MASING LIBRARY ================================================================================

void setup() {
  // INISIALISASI SERIAL
  Serial.begin(115200);

  // PANGGIL FUNGSI setup_wifi()
  setup_wifi();

  // PANGGIL FUNGSI read()
  read();

  // TUNGGU 2 DETIK SEBELUM MASUK KE LOOP
  delay(2000);

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

  // UPLOAD PROGRAM SETIAP INTERVAL
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
      sendData();

      // MEMANGGIL FUNGSI displaySerial()
      displaySerial();

      // SET FLAG MENJADI FALSE HINGGA ADA DATA BARU
      dataBaruTersedia = false;
    }
  }
}
