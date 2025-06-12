/* 
 Nama File      : MODUL_GPS.ino
 Tanggal Update : 09 Juni 2025
 MAC Address    : EC:64:C9:5E:8D:28
 IP Address     : 192.168.0.243
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
    1. Program ini digunakan untuk membaca data GPS dari modul GPS yang terhubung ke ESP32.
    2. Data yang dibaca meliputi latitude, longitude, altitude, speed, hdop, dan jumlah satelit.
    3. Data tersebut kemudian dikirimkan ke server melalui protokol UDP.
    4. Program ini juga menampilkan data GPS pada Serial Monitor.
    5. Pastikan untuk mengatur SSID dan password WiFi sesuai dengan jaringan yang digunakan.
    6. Pastikan juga untuk mengatur IP address sesuai dengan jaringan lokal yang digunakan.
    7. Program ini menggunakan library TinyGPS++ untuk memudahkan pengolahan data GPS.
    8. Program ini juga menggunakan library WiFi, WiFiClientSecure, HTTPClient, AsyncUDP, dan ArduinoJson untuk mengirimkan data ke server.
    9. Pastikan untuk menginstal library yang diperlukan sebelum mengupload program ini ke ESP32.
   10. Program ini juga menggunakan struktur data untuk menyimpan data GPS yang akan dikirimkan ke server.
   11. Program ini juga menggunakan fungsi untuk menginisialisasi koneksi WiFi, membaca data GPS, memproses data GPS, mengirimkan data ke server, dan menampilkan data pada Serial Monitor.
   12. Program ini juga menggunakan fungsi untuk mengatur interval pengiriman data GPS ke server.
   13. Program ini juga menggunakan fungsi untuk mengatur IP address tujuan pengiriman data GPS.
   14. Program ini juga menggunakan fungsi untuk mengatur koneksi UDP untuk pengiriman data GPS.
   15. Program ini juga menggunakan fungsi untuk mengatur koneksi WiFi dengan IP static, gateway, subnet, primary DNS, dan secondary DNS.
   16. Program ini juga menggunakan fungsi untuk mengatur koneksi WiFi dengan SSID dan password yang telah ditentukan.
   17. Program ini juga menggunakan fungsi untuk mengatur koneksi WiFi dengan IP address yang telah ditentukan.
   18. Program ini juga menggunakan fungsi untuk mengatur koneksi WiFi dengan gateway yang telah ditentukan.
   19. Program ini juga menggunakan fungsi untuk mengatur koneksi WiFi dengan subnet yang telah ditentukan.
   20. Program ini juga menggunakan fungsi untuk mengatur koneksi WiFi dengan primary DNS yang telah ditentukan.
   21. Program ini juga menggunakan fungsi untuk mengatur koneksi WiFi dengan secondary DNS yang telah ditentukan.
   22. Program ini juga menggunakan fungsi untuk mengatur koneksi WiFi dengan IP address tujuan pengiriman data GPS yang telah ditentukan.
*/

// AWAL DEKLARASI LIBRARY
#include <Arduino.h>
#include <TinyGPS++.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <AsyncUDP.h>
#include <ArduinoJson.h>
// AKHIR DEKLARASI LIBRARY

// =========================== DEKLARASI SSID DAN PASSWORD WIFI, SESUAIKAN DENGAN SSID DAN PASSWORD ANDA =====================================================
const char* ssid = "Workshop 3";
const char* password =  "eForacimenyan";
// =========================== AKHIR DEKLARASI SSID DAN PASSWORD WIFI ========================================================================================
 
// =========================== SETTING JARINGAN LOKAL DENGAN PARAMETER IP STATIC, GATEWAY, SUBNET, PRIMARY DNS, SECONDARY DNS ================================
// =========================== PASTIKAN IP ADDRESS FORMATNYA SAMA DENGAN NETWORK ADDRESS ROUTER, BEGITU JUGA UNTUK PARAMETER JARINGAN YANG LAIN ==============
IPAddress staticIP(192, 168, 0, 243);
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

// AWAL DEFINISI VARIABEL PIN DAN BAUDRATE GPS
#define RXD2 16
#define TXD2 17
#define GPS_BAUD 9600
// AKHIR DEFINISI

// Structure untuk GPS latitude
struct struct_data_sensor_latitude {
  String kodeModul;
  int kodeVariabel;
  float data;
  int kodeAlarm;
  String berita;
};
struct_data_sensor_latitude latData;
// Akhir structur latitude

// Structure untuk GPS longitude
struct struct_data_sensor_longitude {
  String kodeModul;
  int kodeVariabel;
  float data;
  int kodeAlarm;
  String berita;
};
struct_data_sensor_longitude lonData;
// Akhir structure longitude

// AWAL DEKLARASI VARIABEL lat dan lon
float lat = 0; //latitude
float lon = 0; //longitude
float alt = 0; //altitude
float spd = 0; //speed
float hdop = 0; //hdop
float stl = 0; //satellites
// AKHIR DEKLARASI VARIABEL

// ========================= DEKLARASI VARIABEL UNTUK UPDATE SESUAI INTERVAL =================================================================================
unsigned long previousMillis = 0;
const long interval = 1000;
// ========================= AKHIR DEKLARASI VARIABEL UNTUK UPDATE SESUAI INTERVAL ===========================================================================

// DEKLARASI GLOBAL OBJEK
TinyGPSPlus gps;              // Objek GPS
HardwareSerial gpsSerial(2);  // Serial2 untuk GPS
WiFiClientSecure espClient;
AsyncUDP udp;
// AKHIR DEKLARASI GLOBAL OBJEK

void setup() {
  // Inisialisasi Serial
  Serial.begin(115200);
  delay(2000);

  // Panggil fungsi setup_wifi
  setup_wifi();

  // Inisialisasi gps
  gpsSerial.begin(GPS_BAUD, SERIAL_8N1, RXD2, TXD2);
  Serial.println("Serial2 (GPS) started at 9600 baud rate");
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;

    // Panggil fungsi bacaGPS()
    bacaGPS();

    // Panggil fungsi proses()
    proses();

    // Panggil fungsi sendData()
    sendData();

    // Panggil fungsi displaySerial()
    displaySerial();
  }
}
