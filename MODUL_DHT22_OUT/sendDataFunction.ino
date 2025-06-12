/* 
 Nama File      : sendDataFunction.ino
 Tanggal Update : 09 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
    1. Fungsi sendData() digunakan untuk mengirim data suhu dan kelembaban dalam format JSON ke beberapa tujuan melalui protokol UDP.
    2. Data yang dikirim meliputi kode modul, kode variabel, data, kode alarm, dan berita.
    3. Fungsi ini juga mengirimkan prediksi suhu dan kelembaban untuk periode waktu t+1 t+2, t+3, t+4, dan t+5.
    4. Fungsi ini menggunakan library ArduinoJson untuk membuat dan mengirim data dalam format JSON.
*/

// ==================================================== FUNGSI sendData() UNTUK KIRIM KE BERBAGAI MODUL DALAM FORMAT JSON ====================================
void sendData() {
  // MEMBUAT DOKUMEN JSON UNTUK SUHU OUTDOOR
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
  delay(50);

  // BUAT DOKUMEN JSON UNTUK KELEMBABAN OUTDOOR
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
  delay(50);

  // BUAT DOKUMEN JSON UNTUK prediksi 1 menit ke depan suhu
  StaticJsonDocument<200> doc2;
  doc2["kodeModul"] = suhuData.kodeModul;
  doc2["kodeVariabel"] = 13;
  doc2["kodeData"] = predicted_value_temp[0];
  doc2["kodeAlarm"] = 0;
  doc2["berita"] = "Prediksi t+1"; // ArduinoJson tidak mendukung char langsung

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

  // DELAY 1 DETIK SEBELUM MENGIRIM JSON SUHU
  delay(50);

  // BUAT DOKUMEN JSON UNTUK prediksi 2 menit ke depan suhu
  StaticJsonDocument<200> doc3;
  doc3["kodeModul"] = suhuData.kodeModul;
  doc3["kodeVariabel"] = 14;
  doc3["kodeData"] = predicted_value_temp[1];
  doc3["kodeAlarm"] = 0;
  doc3["berita"] = "Prediksi t+2"; // ArduinoJson tidak mendukung char langsung

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

  // DELAY 1 DETIK SEBELUM MENGIRIM JSON SUHU
  delay(50);

  // BUAT DOKUMEN JSON UNTUK prediksi 3 menit ke depan suhu
  StaticJsonDocument<200> doc4;
  doc4["kodeModul"] = suhuData.kodeModul;
  doc4["kodeVariabel"] = 15;
  doc4["kodeData"] = predicted_value_temp[2];
  doc4["kodeAlarm"] = 0;
  doc4["berita"] = "Prediksi t+3"; // ArduinoJson tidak mendukung char langsung

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

  // DELAY 1 DETIK SEBELUM MENGIRIM JSON SUHU
  delay(50);

  // BUAT DOKUMEN JSON UNTUK prediksi 4 menit ke depan suhu
  StaticJsonDocument<200> doc5;
  doc5["kodeModul"] = suhuData.kodeModul;
  doc5["kodeVariabel"] = 16;
  doc5["kodeData"] = predicted_value_temp[3];
  doc5["kodeAlarm"] = 0;
  doc5["berita"] = "Prediksi t+4"; // ArduinoJson tidak mendukung char langsung

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

  // DELAY 1 DETIK SEBELUM MENGIRIM JSON SUHU
  delay(50);

  // BUAT DOKUMEN JSON UNTUK prediksi 5 menit ke depan suhu
  StaticJsonDocument<200> doc6;
  doc6["kodeModul"] = suhuData.kodeModul;
  doc6["kodeVariabel"] = 17;
  doc6["kodeData"] = predicted_value_temp[4];
  doc6["kodeAlarm"] = 0;
  doc6["berita"] = "Prediksi t+5"; // ArduinoJson tidak mendukung char langsung

  // SERIALIZE KE BUFFER
  char buffer6[256];
  size_t n6 = serializeJson(doc6, buffer6);

  // KIRIM KE BERBAGAI MODUL SESUAI DESTINASI IP MELALUI PROTOKOL KOMUNIKASI UDP
  udp.writeTo((const uint8_t*)buffer6, n6, destinationIP, 1234);
  udp.writeTo((const uint8_t*)buffer6, n6, destinationIP2, 1234);
  udp.writeTo((const uint8_t*)buffer6, n6, destinationIP3, 1234);
  udp.writeTo((const uint8_t*)buffer6, n6, destinationIP4, 1234);

  // MENAMPILKAN PAYLOAD
  Serial.print("Dikirim ke ");
  Serial.print(destinationIP);
  Serial.print(" ");
  Serial.print(destinationIP2);
  Serial.print(" ");
  Serial.print(destinationIP3);
  Serial.print(" ");
  Serial.println(destinationIP4);
  Serial.print("Payload6: ");
  Serial.println(buffer6);

  // DELAY 1 DETIK SEBELUM MENGIRIM JSON SUHU
  delay(50);

    // BUAT DOKUMEN JSON UNTUK prediksi 1 menit ke depan kelembaban
  StaticJsonDocument<200> doc7;
  doc7["kodeModul"] = kelembabanData.kodeModul;
  doc7["kodeVariabel"] = 18;
  doc7["kodeData"] = predicted_value_humidity[0];
  doc7["kodeAlarm"] = 0;
  doc7["berita"] = "Prediksi t+1"; // ArduinoJson tidak mendukung char langsung

  // SERIALIZE KE BUFFER
  char buffer7[256];
  size_t n7 = serializeJson(doc7, buffer7);

  // KIRIM KE BERBAGAI MODUL SESUAI DESTINASI IP MELALUI PROTOKOL KOMUNIKASI UDP
  udp.writeTo((const uint8_t*)buffer7, n7, destinationIP, 1234);
  udp.writeTo((const uint8_t*)buffer7, n7, destinationIP2, 1234);
  udp.writeTo((const uint8_t*)buffer7, n7, destinationIP3, 1234);
  udp.writeTo((const uint8_t*)buffer7, n7, destinationIP4, 1234);

  // MENAMPILKAN PAYLOAD
  Serial.print("Dikirim ke ");
  Serial.print(destinationIP);
  Serial.print(" ");
  Serial.print(destinationIP2);
  Serial.print(" ");
  Serial.print(destinationIP3);
  Serial.print(" ");
  Serial.println(destinationIP4);
  Serial.print("Payload7: ");
  Serial.println(buffer7);

  // DELAY 1 DETIK SEBELUM MENGIRIM JSON SUHU
  delay(50);

    // BUAT DOKUMEN JSON UNTUK prediksi 2 menit ke depan kelembaban
  StaticJsonDocument<200> doc8;
  doc8["kodeModul"] = kelembabanData.kodeModul;
  doc8["kodeVariabel"] = 19;
  doc8["kodeData"] = predicted_value_humidity[1];
  doc8["kodeAlarm"] = 0;
  doc8["berita"] = "Prediksi t+2"; // ArduinoJson tidak mendukung char langsung

  // SERIALIZE KE BUFFER
  char buffer8[256];
  size_t n8 = serializeJson(doc8, buffer8);

  // KIRIM KE BERBAGAI MODUL SESUAI DESTINASI IP MELALUI PROTOKOL KOMUNIKASI UDP
  udp.writeTo((const uint8_t*)buffer8, n8, destinationIP, 1234);
  udp.writeTo((const uint8_t*)buffer8, n8, destinationIP2, 1234);
  udp.writeTo((const uint8_t*)buffer8, n8, destinationIP3, 1234);
  udp.writeTo((const uint8_t*)buffer8, n8, destinationIP4, 1234);

  // MENAMPILKAN PAYLOAD
  Serial.print("Dikirim ke ");
  Serial.print(destinationIP);
  Serial.print(" ");
  Serial.print(destinationIP2);
  Serial.print(" ");
  Serial.print(destinationIP3);
  Serial.print(" ");
  Serial.println(destinationIP4);
  Serial.print("Payload8: ");
  Serial.println(buffer8);

  // DELAY 1 DETIK SEBELUM MENGIRIM JSON SUHU
  delay(50);

    // BUAT DOKUMEN JSON UNTUK prediksi 3 menit ke depan kelembaban
  StaticJsonDocument<200> doc9;
  doc9["kodeModul"] = kelembabanData.kodeModul;
  doc9["kodeVariabel"] = 20;
  doc9["kodeData"] = predicted_value_humidity[2];
  doc9["kodeAlarm"] = 0;
  doc9["berita"] = "Prediksi t+3"; // ArduinoJson tidak mendukung char langsung

  // SERIALIZE KE BUFFER
  char buffer9[256];
  size_t n9 = serializeJson(doc9, buffer9);

  // KIRIM KE BERBAGAI MODUL SESUAI DESTINASI IP MELALUI PROTOKOL KOMUNIKASI UDP
  udp.writeTo((const uint8_t*)buffer9, n9, destinationIP, 1234);
  udp.writeTo((const uint8_t*)buffer9, n9, destinationIP2, 1234);
  udp.writeTo((const uint8_t*)buffer9, n9, destinationIP3, 1234);
  udp.writeTo((const uint8_t*)buffer9, n9, destinationIP4, 1234);

  // MENAMPILKAN PAYLOAD
  Serial.print("Dikirim ke ");
  Serial.print(destinationIP);
  Serial.print(" ");
  Serial.print(destinationIP2);
  Serial.print(" ");
  Serial.print(destinationIP3);
  Serial.print(" ");
  Serial.println(destinationIP4);
  Serial.print("Payload9: ");
  Serial.println(buffer9);

  // DELAY 1 DETIK SEBELUM MENGIRIM JSON SUHU
  delay(50);

    // BUAT DOKUMEN JSON UNTUK prediksi 4 menit ke depan suhu
  StaticJsonDocument<200> doc10;
  doc10["kodeModul"] = kelembabanData.kodeModul;
  doc10["kodeVariabel"] = 21;
  doc10["kodeData"] = predicted_value_humidity[3];
  doc10["kodeAlarm"] = 0;
  doc10["berita"] = "Prediksi t+4"; // ArduinoJson tidak mendukung char langsung

  // SERIALIZE KE BUFFER
  char buffer10[256];
  size_t n10 = serializeJson(doc10, buffer10);

  // KIRIM KE BERBAGAI MODUL SESUAI DESTINASI IP MELALUI PROTOKOL KOMUNIKASI UDP
  udp.writeTo((const uint8_t*)buffer10, n10, destinationIP, 1234);
  udp.writeTo((const uint8_t*)buffer10, n10, destinationIP2, 1234);
  udp.writeTo((const uint8_t*)buffer10, n10, destinationIP3, 1234);
  udp.writeTo((const uint8_t*)buffer10, n10, destinationIP4, 1234);

  // MENAMPILKAN PAYLOAD
  Serial.print("Dikirim ke ");
  Serial.print(destinationIP);
  Serial.print(" ");
  Serial.print(destinationIP2);
  Serial.print(" ");
  Serial.print(destinationIP3);
  Serial.print(" ");
  Serial.println(destinationIP4);
  Serial.print("Payload10: ");
  Serial.println(buffer10);

  // DELAY 1 DETIK SEBELUM MENGIRIM JSON SUHU
  delay(50);

    // BUAT DOKUMEN JSON UNTUK prediksi 5 menit ke depan suhu
  StaticJsonDocument<200> doc11;
  doc11["kodeModul"] = suhuData.kodeModul;
  doc11["kodeVariabel"] = 22;
  doc11["kodeData"] = predicted_value_humidity[4];
  doc11["kodeAlarm"] = 0;
  doc11["berita"] = "Prediksi t+5"; // ArduinoJson tidak mendukung char langsung

  // SERIALIZE KE BUFFER
  char buffer11[256];
  size_t n11 = serializeJson(doc11, buffer11);

  // KIRIM KE BERBAGAI MODUL SESUAI DESTINASI IP MELALUI PROTOKOL KOMUNIKASI UDP
  udp.writeTo((const uint8_t*)buffer11, n11, destinationIP, 1234);
  udp.writeTo((const uint8_t*)buffer11, n11, destinationIP2, 1234);
  udp.writeTo((const uint8_t*)buffer11, n11, destinationIP3, 1234);
  udp.writeTo((const uint8_t*)buffer11, n11, destinationIP4, 1234);

  // MENAMPILKAN PAYLOAD
  Serial.print("Dikirim ke ");
  Serial.print(destinationIP);
  Serial.print(" ");
  Serial.print(destinationIP2);
  Serial.print(" ");
  Serial.print(destinationIP3);
  Serial.print(" ");
  Serial.println(destinationIP4);
  Serial.print("Payload11: ");
  Serial.println(buffer11);

  // DELAY 1 DETIK SEBELUM MENGIRIM JSON SUHU
  delay(50);
}
// ============================================================ AKHIR FUNGSI sendData() =======================================================================

