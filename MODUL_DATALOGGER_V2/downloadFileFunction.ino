/*
 Nama File      : downloadFileFunction.ino
 Tanggal Update : 12 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
   1. Fungsi ini menangani permintaan untuk mengunduh file CSV dari SD Card.
   2. Fungsi ini membuka file log.csv dan mengirimkannya sebagai respons HTTP.
   3. Jika file tidak ditemukan, fungsi ini mengirimkan respons 404.
   4. Fungsi ini juga menyediakan halaman web untuk mengakses data dan mengunduh file CSV.
   5. Fungsi ini menggunakan library SD untuk berkomunikasi dengan SD Card dan WebServer untuk menangani permintaan HTTP.
   6. Fungsi ini juga menangani permintaan untuk mengakses data melalui API lokal.
   7. Fungsi ini mengirimkan header CORS agar bisa diakses oleh JavaScript dari domain lain.
   8. Fungsi ini mengirimkan file CSV sebagai teks biasa.
*/

void handleRoot() {
  String html = "<!DOCTYPE html><html><head><title>ESP32 Data Logger</title></head><body>";
  html += "<h1>ESP32 Data Logger Aktif</h1>";
  html += "<p>Gunakan endpoint <code>/data</code> untuk mengambil CSV atau <code>/download</code> untuk mengunduh.</p>";
  html += "<a href='/download'><button>Download CSV</button></a>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleDownload() {
  File file = SD.open("/log.csv");
  if (!file) {
    server.send(404, "text/plain", "File CSV tidak ditemukan");
    return;
  }

  server.streamFile(file, "text/csv");
  file.close();
}

// *** FUNGSI BARU UNTUK API DASBOR LOKAL ***
// Handler ini mengirimkan isi file CSV sebagai teks biasa
// dan menyertakan header CORS agar bisa diakses oleh JavaScript dari domain lain.
void handleApiData() {
  File file = SD.open(filename);
  if (!file) {
    server.send(404, "text/plain", "File not found");
    return;
  }
  
  // Header ini PENTING! Mengizinkan dasbor lokal Anda untuk meminta data.
  server.sendHeader("Access-Control-Allow-Origin", "*");
  
  // Kirim file sebagai teks
  server.streamFile(file, "text/csv");
  
  file.close();
}