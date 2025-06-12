/* 
 Nama File      : readFunction.ino
 Tanggal Update : 09 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
    1. Fungsi readHujan() digunakan untuk membaca data curah hujan dari sensor tipping bucket.
    2. Fungsi ini akan menambahkan nilai rainfall setiap kali sensor tipping bucket terpicu.
*/

void hitung_curah_hujan()
{
  flag = true;
  lastTipTime = millis(); // catat waktu tipping terakhir
}

// ==================================================== FUNGSI readHujan() ===================================================================================
void readHujan(){
  if (flag == true) // don't really need the == true but makes intent clear for new users
  {
    rainfall += milimeter_per_tip; // Akan bertambah nilainya saat tip penuh
    jumlah_tip++;
    delay(500);
    flag = false; // reset flag
  }
  rainfall = jumlah_tip * milimeter_per_tip;
  if ((jumlah_tip != temp_jumlah_tip)) // Print serial setiap 1 menit atau ketika jumlah_tip berubah
  {
    displaySerial();
  }
  temp_jumlah_tip = jumlah_tip;

  // Reset jika sudah lewat 10 menit sejak tip terakhir
  if (millis() - lastTipTime > hujanTimeout && millis() - lastCheck > 1000) {
    jumlah_tip = 0;
    rainfall = 0;
    displaySerial(); // tampilkan reset
    lastCheck = millis();
  }
}
// =================================================== AKHIR FUNGSI readHujan() ==============================================================================