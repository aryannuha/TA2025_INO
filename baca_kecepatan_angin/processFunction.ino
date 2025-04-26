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

// ===================================================== FUNGSI kondisi() ===================================================================================
void kondisi(){
  // VARIABEL ALARM KECEPATAN ANGIN
  float LL = 0.5;
  float L = 2;
  float N = 5;
  float H = 10;

  // MENETAPKAN kodeAlarm DAN BERITA
  if(windspeedData.data < LL){
    windspeedData.kodeAlarm = 1;
    windspeedData.berita = "Kecepatan Angin Terlalu Rendah";
  }else if(windspeedData.data >= LL && windspeedData.data < L){
    windspeedData.kodeAlarm = 2;
    windspeedData.berita = "Kecepatan Angin Rendah";
  }else if(windspeedData.data >= L && windspeedData.data < N){
    windspeedData.kodeAlarm = 0;
    windspeedData.berita = "Kecepatan Angin Optimal";
  }else if(windspeedData.data >= N && windspeedData.data < H){
    windspeedData.kodeAlarm = 3;
    windspeedData.berita = "Kecepatan Angin Tinggi";
  }else{
    windspeedData.kodeAlarm = 4;
    windspeedData.berita = "Kecepatan Angin Terlalu Tinggi";
  }
}
// ================================================== AKHIR FUNGSI kondisi() ================================================================================