/* 
 Nama File      : processFunction.ino
 Tanggal Update : 09 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
    1. Fungsi ini digunakan untuk memproses data yang dibaca dari PZEM-004T 10A yang sudah dikalibrasi.
    2. Fungsi ini akan melakukan kalibrasi data, menyimpan data dalam buffer, dan mengirimkan data ke IP tujuan.
    3. Fungsi ini juga akan melakukan filtrasi data menggunakan simple moving average jika dibutuhkan.
    4. Fungsi ini akan mengupdate kode modul dan kode variabel untuk setiap data yang dikirimkan.
    5. Fungsi ini akan memanggil fungsi kondisi untuk menentukan apakah ada alarm yang perlu dikirimkan.
*/

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
  teganganData.kodeModul = "09";
  teganganData.kodeVariabel = 11;

  arusData.kodeModul = "09";
  arusData.kodeVariabel = 12;

  dayaData.kodeModul = "09";
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
  voltage_kalibrasi = (a1 * rawVoltage) + c1;
  current_kalibrasi = (a2 * rawCurrent) + c2;
  power_kalibrasi   = rawPower   * 1.0;

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