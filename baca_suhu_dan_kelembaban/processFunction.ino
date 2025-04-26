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

// ============================================== FUNGSI kondisi() UNTUK MENETAPKAN KODE ALARM DAN BERITA ====================================================
void kondisi(){
  // VARIABEL ALARM UNTUK SUHU INDOOR
  int LL_S = 15;
  int L_S = 20;
  int N_S = 30;
  int H_S = 35;

  // VARIABEL ALARM UNTUK KELEMBABAN INDOOR
  int LL_K = 40;
  int L_K = 50;
  int N_K = 70;
  int H_K = 85;

  // KONDISI kodeAlarm SUHU INDOOR
  if(suhuData.data < LL_S){
    suhuData.kodeAlarm = 1;
    suhuData.berita = "Ruang Greenhouse Terlalu Dingin";
  }else if(suhuData.data >= LL_S && suhuData.data < L_S){
    suhuData.kodeAlarm = 2;
    suhuData.berita = "Ruang Greenhouse Dingin";
  }else if(suhuData.data >= L_S && suhuData.data < N_S){
    suhuData.kodeAlarm = 0;
    suhuData.berita = "Ruang Greenhouse Optimal";
  }else if(suhuData.data >= N_S && suhuData.data < H_S){
    suhuData.kodeAlarm = 3;
    suhuData.berita = "Ruang Greenhouse Panas";
  }else{
    suhuData.kodeAlarm = 4;
    suhuData.berita = "Ruang Greenhouse Terlalu Panas";
  }

  // KONDISI kodeAlarm KELEMBABAN INDOOR
  if(kelembabanData.data < LL_K){
    kelembabanData.kodeAlarm = 1;
    kelembabanData.berita = "Ruang Greenhouse Terlalu Kering";
  }else if(kelembabanData.data >= LL_K && kelembabanData.data < L_K){
    kelembabanData.kodeAlarm = 2;
    kelembabanData.berita = "Ruang Greenhouse Kering";
  }else if(kelembabanData.data >= L_K && kelembabanData.data < N_K){
    kelembabanData.kodeAlarm = 0;
    kelembabanData.berita = "Ruang Greenhouse Optimal";
  }else if(kelembabanData.data >= N_K && kelembabanData.data < H_K){
    kelembabanData.kodeAlarm = 3;
    kelembabanData.berita = "Ruang Greenhouse Lembab";
  }else{
    kelembabanData.kodeAlarm = 4;
    kelembabanData.berita = "Ruang Greenhouse Terlalu Lembab";
  }
}
// ======================================================== AKHIR FUNGSI kondisi() ===========================================================================