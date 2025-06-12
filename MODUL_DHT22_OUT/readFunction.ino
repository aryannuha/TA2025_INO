/* 
 Nama File      : readFunction.ino
 Tanggal Update : 09 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
    1. Fungsi readDHT() digunakan untuk membaca data suhu dan kelembaban dari sensor DHT22.
    2. Data yang dibaca akan disimpan dalam variabel rawTemp dan rawHumidity.
    3. Data suhu dan kelembaban akan dimasukkan ke dalam structure suhuData dan kelembabanData.
*/

// =============================================== FUNGSI readDHT() UNTUK MEMBACA SUHU DAN KELEMBABAN UDARA ==================================================
void readDHT() {
  // MASUKKAN SUHU PADA VARIABEL rawTemp
  rawTemp = dht.readTemperature();

  // MASUKKAN KELEMBABAN PADA VARIABEL rawHumidity
  rawHumidity = dht.readHumidity();       

  // MASUKKAN SUHU DAN KELEMBABAN PADA STRUCTURE
  suhuData.data = rawTemp;
  kelembabanData.data = rawHumidity;
}
// =============================================== AKHIR FUNGSI readDHT() ====================================================================================