/* 
 Nama File      : alarmFunction.ino
 Tanggal Update : 09 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
    1. Fungsi kondisi() digunakan untuk menetapkan kode alarm dan berita berdasarkan data Rainfall.
    2. Fungsi ini menggunakan beberapa variabel untuk menentukan kondisi rainfall.
    3. Kode alarm dan berita akan disimpan dalam structure rainfallData.
    4. Fungsi ini akan dipanggil dalam fungsi proses() untuk menetapkan kondisi alarm dan berita.
*/

// =============================== FUNGSI kondisi() UNTUK ALARM DAN BERITA ===================================================================================
void kondisi(){
  // VARIABEL ALARM CURAH HUJAN
  int LL = 0.1;
  int L = 2.5;
  int N = 7.5;
  int H = 15;

  // KONDISI kodeAlarm DAN BERITA
  if(rainfallData.data < LL){
    rainfallData.kodeAlarm = 0;
    rainfallData.berita = "Curah Hujan Terlalu Rendah";
  }else if(rainfallData.data >= LL && rainfallData.data < L){
    rainfallData.kodeAlarm = 0;
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