/* 
 Nama File      : alarmFunction.ino
 Tanggal Update : 09 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
    1. Fungsi kondisi() digunakan untuk menetapkan kode alarm dan berita berdasarkan data co2.
    2. Fungsi ini menggunakan beberapa variabel untuk menentukan kondisi co2.
    3. Kode alarm dan berita akan disimpan dalam structure co2Data.
    4. Fungsi ini akan dipanggil dalam fungsi proses() untuk menetapkan kondisi alarm dan berita.
*/

// ==================================================== FUNGSI kondisi() =====================================================================================
void kondisi(){
  // VARIABEL ALARM CO2
  int LL = 300;
  int L = 400;
  int N = 1000;
  int H = 1500;

  // KONDISI kodeAlarm DAN berita CO2
  if(co2Data.data < LL){
    co2Data.kodeAlarm = 1;
    co2Data.berita = "Ruang Greenhouse CO2 Terlalu Rendah";
  }else if(co2Data.data >= LL && co2Data.data < L){
    co2Data.kodeAlarm = 2;
    co2Data.berita = "Ruang Greenhouse CO2 Rendah";
  }else if(co2Data.data >= L && co2Data.data < N){
    co2Data.kodeAlarm = 0;
    co2Data.berita = "Ruang Greenhouse Optimal";
  }else if(co2Data.data >= N && co2Data.data < H){
    co2Data.kodeAlarm = 3;
    co2Data.berita = "Ruang Greenhouse CO2 Tinggi";
  }else{
    co2Data.kodeAlarm = 4;
    co2Data.berita = "Ruang Greenhouse CO2 Terlalu Tinggi";
  }
}
// ====================================================== AKHIR FUNGSI kondisi() ============================================================================