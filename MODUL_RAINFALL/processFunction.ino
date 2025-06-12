/* 
 Nama File      : processFunction.ino
 Tanggal Update : 09 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
    1. Fungsi proses() digunakan untuk melakukan kalibrasi, filtrasi, menetapkan kode modul dan variabel, serta kondisi untuk alarm dan berita.
    2. Fungsi kalibrasi() digunakan untuk menghitung nilai kalibrasi rainfall berdasarkan data awal dan akhir.
    3. Fungsi filtrasi() digunakan untuk menghitung rata-rata dari data rainfall yang disimpan dalam buffer.
    4. Fungsi ini juga menetapkan kode modul dan variabel untuk rainfall.
*/

// =================== FUNGSI proses() UNTUK KALIBRASI DAN FILTRASI JIKA DIBUTUHKAN JUGA UNTUK MENETAPKAN ALARM, KODE MODUL, DAN KODE VARIABEL ===============
void proses(){
  // PANGGIL FUNGSI kalibrasi()
  // kalibrasi();

  // Store in circular buffer
  // rainfallWindow[bufferIndex] = yRainfall;
  // bufferIndex = (bufferIndex + 1) % WINDOW_SIZE;

  // Track count of valid readings
  // if (count < WINDOW_SIZE) count++;

  // fungsi filtrasi hasil kalibrasi menggunakan MA
  // avgRainfall = filtrasi(rainfallWindow, count); 

  // MENETAPKAN KODE MODUL DAN KODE VARIABEL
  rainfallData.kodeModul = "05";
  rainfallData.kodeVariabel = 11;
  rainfallData.data = rainfall;
  // rainfallData.data = avgRainfall;

  // fungsi kondisi kodeAlarm
  kondisi();
}
// ================================================== AKHIR FUNGSI proses() ==================================================================================

// ========================================================= FUNGSI kalibrasi() ==============================================================================
void kalibrasi(){
  // perhitungan linearitas
  aRainfall = (akhir_ukurRainfall - akhir_sensorRainfall)/(awal_ukurRainfall - awal_sensorRainfall);

  // perhitungan kalibrasi
  yRainfall = aRainfall * rainfall + cRainfall;
}
// ===================================================== AKHIR FUNGSI kalibrasi() ============================================================================

// ===================================================== FUNGSI filtrasi() ===================================================================================
float filtrasi(float* data, int size){
  float sum = 0.0;
  for (int i = 0; i < size; i++) {
    sum += data[i];
  }
  return sum / size;
}
// ===================================================== AKHIR FUNGSI filtrasi() =============================================================================