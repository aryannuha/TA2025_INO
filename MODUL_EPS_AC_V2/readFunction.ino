/* 
 Nama File      : readFunction.ino
 Tanggal Update : 09 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
    1. Fungsi ini digunakan untuk membaca data dari PZEM-004T 10A yang sudah dikalibrasi.
    2. Fungsi ini akan mengupdate variabel global rawVoltage, rawCurrent, dan rawPower dengan data yang dibaca dari PZEM-004T.
*/

void readPzem(){
  rawVoltage = pzem.voltage();
  rawCurrent = pzem.current();
  rawPower   = pzem.power();
}