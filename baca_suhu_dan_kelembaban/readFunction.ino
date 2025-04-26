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