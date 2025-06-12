/* 
 Nama File      : processFunction.ino
 Tanggal Update : 09 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
    1. Fungsi proses() digunakan untuk melakukan kalibrasi, filtrasi, menetapkan kode modul dan variabel, serta kondisi untuk alarm dan berita.
    2. Fungsi kalibrasi() digunakan untuk menghitung nilai kalibrasi suhu dan kelembaban berdasarkan data awal dan akhir.
    3. Fungsi filtrasi() digunakan untuk menghitung rata-rata dari data suhu dan kelembaban yang disimpan dalam buffer.
    4. Fungsi ini juga menetapkan kode modul dan variabel untuk suhu dan kelembaban indoor.
*/

// ======================== FUNGSI proses() UNTUK KALIBRASI, FILTRASI, MENETAPKAN KODE MODUL, MENETAPKAN KODE VARIABEL, ALARM, SERTA BERITA =================
void proses(){
  // PANGGIL FUNGSI kalibrasi()
  // kalibrasi();

  // SIMPAN PADA BUFFER FILTRASI
  // tempWindow[bufferIndex] = ySuhu;
  // humWindow[bufferIndex] = yKelembaban;
  // bufferIndex = (bufferIndex + 1) % WINDOW_SIZE;

  // MENYESUAIKAN JUMLAH DATA SESUAI WINDOW_SIZE
  // if (count < WINDOW_SIZE) count++;

  // MENYIMPAN HASIL FILTRASI PADA VARIABEL avgTemp DAN avgHUM
  // avgTemp = filtrasi(tempWindow, count); 
  // avgHum = filtrasi(humWindow, count); 

  // MENETAPKAN KODE MODUL DAN KODE VARIABEL UNTUK SUHU INDOOR
  suhuData.kodeModul = "02";
  suhuData.kodeVariabel = 11;
  // suhuData.data = avgTemp;

  // MENETAPKAN KODE MODUL DAN KODE VARIABEL UNTUK KELEMBABAN INDOOR
  kelembabanData.kodeModul = "02";
  kelembabanData.kodeVariabel = 12;
  // kelembabanData.data = avgHum;
  
  // PANGGIL FUNGSI kondisi() UNTUK ALARM
  kondisi();
}

// ================================================ FUNGSI KALIBRASI =========================================================================================
void kalibrasi(){
  // PERHITUNGAN LINEARITAS
  aSuhu = (akhir_ukurSuhu - akhir_sensorSuhu)/(awal_ukurSuhu - awal_sensorSuhu);
  aKelembaban = (akhir_ukurKelembaban - akhir_sensorKelembaban)/(awal_ukurKelembaban - awal_sensorKelembaban);

  // PERHITUNGAN KALIBRASI
  ySuhu = aSuhu * rawTemp + cSuhu;
  yKelembaban = aKelembaban * rawHumidity + cKelembaban;
}
// =============================================== AKHIR FUNGSI KALIBRASI ====================================================================================

// =============================================== FUNGSI FILTRASI ===========================================================================================
float filtrasi(float* data, int size){
  float sum = 0.0;
  for (int i = 0; i < size; i++) {
    sum += data[i];
  }
  return sum / size;
}
// ============================================== AKHIR FUNGSI FILTRASI ======================================================================================