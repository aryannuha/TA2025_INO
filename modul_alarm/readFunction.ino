// ======================================== FUNGSI read() UNTUK MEMBACA DATA YANG DIKIRIM WSN DALAM FORMAT JSON ============================================
void read(){
  // LISTENING KE PORT 1234 UDP HARUS SESUAI DENGAN PORT WSN DAN MODUL LAIN UNTUK BISA SALING TERKONEKSI
  if (udp.listen(1234)) {
    // TAMPILKAN TULISAN DI SERIAL MONITOR KETIKA BERHASIL LISTENING
    Serial.println("UDP listening on port 1234");

    // BACA DATA YANG DIKIRIM
    udp.onPacket([](AsyncUDPPacket packet) {
      // Create a proper buffer with null termination
      char* nullTerminatedData = (char*)malloc(packet.length() + 1);
      if (nullTerminatedData) {
        memcpy(nullTerminatedData, packet.data(), packet.length());
        nullTerminatedData[packet.length()] = '\0';
        
        // Use a larger StaticJsonDocument
        StaticJsonDocument<512> doc;
        
        // Clear any previous data
        doc.clear();
        
        DeserializationError error = deserializeJson(doc, nullTerminatedData);
        
        if (!error) {
          // Store in the struct
          kodeModul_R = doc["kodeModul"].as<String>();
          kodeVariabel_R = doc["kodeVariabel"].as<int>();
          data_R = doc["kodeData"].as<float>();
          kodeAlarm_R = doc["kodeAlarm"].as<int>();
          berita_R = doc["berita"].as<String>();
          
          // Set flag for new data
          dataBaruTersedia = true;
          
          // // Debug print
          // Serial.println("\n-- UDP Packet Received --");
          // Serial.printf("From %s:%u\n", packet.remoteIP().toString().c_str(), packet.remotePort());
          // Serial.printf("Nama sensor: %s\n", namaSensor_R.c_str());
          // Serial.printf("Kode Modul: %d\n", kodeModul_R);
          // Serial.printf("Kode Variabel: %d\n", kodeVariabel_R);
          // Serial.printf("Data: %.3f\n", data_R);
          // Serial.printf("typeChar: %s\n", tesChar.c_str());
          // Serial.printf("typeBool: %s\n", tesBool ? "true" : "false");
        } else {
          Serial.print("JSON parse error: ");
          Serial.println(error.c_str());
          Serial.println("Raw data:");
          Serial.println(nullTerminatedData);
        }
        // Free the allocated memory
        free(nullTerminatedData);
      } else {
        Serial.println("Memory allocation failed");
      }
    });
  } else {
    Serial.println("Failed to start UDP listener!");
  }
}
// ===================================================== AKHIR FUNGSI read() ==============================================================================