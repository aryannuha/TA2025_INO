// ==================================================== FUNGSI sendData() UNTUK KIRIM KE BERBAGAI MODUL DALAM FORMAT JSON ====================================
void sendData() {
 // MEMBUAT DOKUMEN JSON UNTUK KECEPATAN ANGIN
  StaticJsonDocument<200> doc;
  doc["kodeModul"] = windspeedData.kodeModul;
  doc["kodeVariabel"] = windspeedData.kodeVariabel;
  doc["kodeData"] = windspeedData.data;
  doc["kodeAlarm"] = windspeedData.kodeAlarm;
  doc["berita"] = windspeedData.berita;

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
// ============================================================ AKHIR FUNGSI sendData() ======================================================================