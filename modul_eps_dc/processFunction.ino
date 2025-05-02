// ========================================== FUNGSI proses() ===============================================================================================
void proses(){  
  // Panggil fungsi kalibrasi nilai pembacaan sensor
  kalibrasi();

  // Store in circular buffer
  // voltageWindow[bufferIndex] = voltage_kalibrasi;
  // currentWindow[bufferIndex] = current_kalibrasi;
  // powerWindow[bufferIndex] = power_kalibrasi;
  // bufferIndex = (bufferIndex + 1) % WINDOW_SIZE;

  // Track count of valid readings
  // if (count < WINDOW_SIZE) count++;

  // fungsi filtrasi hasil kalibrasi menggunakan MA
  // avgVoltage = filtrasi(voltageWindow, count); 
  // avgCurrent = filtrasi(currentWindow, count); 
  // avgPower = filtrasi(powerWindow, count); 

  // MENETAPKAN KODE MODUL DAN KODE VARIABEL
  teganganData.kodeModul = "08";
  teganganData.kodeVariabel = 11;

  arusData.kodeModul = "08";
  arusData.kodeVariabel = 12;

  dayaData.kodeModul = "08";
  dayaData.kodeVariabel = 13;
  // windspeedData.data = avgWind;

  // Panggil fungsi kondisi kodeAlarm
  kondisi();
}
// =================================================== AKHIR FUNGSI proses() ================================================================================

// ============================================== FUNGSI kalibrasi() ========================================================================================
void kalibrasi(){
  // perhitungan slope tegangan
  float a1 = (Vu2 - Vu1) / (Va2 - Va1);
  float c1 = Vu1 - (a1 * Va1);

  // perhitungan slope arus
  float a2 = (Cu2 - Cu1) / (Ca2 - Ca1);
  float c2 = Cu1 - (a2 * Ca1);

  // a dan c adalah rumus (y=ax +c)
  voltage_kalibrasi = (a1 * busVoltage) + c1;
  current_kalibrasi = (a2 * current) + c2;
  power_kalibrasi   = power   * 1.0;

  teganganData.data = voltage_kalibrasi;
  arusData.data = current_kalibrasi;
  dayaData.data = power_kalibrasi;
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
  // VARIABEL ALARM TEGANGAN
  float LL_V = 3;
  float L_V = 3.5;
  float N_V = 4.9;
  float H_V = 5.3;

  // VARIABEL ALARM ARUS
  float LL_A = 10;
  float L_A = 100;
  float N_A = 120;
  float H_A = 151;

  // VARIABEL ALARM DAYA
  float LL_P = 10;
  float L_P = 100;
  float N_P = 5;
  float H_P = 10;

  // MENETAPKAN kodeAlarm DAN BERITA TEGANGAN
  if(teganganData.data < LL_V){
    teganganData.kodeAlarm = 1;
    teganganData.berita = "Tegangan Terlalu Rendah";
  }else if(teganganData.data >= LL_V && teganganData.data < L_V){
    teganganData.kodeAlarm = 2;
    teganganData.berita = "Tegangan Rendah";
  }else if(teganganData.data >= L_V && teganganData.data < N_V){
    teganganData.kodeAlarm = 0;
    teganganData.berita = "Tegangan Optimal";
  }else if(teganganData.data >= N_V && teganganData.data < H_V){
    teganganData.kodeAlarm = 3;
    teganganData.berita = "Tegangan Tinggi";
  }else{
    teganganData.kodeAlarm = 4;
    teganganData.berita = "Tegangan Terlalu Tinggi";
  }

  // MENETAPKAN kodeAlarm DAN BERITA ARUS
  if(arusData.data < LL_A){
    arusData.kodeAlarm = 1;
    arusData.berita = "Arus Terlalu Rendah";
  }else if(arusData.data >= LL_A && arusData.data < L_A){
    arusData.kodeAlarm = 2;
    arusData.berita = "Arus Rendah";
  }else if(arusData.data >= L_A && arusData.data < N_A){
    arusData.kodeAlarm = 0;
    arusData.berita = "Arus Optimal";
  }else if(arusData.data >= N_A && arusData.data < H_A){
    arusData.kodeAlarm = 3;
    arusData.berita = "Arus Tinggi";
  }else{
    arusData.kodeAlarm = 4;
    arusData.berita = "Arus Terlalu Tinggi";
  }

  // MENETAPKAN kodeAlarm DAN BERITA DAYA
  if(dayaData.data < LL_P){
    dayaData.kodeAlarm = 1;
    dayaData.berita = "Daya Terlalu Rendah";
  }else if(dayaData.data >= LL_P && dayaData.data < L_P){
    dayaData.kodeAlarm = 2;
    dayaData.berita = "Daya Rendah";
  }else if(dayaData.data >= L_P && dayaData.data < N_P){
    dayaData.kodeAlarm = 0;
    dayaData.berita = "Daya Optimal";
  }else if(dayaData.data >= N_P && dayaData.data < H_A){
    dayaData.kodeAlarm = 3;
    dayaData.berita = "Daya Tinggi";
  }else{
    dayaData.kodeAlarm = 4;
    dayaData.berita = "Daya Terlalu Tinggi";
  }
}
// ================================================== AKHIR FUNGSI kondisi() ================================================================================