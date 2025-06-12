/* 
 Nama File      : connectWifiFunction.ino
 Tanggal Update : 09 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
    1. Fungsi ini digunakan untuk menghubungkan modul ke jaringan WiFi dengan IP statis.
    2. Fungsi ini akan mengkonfigurasi IP, gateway, subnet, dan DNS sesuai dengan parameter yang telah ditentukan.
*/

// ========================================= FUNGSI setup_wifi() UNTUK KONEKSI WIFI DAN KONFIGURASI JARINGAN ================================================
void setup_wifi() {
  // KONFIGURASI DARI PARAMETER JARINGAN
  if (WiFi.config(staticIP, gateway, subnet, dns, dns2) == false) {
    Serial.println("Configuration failed.");
  }
    
  // MULAI KONEKSI SESUAI SSID DAN PASSWORD
  WiFi.begin(ssid, password);
 
  // CEK STATUS KONEKSI
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("Connecting...\n\n");
  }
 
  // TAMPILKAN PARAMETER JARINGAN SAAT BERHASIL TERKONEKSI
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("Subnet Mask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway IP: ");
  Serial.println(WiFi.gatewayIP());
  Serial.print("DNS 1: ");
  Serial.println(WiFi.dnsIP(0));
  Serial.print("DNS 2: ");
  Serial.println(WiFi.dnsIP(1));
}
// ========================================= AKHIR FUNGSI setup_wifi() =======================================================================================