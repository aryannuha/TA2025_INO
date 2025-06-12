/* 
 Nama File      : alarmFunction.ino
 Tanggal Update : 09 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
    1. Fungsi kondisi() digunakan untuk menetapkan kode alarm dan berita berdasarkan data PAR.
    2. Fungsi ini menggunakan beberapa variabel untuk menentukan kondisi PAR.
    3. Kode alarm dan berita akan disimpan dalam structure parData.
    4. Fungsi ini akan dipanggil dalam fungsi proses() untuk menetapkan kondisi alarm dan berita.
*/

// ===================================================== FUNGSI kondisi() ===================================================================================
void kondisi(){
  // VARIABEL ALARM PAR
  float LL = 100;
  float L = 300;
  float N = 600;
  float H = 1500;

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