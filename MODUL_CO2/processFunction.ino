/* 
 Nama File      : processFunction.ino
 Tanggal Update : 09 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
    1. Fungsi proses() digunakan untuk melakukan kalibrasi, filtrasi, menetapkan kode modul dan variabel, serta kondisi untuk alarm dan berita.
    2. Fungsi kalibrasi() digunakan untuk menghitung nilai kalibrasi CO2 berdasarkan data awal dan akhir.
    3. Fungsi filtrasi() digunakan untuk menghitung rata-rata dari data CO2 yang disimpan dalam buffer.
    4. Fungsi ini juga menetapkan kode modul dan variabel untuk CO2.
*/

/*****************************  MQGetPercentage **********************************
Input:   volts   - SEN-000007 output measured in volts
         pcurve  - pointer to the curve of the target gas
Output:  ppm of the target gas
Remarks: By using the slope and a point of the line. The x(logarithmic value of ppm)
         of the line could be derived if y(MG-811 output) is provided. As it is a
         logarithmic coordinate, power of 10 is used to convert the result to non-logarithmic
         value.
************************************************************************************/

// =============================== FUNGSI proses() MENGUBAH TEGANGAN MENJADI PPM, TERSEDIA KALIBRASI DAN FILTRASI ============================================
void proses()
{
  // if ((volts / DC_GAIN) >= ZERO_POINT_VOLTAGE) {
  //   return -1;
  // } else {
  rawCO2 = pow(10, ((volts / DC_GAIN) - CO2Curve[1]) / CO2Curve[2] + CO2Curve[0]);

  // PANGGIL FUNGSI kalibrasi()
  // kalibrasi();

  // Store in circular buffer
  // co2Window[bufferIndex] = yCo2;
  // bufferIndex = (bufferIndex + 1) % WINDOW_SIZE;

  // Track count of valid readings
  // if (count < WINDOW_SIZE) count++;

  // MENYIMPAN HASIL FILTRASI PADA VARIABEL avgCo2
  // avgCo2 = filtrasi(co2Window, count); 

  // MENETAPKAN KODE MODUL DAN KODE VARIABEL SERTA MEMASUKKAN HASIL KONVERSI TEGANGAN MENJADI PPM
  co2Data.kodeModul = "03";
  co2Data.kodeVariabel = 11;
  co2Data.data = (float)rawCO2;
  // co2Data.dataCO2 = avgCo2;

  // PANGGIL FUNGSI kondisi() UNTUK MENETAPKAN KODE ALARM DAN BERITA
  kondisi();
}
// ================================================================ AKHIR FUNGSI proses() ====================================================================

// ============================================================ FUNGSI KALIBRASI CO2 =========================================================================
void kalibrasi(){
  // perhitungan linearitas
  aCo2 = (akhir_ukurCo2 - akhir_sensorCo2)/(awal_ukurCo2 - awal_sensorCo2);

  // perhitungan kalibrasi
  yCo2 = aCo2 * rawCO2 + cCo2;
}
// ======================================================== AKHIR FUNGSI kalibrasi() CO2 =====================================================================

// ===================================================== FUNGSI FILTRASI =====================================================================================
float filtrasi(float* data, int size){
  float sum = 0.0;
  for (int i = 0; i < size; i++) {
    sum += data[i];
  }
  return sum / size;
}
// ======================================================= AKHIR FUNGSI filtrasi() ===========================================================================