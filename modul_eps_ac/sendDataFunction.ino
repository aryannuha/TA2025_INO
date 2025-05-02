// ==================================================== FUNGSI sendData() UNTUK KIRIM KE BERBAGAI MODUL DALAM FORMAT JSON ====================================
void sendData() {
  // MEMBUAT DOKUMEN JSON UNTUK Tegangan
  StaticJsonDocument<200> doc;
  doc["kodeModul"] = teganganData.kodeModul;
  doc["kodeVariabel"] = teganganData.kodeVariabel;
  doc["kodeData"] = teganganData.data;
  doc["kodeAlarm"] = teganganData.kodeAlarm;
  doc["berita"] = teganganData.berita;

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

  delay(1000);

  // MEMBUAT DOKUMEN JSON UNTUK ARUS
  StaticJsonDocument<200> doc1;
  doc1["kodeModul"] = arusData.kodeModul;
  doc1["kodeVariabel"] = arusData.kodeVariabel;
  doc1["kodeData"] = arusData.data;
  doc1["kodeAlarm"] = arusData.kodeAlarm;
  doc1["berita"] = arusData.berita;

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
  Serial.print("Payload: ");
  Serial.println(buffer1);

  delay(1000);

  // MEMBUAT DOKUMEN JSON UNTUK DAYA
  StaticJsonDocument<200> doc2;
  doc2["kodeModul"] = dayaData.kodeModul;
  doc2["kodeVariabel"] = dayaData.kodeVariabel;
  doc2["kodeData"] = dayaData.data;
  doc2["kodeAlarm"] = dayaData.kodeAlarm;
  doc2["berita"] = dayaData.berita;

  // SERIALIZE KE BUFFER
  char buffer2[256];
  size_t n2 = serializeJson(doc2, buffer2);

  // KIRIM KE BERBAGAI MODUL SESUAI DESTINASI IP MELALUI PROTOKOL KOMUNIKASI UDP
  udp.writeTo((const uint8_t*)buffer2, n2, destinationIP, 1234);
  udp.writeTo((const uint8_t*)buffer2, n2, destinationIP2, 1234);
  udp.writeTo((const uint8_t*)buffer2, n2, destinationIP3, 1234);
  udp.writeTo((const uint8_t*)buffer2, n2, destinationIP4, 1234);

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
  Serial.println(buffer2);

  delay(1000);
}
// ============================================================ AKHIR FUNGSI sendData() ======================================================================