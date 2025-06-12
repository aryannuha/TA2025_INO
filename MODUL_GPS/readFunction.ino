/* 
 Nama File      : readFunction.ino
 Tanggal Update : 09 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
    1. Fungsi ini digunakan untuk membaca data GPS dari modul GPS yang terhubung ke ESP32.
    2. Data yang dibaca meliputi latitude dan longitude.
    3. Data tersebut kemudian disimpan ke dalam struktur data yang telah didefinisikan sebelumnya.
*/

void bacaGPS() {
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

  if (gps.location.isUpdated()) {
    // Ambil dan simpan data GPS ke variabel
    lat = gps.location.lat();
    lon = gps.location.lng();
    // spd = gps.speed.kmph();
    // alt = gps.altitude.meters();
    // hdop = gps.hdop.value() / 100.0;
    // stl = gps.satellites.value();

    // Simpan data ke struct
    latData.data = lat;
    lonData.data = lon;
    // altData.data = alt;
    // spdData.data = spd;
    // hdopData.data = hdop;
    // stlData.data = stl;
  }
}
