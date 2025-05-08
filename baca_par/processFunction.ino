// ========================================== FUNGSI proses() ===============================================================================================
void proses(){  
  // Panggil fungsi kalibrasi nilai pembacaan sensor
  // kalibrasi();

  // Store in circular buffer
  // parWindow[bufferIndex] = yPar;
  // bufferIndex = (bufferIndex + 1) % WINDOW_SIZE;

  // Track count of valid readings
  // if (count < WINDOW_SIZE) count++;

  // fungsi filtrasi hasil kalibrasi menggunakan MA
  // avgPar = filtrasi(parWindow, count); 

  // MENETAPKAN KODE MODUL DAN KODE VARIABEL
  parData.kodeModul = "06";
  parData.kodeVariabel = 11;
  // windspeedData.data = avgWind;

  // Panggil fungsi kondisi kodeAlarm
  kondisi();
}
// =================================================== AKHIR FUNGSI proses() ================================================================================

// ============================================== FUNGSI kalibrasi() ========================================================================================
void kalibrasi(){
  // perhitungan linearitas
  aPar = (akhir_ukurPar - akhir_sensorPar)/(awal_ukurPar - awal_sensorPar);

  // perhitungan kalibrasi
  yPar = aPar * parValue + cPar;
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

// ===================================================== FUNGSI kondisi() ===================================================================================
void kondisi(){
  // VARIABEL ALARM PAR
  float LL = 100;
  float L = 300;
  float N = 600;
  float H = 1000;

  // MENETAPKAN kodeAlarm DAN BERITA
  if(parData.data < LL){
    parData.kodeAlarm = 1;
    parData.berita = "PAR Terlalu Rendah";
  }else if(parData.data >= LL && parData.data < L){
    parData.kodeAlarm = 2;
    parData.berita = "PAR Rendah";
  }else if(parData.data >= L && parData.data < N){
    parData.kodeAlarm = 0;
    parData.berita = "PAR Optimal";
  }else if(parData.data >= N && parData.data < H){
    parData.kodeAlarm = 3;
    parData.berita = "PAR Tinggi";
  }else{
    parData.kodeAlarm = 4;
    parData.berita = "PAR Terlalu Tinggi";
  }
}
// ================================================== AKHIR FUNGSI kondisi() ================================================================================