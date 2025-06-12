/* 
 Nama File      : sendDataFunction.ino
 Tanggal Update : 09 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
    1. Fungsi sendData() digunakan untuk mengirim data rainfall dalam format JSON ke beberapa tujuan melalui protokol UDP.
    2. Data yang dikirim meliputi kode modul, kode variabel, data, kode alarm, dan berita.
    3. Fungsi ini juga mengirimkan prediksi rainfall untuk periode waktu t+1 t+2, t+3, t+4, dan t+5.
    4. Fungsi ini menggunakan library ArduinoJson untuk membuat dan mengirim data dalam format JSON.
*/

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

// BUAT DOKUMEN JSON UNTUK prediksi 1 menit ke depan rainfall
  StaticJsonDocument<200> doc1;
  doc1["kodeModul"] = rainfallData.kodeModul;
  doc1["kodeVariabel"] = 12;
  doc1["kodeData"] = predicted_value[0];
  doc1["kodeAlarm"] = 0;
  doc1["berita"] = "Prediksi t+1"; // ArduinoJson tidak mendukung char langsung

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

  // DELAY 1 DETIK SEBELUM MENGIRIM JSON rainfall
  delay(50);

  // BUAT DOKUMEN JSON UNTUK prediksi 2 menit ke depan rainfall
  StaticJsonDocument<200> doc2;
  doc2["kodeModul"] = rainfallData.kodeModul;
  doc2["kodeVariabel"] = 13;
  doc2["kodeData"] = predicted_value[1];
  doc2["kodeAlarm"] = 0;
  doc2["berita"] = "Prediksi t+2"; // ArduinoJson tidak mendukung char langsung

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
  Serial.print("Payload2: ");
  Serial.println(buffer2);

  // DELAY 1 DETIK SEBELUM MENGIRIM JSON rainfall
  delay(50);

  // BUAT DOKUMEN JSON UNTUK prediksi 3 menit ke depan rainfall
  StaticJsonDocument<200> doc3;
  doc3["kodeModul"] = rainfallData.kodeModul;
  doc3["kodeVariabel"] = 14;
  doc3["kodeData"] = predicted_value[2];
  doc3["kodeAlarm"] = 0;
  doc3["berita"] = "Prediksi t+3"; // ArduinoJson tidak mendukung char langsung

  // SERIALIZE KE BUFFER
  char buffer3[256];
  size_t n3 = serializeJson(doc3, buffer3);

  // KIRIM KE BERBAGAI MODUL SESUAI DESTINASI IP MELALUI PROTOKOL KOMUNIKASI UDP
  udp.writeTo((const uint8_t*)buffer3, n3, destinationIP, 1234);
  udp.writeTo((const uint8_t*)buffer3, n3, destinationIP2, 1234);
  udp.writeTo((const uint8_t*)buffer3, n3, destinationIP3, 1234);
  udp.writeTo((const uint8_t*)buffer3, n3, destinationIP4, 1234);

  // MENAMPILKAN PAYLOAD
  Serial.print("Dikirim ke ");
  Serial.print(destinationIP);
  Serial.print(" ");
  Serial.print(destinationIP2);
  Serial.print(" ");
  Serial.print(destinationIP3);
  Serial.print(" ");
  Serial.println(destinationIP4);
  Serial.print("Payload3: ");
  Serial.println(buffer3);

  // DELAY 1 DETIK SEBELUM MENGIRIM JSON rainfall
  delay(50);

  // BUAT DOKUMEN JSON UNTUK prediksi 4 menit ke depan rainfall
  StaticJsonDocument<200> doc4;
  doc4["kodeModul"] = rainfallData.kodeModul;
  doc4["kodeVariabel"] = 15;
  doc4["kodeData"] = predicted_value[3];
  doc4["kodeAlarm"] = 0;
  doc4["berita"] = "Prediksi t+4"; // ArduinoJson tidak mendukung char langsung

  // SERIALIZE KE BUFFER
  char buffer4[256];
  size_t n4 = serializeJson(doc4, buffer4);

  // KIRIM KE BERBAGAI MODUL SESUAI DESTINASI IP MELALUI PROTOKOL KOMUNIKASI UDP
  udp.writeTo((const uint8_t*)buffer4, n4, destinationIP, 1234);
  udp.writeTo((const uint8_t*)buffer4, n4, destinationIP2, 1234);
  udp.writeTo((const uint8_t*)buffer4, n4, destinationIP3, 1234);
  udp.writeTo((const uint8_t*)buffer4, n4, destinationIP4, 1234);

  // MENAMPILKAN PAYLOAD
  Serial.print("Dikirim ke ");
  Serial.print(destinationIP);
  Serial.print(" ");
  Serial.print(destinationIP2);
  Serial.print(" ");
  Serial.print(destinationIP3);
  Serial.print(" ");
  Serial.println(destinationIP4);
  Serial.print("Payload4: ");
  Serial.println(buffer4);

  // DELAY 1 DETIK SEBELUM MENGIRIM JSON rainfall
  delay(50);

  // BUAT DOKUMEN JSON UNTUK prediksi 5 menit ke depan rainfall
  StaticJsonDocument<200> doc5;
  doc5["kodeModul"] = rainfallData.kodeModul;
  doc5["kodeVariabel"] = 16;
  doc5["kodeData"] = predicted_value[4];
  doc5["kodeAlarm"] = 0;
  doc5["berita"] = "Prediksi t+5"; // ArduinoJson tidak mendukung char langsung

  // SERIALIZE KE BUFFER
  char buffer5[256];
  size_t n5 = serializeJson(doc5, buffer5);

  // KIRIM KE BERBAGAI MODUL SESUAI DESTINASI IP MELALUI PROTOKOL KOMUNIKASI UDP
  udp.writeTo((const uint8_t*)buffer5, n5, destinationIP, 1234);
  udp.writeTo((const uint8_t*)buffer5, n5, destinationIP2, 1234);
  udp.writeTo((const uint8_t*)buffer5, n5, destinationIP3, 1234);
  udp.writeTo((const uint8_t*)buffer5, n5, destinationIP4, 1234);

  // MENAMPILKAN PAYLOAD
  Serial.print("Dikirim ke ");
  Serial.print(destinationIP);
  Serial.print(" ");
  Serial.print(destinationIP2);
  Serial.print(" ");
  Serial.print(destinationIP3);
  Serial.print(" ");
  Serial.println(destinationIP4);
  Serial.print("Payload5: ");
  Serial.println(buffer5);

  delay(50);
}
// =============================================================== AKHIR FUNGSI sendData() ===================================================================