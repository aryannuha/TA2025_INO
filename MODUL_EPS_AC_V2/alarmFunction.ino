/* 
 Nama File      : alarmFunction.ino
 Tanggal Update : 09 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
    1. Modul ini digunakan untuk mengatur fungsi alarm berdasarkan data yang dibaca dari PZEM-004T 10A yang sudah dikalibrasi.
    2. Modul ini akan menentukan kondisi alarm berdasarkan nilai tegangan, arus, dan daya yang dibaca.
    3. Modul ini akan mengirimkan kode alarm dan berita terkait kondisi alarm.
*/

// ===================================================== FUNGSI kondisi() ===================================================================================
void kondisi(){
  // VARIABEL ALARM TEGANGAN
  float LL_V = 198;
  float L_V = 201;
  float N_V = 240;
  float H_V = 242;

  // VARIABEL ALARM ARUS
  float LL_A = 1;
  float L_A = 2;
  float N_A = 4;
  float H_A = 8;

  // VARIABEL ALARM DAYA
  float LL_P = 1;
  float L_P = 3;
  float N_P = 5;
  float H_P = 10;

  // MENETAPKAN kodeAlarm DAN BERITA TEGANGAN
  if(teganganData.data < LL_V){
    teganganData.kodeAlarm = 0;
    teganganData.berita = "Tegangan Terlalu Rendah";
  }else if(teganganData.data >= LL_V && teganganData.data < L_V){
    teganganData.kodeAlarm = 0;
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
    arusData.kodeAlarm = 0;
    arusData.berita = "Arus Terlalu Rendah";
  }else if(arusData.data >= LL_A && arusData.data < L_A){
    arusData.kodeAlarm = 0;
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
    dayaData.kodeAlarm = 0;
    dayaData.berita = "Daya Terlalu Rendah";
  }else if(dayaData.data >= LL_P && dayaData.data < L_P){
    dayaData.kodeAlarm = 0;
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