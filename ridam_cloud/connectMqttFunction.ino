// ========================================= FUNGSI reconnect() UNTUK MENGKONEKSIKAN MQTT SAAT BELUM TERKONEKSI ==============================================
void reconnect() {
  int attempts = 0;

  // MENCOBA KONEKSI MQTT SAAT CLIENT BELUM TERKONEKSI 5 KALI
  while (!client.connected() && attempts < 5) {
    Serial.print("Connecting to MQTT...");

    // MENJAGA SISTEM TIDAK WATCHDOG RESET
    yield();
    
    // Create a unique client ID
    String clientId = "ESP32Receiver-";
    clientId += String(random(0xffff), HEX);
    
    // KONEKSIKAN BERDASARKAN clientId, mqtt_user DAN mqtt_password
    if (client.connect(clientId.c_str(), mqtt_user, mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds");
      // Print error details
      switch(client.state()) {
        case -4: Serial.println("Connection timeout"); break;
        case -3: Serial.println("Connection lost"); break;
        case -2: Serial.println("Connection failed"); break;
        case -1: Serial.println("Disconnected"); break;
        case 1: Serial.println("Bad protocol"); break;
        case 2: Serial.println("Bad client ID"); break;
        case 3: Serial.println("Server unavailable"); break;
        case 4: Serial.println("Bad credentials"); break;
        case 5: Serial.println("Unauthorized"); break;
      }
      attempts++;

      // MENCOBA KONEKSI MQTT SETIAP 5 DETIK SEKALI
      delay(5000);

      // MENJAGA SISTEM TIDAK WATCHDOG RESET
      yield();
    }
  }
}
// ==================================================== AKHIR FUNGSI reconnect() ============================================================================