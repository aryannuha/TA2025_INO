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

// =============================== FUNGSI kondisi() UNTUK ALARM DAN BERITA ===================================================================================
void kondisi(){
  // VARIABEL ALARM CURAH HUJAN
  int LL = 0.1;
  int L = 2.5;
  int N = 7.5;
  int H = 15;

  // KONDISI kodeAlarm DAN BERITA
  if(rainfallData.data < LL){
    rainfallData.kodeAlarm = 1;
    rainfallData.berita = "Curah Hujan Terlalu Rendah";
  }else if(rainfallData.data >= LL && rainfallData.data < L){
    rainfallData.kodeAlarm = 2;
    rainfallData.berita = "Curah Hujan Rendah";
  }else if(rainfallData.data >= L && rainfallData.data < N){
    rainfallData.kodeAlarm = 0;
    rainfallData.berita = "Curah Hujan Optimal";
  }else if(rainfallData.data >= N && rainfallData.data < H){
    rainfallData.kodeAlarm = 3;
    rainfallData.berita = "Curah Hujan Tinggi";
  }else{
    rainfallData.kodeAlarm = 4;
    rainfallData.berita = "Curah Hujan Terlalu Tinggi";
  }
}
// ========================================================= AKHIR FUNGSI kondisi() ==========================================================================