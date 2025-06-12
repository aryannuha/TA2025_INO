/* 
 Nama File      : sendDataFunction.ino
 Tanggal Update : 09 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
    1. Fungsi ini digunakan untuk mengirim data yang telah diproses ke server MQTT.
    2. Data yang dikirim meliputi kode modul, kode variabel, nilai data, kode alarm, dan berita.
    3. Fungsi ini juga mengatur topik MQTT berdasarkan kode modul dan variabel untuk setiap data yang dikirim.
    4. Fungsi ini memastikan koneksi MQTT aktif sebelum mengirim data.
    5. Fungsi ini juga mengatur flag retain pada setiap data yang dikirim untuk memastikan data tetap tersedia di server MQTT.
    6. Fungsi ini digunakan untuk mengirim data secara periodik sesuai dengan interval yang telah ditentukan.
    7. Fungsi ini juga mengatur jumlah data yang berhasil dipublikasikan ke server MQTT.
    8. Fungsi ini juga mengatur delay kecil antara setiap pengiriman data untuk menghindari overload pada server MQTT.
*/

// ================================================ FUNGSI sendData() KE MQTT ================================================================================
void sendData(){
  if (!client.connected()) {
    Serial.println("MQTT not connected, skipping publish");
    return;
  }
  
  int publishCount = 0;
  
  for (int i = 0; i < numModules; i++) {
    for (int j = 0; j < MAX_VARIABLES_PER_MODULE; j++) {
        publishSensorData(dataMatrix[i][j]);
        publishCount++;
        delay(10);  // Small delay between publishes
    }
  }
  
  // Serial.printf("Published %d sensor readings to MQTT\n", publishCount);
}
// =============================================== AKHRI FUNGSI sendData() ====================================================================================

void publishSensorData(SensorData& sensorData) {
  // Convert data to strings for MQTT publishing
  char kodeModul_str[50];
  char kodeVariabel_str[10];
  char kodeData_str[15];
  char kodeAlarm_str[10];
  char berita_str[100];
  
  // Convert values to strings
  strcpy(kodeModul_str, sensorData.kodeModul.c_str());
  itoa(sensorData.kodeVariabel, kodeVariabel_str, 10);
  dtostrf(sensorData.kodeData, 4, 6, kodeData_str);
  itoa(sensorData.kodeAlarm, kodeAlarm_str, 10);
  strcpy(berita_str, sensorData.berita.c_str());
  
  // Create topic names with module and variable identifiers
  String topicPrefix = "mcs/";
  String moduleVarSuffix = sensorData.kodeModul + String(sensorData.kodeVariabel);
  
  String kodeModulTopic = topicPrefix + "kodeModul" + moduleVarSuffix;
  String kodeVariabelTopic = topicPrefix + "kodeVariabel" + moduleVarSuffix;
  String kodeDataTopic = topicPrefix + "kodeData" + moduleVarSuffix;
  String kodeAlarmTopic = topicPrefix + "kodeAlarm" + moduleVarSuffix;
  String beritaTopic = topicPrefix + "berita" + moduleVarSuffix;

  // Publish each data field to separate topics with retain flag
  // bool success = true;
  // success &= client.publish(kodeModulTopic.c_str(), kodeModul_str, false);
  // success &= client.publish(kodeVariabelTopic.c_str(), kodeVariabel_str, false);
  // success &= client.publish(kodeDataTopic.c_str(), kodeData_str, false);
  // success &= client.publish(kodeAlarmTopic.c_str(), kodeAlarm_str, false);
  // success &= client.publish(beritaTopic.c_str(), berita_str, false);

  client.publish(kodeModulTopic.c_str(), kodeModul_str, false);
  client.publish(kodeVariabelTopic.c_str(), kodeVariabel_str, false);
  client.publish(kodeDataTopic.c_str(), kodeData_str, false);
  client.publish(kodeAlarmTopic.c_str(), kodeAlarm_str, false);
  client.publish(beritaTopic.c_str(), berita_str, false);
  
  // if (success) {
  //   Serial.printf("Published all data for Module=%s, Variable=%d\n", 
  //                sensorData.kodeModul.c_str(), sensorData.kodeVariabel);
  //   Serial.printf("  Data: %s, Alarm: %s, Message: %s\n", 
  //                kodeData_str, kodeAlarm_str, berita_str);
  // } else {
  //   Serial.printf("Failed to publish some data for Module=%s, Variable=%d\n", 
  //                sensorData.kodeModul.c_str(), sensorData.kodeVariabel);
  // }
}