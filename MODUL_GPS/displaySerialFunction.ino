/* 
 Nama File      : displaySerialFunction.ino
 Tanggal Update : 09 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
    1. Fungsi ini digunakan untuk menampilkan data GPS yang telah dibaca dari modul GPS ke Serial Monitor.
    2. Data yang ditampilkan meliputi latitude dan longitude.
*/

// =========================================== FUNGSI displaySerial() UNTUK MENAMPILKAN PEMBACAAN GPS =====================================================
void displaySerial() {
  // TAMPILKAN SUHU DAN KELEMBABAN KE SERIAL MONITOR
  Serial.print("Latitude: ");
  Serial.print(latData.data);
  Serial.print(" | Longitude: ");
  Serial.println(lonData.data);
}
// =========================================== AKHIR FUNGSI displaySerial() =================================================================================