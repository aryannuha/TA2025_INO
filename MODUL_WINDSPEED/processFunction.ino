/* 
 Nama File      : processFunction.ino
 Tanggal Update : 09 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
    1. Fungsi proses() digunakan untuk melakukan kalibrasi, filtrasi, menetapkan kode modul dan variabel, serta kondisi untuk alarm dan berita.
    2. Fungsi kalibrasi() digunakan untuk menghitung nilai kalibrasi Windspeed berdasarkan data awal dan akhir.
    3. Fungsi filtrasi() digunakan untuk menghitung rata-rata dari data Windspeed yang disimpan dalam buffer.
    4. Fungsi ini juga menetapkan kode modul dan variabel untuk Windspeed.
*/

// ========================================== FUNGSI proses() ===============================================================================================
void proses(){  
  // Panggil fungsi kalibrasi nilai pembacaan sensor
  // kalibrasi();

  // Store in circular buffer
  // windWindow[bufferIndex] = yWind;
  // bufferIndex = (bufferIndex + 1) % WINDOW_SIZE;

  // Track count of valid readings
  // if (count < WINDOW_SIZE) count++;

  // fungsi filtrasi hasil kalibrasi menggunakan MA
  // avgWind = filtrasi(windWindow, count); 

  // MENETAPKAN KODE MODUL DAN KODE VARIABEL
  windspeedData.kodeModul = "04";
  windspeedData.kodeVariabel = 11;
  // windspeedData.data = avgWind;

  // Panggil fungsi kondisi kodeAlarm
  kondisi();
}
// =================================================== AKHIR FUNGSI proses() ================================================================================

// ============================================== FUNGSI kalibrasi() ========================================================================================
void kalibrasi(){
  // perhitungan linearitas
  aWind = (akhir_ukurWind - akhir_sensorWind)/(awal_ukurWind - awal_sensorWind);

  // perhitungan kalibrasi
  yWind = aWind * windSpeed + cWind;
}
// ============================================== AKHIR FUNGSI kalibrasi() ==================================================================================

// ====================================================== FUNGSI filtrasi() =================================================================================
float filtrasi(float* data, int size){
  float sum = 0.0;
  for (int i = 0; i < size; i++) {
    sum += data[i];
  }
  return sum / size;
}
// ====================================================== AKHIR FUNGSI filtrasi() ===========================================================================