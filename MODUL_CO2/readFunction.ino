/* 
 Nama File      : readFunction.ino
 Tanggal Update : 09 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
    1. Fungsi readCO2() digunakan untuk membaca nilai CO2 dari sensor SEN-000007 yang terhubung ke pin analog ESP32.
    2. Fungsi ini akan mengambil beberapa sampel dari pin analog, menghitung rata-ratanya, dan mengonversinya menjadi tegangan.
*/

/*****************************  MGRead *********************************************
Input:   mg_pin - analog channel
Output:  output of SEN-000007
Remarks: This function reads the output of SEN-000007
************************************************************************************/

// ============================================ FUNGSI readCO2() UNTUK MEMBACA TEGANGAN ADC YANG DIHASILKAN SENSOR ===========================================
void readCO2()
{
  int i;
  float v = 0;

  for (i = 0; i < READ_SAMPLE_TIMES; i++) {
    v += analogRead(MG_PIN);
    delay(READ_SAMPLE_INTERVAL);
  }
  v = (v / READ_SAMPLE_TIMES) * ADC_VOLTAGE / ADC_RESOLUTION;  // Convert to voltage using ESP32 specs
  volts = v;
}
// ============================================ AKHIR FUNGSI readCO2() ========================================================================================