/* 
 Nama File      : connectWifiFunction.ino
 Tanggal Update : 09 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
    1. Fungsi ini digunakan untuk menginisialisasi koneksi WiFi dengan IP static, gateway, subnet, primary DNS, dan secondary DNS.
    2. Fungsi ini juga digunakan untuk menginisialisasi koneksi WiFi dengan SSID dan password yang telah ditentukan.
    3. Fungsi ini akan menampilkan informasi jaringan seperti Local IP, Subnet Mask, Gateway IP, DNS 1, dan DNS 2 pada Serial Monitor.
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