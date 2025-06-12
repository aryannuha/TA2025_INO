/* 
 Nama File      : processFunction.ino
 Tanggal Update : 09 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
    1. Fungsi ini digunakan untuk memproses data GPS yang telah dibaca dari modul GPS.
    2. Data yang diproses meliputi latitude dan longitude.
*/

void proses(){

  latData.kodeModul = "10";
  latData.kodeVariabel = 11;
  
  lonData.kodeModul = "10";
  lonData.kodeVariabel = 12;
  
  // altData.kodeModul = "04";
  // altData.kodeVariabel = 13;

  // spdData.kodeModul = "04";
  // spdData.kodeVariabel = 14;
  
  // hdopData.kodeModul = "04";
  // hdopData.kodeVariabel = 15;

  // stlData.kodeModul = "04";
  // stlData.kodeVariabel = 16;
}