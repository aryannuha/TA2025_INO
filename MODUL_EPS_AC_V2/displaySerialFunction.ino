/* 
 Nama File      : displaySerialFunction.ino
 Tanggal Update : 09 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
    1. Fungsi ini digunakan untuk menampilkan data pembacaan PZEM-004T 10A yang sudah dikalibrasi di serial monitor.
    2. Fungsi ini akan menampilkan tegangan, arus, dan daya yang sudah dikalibrasi.
*/

void displaySerial(){
  Serial.println("== Pembacaan INA219 ==");
  Serial.print("Tegangan Bus   : "); Serial.print(voltage_kalibrasi); Serial.println(" V");
  Serial.print("Arus           : "); Serial.print(current_kalibrasi); Serial.println(" A");
  Serial.print("Daya           : "); Serial.print(power_kalibrasi); Serial.println(" W");
  Serial.println();
}