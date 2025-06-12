/* 
 Nama File      : readFunction.ino
 Tanggal Update : 09 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
    1. Fungsi ini digunakan untuk membaca data yang dikirim oleh WSN (Wireless Sensor Network) dalam format JSON melalui protokol UDP.
    2. Data yang diterima kemudian diparsing dan disimpan pada struktur data yang telah didefinisikan.
*/

// ======================================== FUNGSI read() UNTUK MEMBACA DATA YANG DIKIRIM WSN DALAM FORMAT JSON ============================================
void read(){
 if (udp.listen(1234)) {
    Serial.print("UDP listening on port ");
    Serial.println(1234);

    // Configure UDP packet handler
    udp.onPacket([](AsyncUDPPacket packet) {
      packetsReceived++;
      
      // Ensure we have a null-terminated string
      char* buffer = (char*)malloc(packet.length() + 1);
      if (!buffer) {
        Serial.println("Memory allocation failed for UDP packet");
        return;
      }
      
      memcpy(buffer, packet.data(), packet.length());
      buffer[packet.length()] = '\0';
      
      // Process the packet
      bool processed = parsing(buffer);
      if (processed) {
        packetsProcessed++;
        dataBaruTersedia = true;
      }
      
      // Cleanup
      free(buffer);
    });
  } else {
    Serial.println("Failed to start UDP listener!");
  }
}
// ===================================================== AKHIR FUNGSI read() ==============================================================================

// Fungsi inisialisasi data matrix
void initializeDataMatrix() {
  for (int i = 0; i < MAX_MODULES; i++) {
    moduleNames[i] = "";
    for (int j = 0; j < MAX_VARIABLES_PER_MODULE; j++) {
      dataMatrix[i][j].kodeModul = "";
      dataMatrix[i][j].kodeVariabel = -1;
      dataMatrix[i][j].kodeData = 0.0;
      dataMatrix[i][j].kodeAlarm = 0;
      dataMatrix[i][j].berita = "";
    }
  }
}