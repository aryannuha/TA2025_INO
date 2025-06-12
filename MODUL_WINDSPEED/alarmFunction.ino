/* 
 Nama File      : alarmFunction.ino
 Tanggal Update : 09 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
    1. Fungsi kondisi() digunakan untuk menetapkan kode alarm dan berita berdasarkan data windspeed.
    2. Fungsi ini menggunakan beberapa variabel untuk menentukan kondisi windspeed.
    3. Kode alarm dan berita akan disimpan dalam structure windspeedData.
    4. Fungsi ini akan dipanggil dalam fungsi proses() untuk menetapkan kondisi alarm dan berita.
*/

// ===================================================== FUNGSI kondisi() ===================================================================================
void kondisi(){
  // VARIABEL ALARM KECEPATAN ANGIN
  float LL = 0.5;
  float L = 2;
  float N = 5;
  float H = 10;

  // MENETAPKAN kodeAlarm DAN BERITA
  if(windspeedData.data < LL){
    windspeedData.kodeAlarm = 0;
    windspeedData.berita = "Kecepatan Angin Terlalu Rendah";
  }else if(windspeedData.data >= LL && windspeedData.data < L){
    windspeedData.kodeAlarm = 0;
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