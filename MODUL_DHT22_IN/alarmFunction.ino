/* 
 Nama File      : alarmFunction.ino
 Tanggal Update : 09 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
    1. Fungsi kondisi() digunakan untuk menetapkan kode alarm dan berita berdasarkan data suhu dan kelembaban indoor.
    2. Fungsi ini menggunakan beberapa variabel untuk menentukan kondisi suhu dan kelembaban indoor.
    3. Kode alarm dan berita akan disimpan dalam structure suhuData dan kelembabanData.
    4. Fungsi ini akan dipanggil dalam fungsi proses() untuk menetapkan kondisi alarm dan berita.
*/

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