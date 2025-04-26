// ========================================================== FUNGSI sendData() ==============================================================================
void sendData() {
 // MEMBUAT DOKUMEN JSON UNTUK CURAH HUJAN
  StaticJsonDocument<200> doc;
  doc["kodeModul"] = rainfallData.kodeModul;
  doc["kodeVariabel"] = rainfallData.kodeVariabel;
  doc["kodeData"] = rainfallData.data;
  doc["kodeAlarm"] = rainfallData.kodeAlarm;
  doc["berita"] = rainfallData.berita;

  // SERIALIZE KE BUFFER
  char buffer[256];
  size_t n = serializeJson(doc, buffer);

  // KIRIM KE BERBAGAI MODUL SESUAI DESTINASI IP MELALUI PROTOKOL KOMUNIKASI UDP
  udp.writeTo((const uint8_t*)buffer, n, destinationIP, 1234);
  udp.writeTo((const uint8_t*)buffer, n, destinationIP2, 1234);
  udp.writeTo((const uint8_t*)buffer, n, destinationIP3, 1234);
  udp.writeTo((const uint8_t*)buffer, n, destinationIP4, 1234);

  // MENAMPILKAN PAYLOAD
  Serial.print("Dikirim ke ");
  Serial.print(destinationIP);
  Serial.print(" ");
  Serial.print(destinationIP2);
  Serial.print(" ");
  Serial.print(destinationIP3);
  Serial.print(" ");
  Serial.println(destinationIP4);
  Serial.print("Payload: ");
  Serial.println(buffer);

  // delay(1000);
}
// =============================================================== AKHIR FUNGSI sendData() ===================================================================