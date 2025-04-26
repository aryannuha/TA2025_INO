// ==================================================== FUNGSI sendData() UNTUK KIRIM KE BERBAGAI MODUL DALAM FORMAT JSON ====================================
void sendData() {
  // MEMBUAT DOKUMEN JSON UNTUK SUHU INDOOR
  StaticJsonDocument<200> doc;
  doc["kodeModul"] = suhuData.kodeModul;
  doc["kodeVariabel"] = suhuData.kodeVariabel;
  doc["kodeData"] = suhuData.data;
  doc["kodeAlarm"] = suhuData.kodeAlarm;
  doc["berita"] = suhuData.berita;

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

  // DELAY 1 DETIK SEBELUM MENGIRIM JSON KELEMBABAN
  delay(1000);

  // BUAT DOKUMEN JSON UNTUK KELEMBABAN INDOOR
  StaticJsonDocument<200> doc1;
  doc1["kodeModul"] = kelembabanData.kodeModul;
  doc1["kodeVariabel"] = kelembabanData.kodeVariabel;
  doc1["kodeData"] = kelembabanData.data;
  doc1["kodeAlarm"] = kelembabanData.kodeAlarm;
  doc1["berita"] = kelembabanData.berita; // ArduinoJson tidak mendukung char langsung

  // SERIALIZE KE BUFFER
  char buffer1[256];
  size_t n1 = serializeJson(doc1, buffer1);

  // KIRIM KE BERBAGAI MODUL SESUAI DESTINASI IP MELALUI PROTOKOL KOMUNIKASI UDP
  udp.writeTo((const uint8_t*)buffer1, n1, destinationIP, 1234);
  udp.writeTo((const uint8_t*)buffer1, n1, destinationIP2, 1234);
  udp.writeTo((const uint8_t*)buffer1, n1, destinationIP3, 1234);
  udp.writeTo((const uint8_t*)buffer1, n1, destinationIP4, 1234);

  // MENAMPILKAN PAYLOAD
  Serial.print("Dikirim ke ");
  Serial.print(destinationIP);
  Serial.print(" ");
  Serial.print(destinationIP2);
  Serial.print(" ");
  Serial.print(destinationIP3);
  Serial.print(" ");
  Serial.println(destinationIP4);
  Serial.print("Payload1: ");
  Serial.println(buffer1);

  // DELAY 1 DETIK SEBELUM MENGIRIM JSON SUHU
  delay(1000);
}
// ============================================================ AKHIR FUNGSI sendData() =======================================================================

