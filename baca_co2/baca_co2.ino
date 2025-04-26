// 25 APRIL 2025
// AUTHOR : AMMAR ARYAN NUHA
// PROGRAM AKUISISI DATA CO2,
// KIRIM KE RIDAM CLOUD A, RIDAM LOCAL A, ALARM, DAN DATALOGGER
// MENGIRIM DATA DALAM FORMAT JSON MELALUI JARINGAN LOKAL DENGAN PROTOKOL UDP
// SENSOR CO2 DIHUBUNGKAN DENGAN ESP32 PADA PIN GPIO32 UNTUK ADC
// PEMBACAAN RAW DATA DISIMPAN PADA VARIABEL volts DAN rawCO2
// TERSEDIA FUNGSI KALIBRASI DAN FILTRASI JIKA DIBUTUHKAN
// UNTUK SAAT INI RAW DATA LANGSUNG DIMASUKKAN KE DALAM STRUCT
// MAC ADDRESS CO2 F4:65:0B:59:07:50

// ============================================ DEKLARASI LIBRARY YANG DIBUTUHKAN ==========================================================================
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <AsyncUDP.h>
#include <ArduinoJson.h>
// ============================================ AKHIR DEKLARASI LIBRARY ====================================================================================

// ============================================ DEKLARASI TERKAIT SENSOR CO2 ===============================================================================
#define         MG_PIN                       (32)     // ESP32 ADC pin (GPIO34)
// #define         BOOL_PIN                     (4)      // ESP32 digital pin (GPIO4)
#define         DC_GAIN                      (8.5)    // define the DC gain of amplifier
#define         ADC_RESOLUTION               (4096)   // ESP32 12-bit ADC resolution
#define         ADC_VOLTAGE                  (3.3)    // ESP32 operates at 3.3V instead of 5V

#define         READ_SAMPLE_INTERVAL         (50)    // define the time interval(in milisecond) between each samples
#define         READ_SAMPLE_TIMES            (5)     // define how many samples you are going to take in normal operation

#define         ZERO_POINT_VOLTAGE           (0.00048470) // define the output of the sensor in volts when the concentration of CO2 is 400PPM, was read 412mV
#define         REACTION_VOLTAGE             (0.030) // define the voltage drop of the sensor when move the sensor from air into 1000ppm CO2

float           CO2Curve[3]  =  {2.602,ZERO_POINT_VOLTAGE,(REACTION_VOLTAGE/(2.602-3))};
                                                     // two points are taken from the curve.
                                                     // with these two points, a line is formed which is
                                                     // "approximately equivalent" to the original curve.
                                                     // data format:{ x, y, slope}; point1: (lg400, 0.324), point2: (lg4000, 0.280)
                                                     // slope = ( reaction voltage ) / (log400 –log1000)
// =============================================== AKHIR DEKLARASI TERKAIT CO2 =============================================================================

// =========================== DEKLARASI SSID DAN PASSWORD WIFI, SESUAIKAN DENGAN SSID DAN PASSWORD ANDA ===================================================
const char* ssid = "Workshop 3";
const char* password = "eForacimenyan";
// =========================== AKHIR DEKLARASI SSID DAN PASSWORD WIFI ======================================================================================

// =========================== SETTING JARINGAN LOKAL DENGAN PARAMETER IP STATIC, GATEWAY, SUBNET, PRIMARY DNS, SECONDARY DNS ==============================
// =========================== PASTIKAN IP ADDRESS FORMATNYA SAMA DENGAN NETWORK ADDRESS ROUTER, BEGITU JUGA UNTUK PARAMETER JARINGAN YANG LAIN ============
IPAddress staticIP(192, 168, 0, 233);
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

// ========================== DEKLARASI VARIABEL UNTUK MENYIMPAN RAW DATA CO2 ================================================================================
int rawCO2;
float volts;
// ========================== AKHIR DEKLARASI VARIABEL RAW DATA CO2 ==========================================================================================

// ========================== DEKLARASI STRUCTURE UNTUK CO2 ==================================================================================================
struct struct_data_sensor_co2{
  String kodeModul;
  int kodeVariabel;
  float data;
  int kodeAlarm;
  String berita;
};
struct_data_sensor_co2 co2Data;
// ========================= AKHIR STRUCTURE CO2 =============================================================================================================

// ========================== DEKLARASI JUMLAH DATA UNTUK FILTRASI SIMPLE MOVING AVERAGE =====================================================================
#define WINDOW_SIZE 5   
// ========================== AKHIR DEKLARASI JUMLAH DATA UNTUK FILTRASI =====================================================================================

// ========================== DEKLARASI VARIABEL UNTUK MENYIMPAN DATA SEBANYAK WINDOW SIZE ===================================================================
float co2Window[WINDOW_SIZE];
int bufferIndex = 0;
int count = 0;
float avgCo2;
// ========================== AKHIR DEKLARASI VARIABEL UNTUK MENYIMPAN DATA SEBANYAK WINDOW SIZE =============================================================

// ========================== DEKLARASI VARIABEL KALIBRASI ===================================================================================================
float yCo2;
float awal_ukurCo2, awal_sensorCo2,
    akhir_ukurCo2, akhir_sensorCo2;
float aCo2;
float cCo2;
// ========================== AKHIR DEKLARASI VARIABEL KALIBRASI =============================================================================================

// ========================= DEKLARASI VARIABEL UNTUK UPDATE SESUAI INTERVAL =================================================================================
unsigned long previousMillis = 0;
const long interval = 1000;
// ========================= AKHIR DEKLARASI VARIABEL UNTUK UPDATE SESUAI INTERVAL ===========================================================================

// ========================= DEKLARASI OBJEK UNTUK MASING-MASING LIBRARY =====================================================================================
WiFiClientSecure espClient;
AsyncUDP udp;
// ========================= AKHIR DEKLARASI OBJEK ===========================================================================================================

void setup()
{
    // INISIALISASI SERIAL
    Serial.begin(115200); 
    
    // INISIALISASI WIFI
    setup_wifi();   

    // ESP32-specific ADC configuration
    analogSetWidth(12);                              // Set resolution to 12 bits
    analogSetAttenuation(ADC_11db);                  // Set attenuation for the full 3.3V range

    Serial.println("MG-811 Demonstration for ESP32");
    Serial.println("-------------------------------");
}

void loop()
{
    // DEKLARASI VARIABEL MILLIS SESUAI DENGAN WAKTU millis() SEKARANG
    unsigned long currentMillis = millis();

    // UPDATE PEMBACAAN SESUAI INTERVAL
    if(currentMillis - previousMillis >= interval){
        // UPDATE WAKTU TERAKHIR PEMBACAAN
        previousMillis = currentMillis; 

        // PANGGIL FUNGSI readCO2()
        readCO2();

        // PANGGIL FUNGSI proses()
        proses();

        // PANGGIL FUNGSI sendData()
        sendData();

        // PANGGIL FUNGSI displayMonitor()
        displayMonitor();
    }
}