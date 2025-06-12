/*
 Nama File      : MODUL_ALARM_V2.ino
 Tanggal Update : 12 Juni 2025
 MAC Address    : 8C:4F:00:27:B9:98
 IP Address     : 192.168.0.239
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
   1. Modul ini merupakan versi kedua dari modul alarm yang telah diperbarui untuk menangani data sensor secara efisien.
   2. Modul ini menggunakan struktur data matriks untuk menyimpan data sensor dari berbagai modul.
   3. Modul ini mengimplementasikan sistem alarm yang lebih canggih dengan penanganan prioritas alarm, tampilan LCD, dan kontrol LED.
   4. Modul ini juga mengimplementasikan sistem penanganan tombol untuk mengubah mode tampilan dan mengelola alarm.
   5. Modul ini menggunakan WiFi untuk menerima data dari server dan mengirimkan data ke server.
   6. Modul ini menggunakan library LiquidCrystal_I2C untuk mengontrol LCD I2C.
   7. Modul ini menggunakan library AsyncUDP untuk menangani komunikasi UDP secara asinkron.
   8. Modul ini menggunakan library ArduinoJson untuk memparsing data JSON yang diterima dari server.
   9. Modul ini menggunakan library Wire untuk komunikasi I2C dengan LCD.
*/

// ====================================== DEKLARASI LIBRARY =================================================================================================
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <AsyncUDP.h>
#include <ArduinoJson.h>
// =========================== AKHIR DEKLARASI LIBRARY DAN HEADER ============================================================================================

// ========================================================= DEKLARASI PIN ============================================================================
#define buzzPin 4    //Connect Buzzer on Digital Pin4
#define buttonPin 13
#define buttonPin2 15

// Deklarasi pin LED
#define ledMerahPin 27
#define ledKuningPin 12
#define ledHijauPin 14
// ======================================================== AKHIR DEKLARASI PIN =======================================================================

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
  bool isUsed = false; // Flag untuk menandai apakah slot data ini digunakan
  unsigned long alarmSilencedTime = 0; // Waktu saat alarm dimatikan
  bool warningCleared = false;
};
SensorData dataMatrix[MAX_MODULES][MAX_VARIABLES_PER_MODULE];

// Module mapping for quick access
String moduleNames[MAX_MODULES];
int numModules = 0;

// Statistics for monitoring data loss
unsigned long packetsReceived = 0;
unsigned long packetsProcessed = 0;
unsigned long lastStatsTime = 0;

// ========================================= DEKLARASI VARIABEL UNTUK TAMPILAN LCD & ALARM =====================================================================
// Mode tampilan: 0 = otomatis, 1 = manual
int displayMode = 0; 
// Indeks data sensor yang sedang ditampilkan
int currentDisplayIndex = 0; 
// Waktu terakhir display diubah (untuk mode otomatis)
unsigned long lastDisplayChange = 0;
// Durasi danger dimatikan
unsigned long alarmDangerDuration = 300000;
// Interval penggantian tampilan (2 detik)
const long displayInterval = 2000; 
// Waktu terakhir tombol ditekan (untuk debouncing)
unsigned long lastButtonPress = 0;
// Status alarm global (aktif/tidak)
bool alarmActive = false; 

// Variabel untuk Buzzer non-blocking
unsigned long buzzerStartTime = 0;
bool buzzerOn = false;
int currentAlarmCode = 0;
// ===========================================================================================================================================================

// ========================= DEKLARASI OBJEK DARI MASING-MASING LIBRARY ======================================================================================
WiFiClientSecure espClient;
AsyncUDP udp;
LiquidCrystal_I2C lcd(0x27, 20, 4);
// ========================= AKHIR DEKLARASI OBJEK DARI MASING-MASING LIBRARY ================================================================================

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // setting pin buzzer sebagai output
  pinMode(buzzPin, OUTPUT);
  digitalWrite(buzzPin, LOW);

  // Mengatur pin LED sebagai output
  pinMode(ledMerahPin, OUTPUT);
  pinMode(ledKuningPin, OUTPUT);
  pinMode(ledHijauPin, OUTPUT);
  digitalWrite(ledMerahPin, LOW);
  digitalWrite(ledKuningPin, LOW);
  digitalWrite(ledHijauPin, HIGH); // Nyalakan LED hijau sebagai status normal awal

  // setting pin button sebagai input_pullup
  pinMode(buttonPin, INPUT_PULLUP);

  // setting pin button sebagai input_pullup
  pinMode(buttonPin2, INPUT_PULLUP);

  // Initialize data matrix first
  initializeDataMatrix();

  // inisialisasi wifi
  setup_wifi();

  // panggil fungsi baca
  read();

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MODUL ALARM V2");
  lcd.setCursor(0, 1);
  lcd.print("Menunggu Data...");
  delay(2000);
  lcd.clear();

  // Set initial display time
  lastDisplayChange = millis();

  // MENJAGA SISTEM TIDAK WATCHDOG RESET
  yield();
}

void loop() {
  //  static unsigned long lastDebugTime = 0;
  // if (millis() - lastDebugTime > 5000) {
  //   Serial.println("=== DEBUG INFO ===");
  //   Serial.print("Display Mode: ");
  //   Serial.println(displayMode);
  //   Serial.print("Current Index: ");
  //   Serial.println(currentDisplayIndex);
  //   Serial.print("Total Data: ");
  //   Serial.println(countValidData());
  //   Serial.print("Current Alarm Code: ");
  //   Serial.println(currentAlarmCode);
  //   Serial.println("==================");
  //   lastDebugTime = millis();
  // }

  // Serial.print("read1: ");
  // Serial.print(digitalRead(buttonPin));
  // Serial.print("   read2: ");
  // Serial.println(digitalRead(buttonPin2));
  // 1. Selalu periksa dan tangani input tombol
  handleButtons();

  // 2. Tentukan status alarm dengan prioritas tertinggi
  checkAlarms();

  // 3. Bunyikan buzzer berdasarkan status alarm
  triggerBuzzer(); 

  // 4. Nyalakan LED yang sesuai berdasarkan status alarm
  updateLeds();

  // 5. Perbarui tampilan pada LCD jika ada perubahan
  updateDisplay();

  // Small delay to prevent excessive processing
  delay(10);
}
