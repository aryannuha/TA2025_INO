/* 
 Nama File      : processFunction.ino
 Tanggal Update : 09 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
    1. Fungsi ini digunakan untuk memproses data yang diterima dari WSN (Wireless Sensor Network) dalam format JSON.
    2. Data yang diterima kemudian diparsing dan disimpan pada struktur data yang telah didefinisikan.
    3. Data yang tersimpan pada struktur data kemudian dapat digunakan untuk keperluan lain, seperti pengiriman ke cloud atau Google Sheets.
    4. Fungsi ini menggunakan library ArduinoJson untuk memparsing data JSON.
*/

// ======================================== FUNGSI parsing() UNTUK MEMASUKAN DATA JSON KE STRUCT MASING-MASING =================================================
bool parsing(const char* jsonString){
  DynamicJsonDocument doc(512);
  DeserializationError error = deserializeJson(doc, jsonString);
  
  if (error) {
    Serial.print("JSON parse error: "); Serial.println(error.c_str());
    return false;
  }
  
  if (!doc.containsKey("kodeModul") || !doc.containsKey("kodeVariabel") || !doc.containsKey("kodeData") || !doc["kodeModul"].is<String>()) {
    Serial.println("Missing required fields in JSON");
    return false;
  }
  
  String kodeModul = doc["kodeModul"].as<String>();
  int kodeVariabel = doc["kodeVariabel"];
  float kodeData = doc["kodeData"];
  int kodeAlarm = doc.containsKey("kodeAlarm") ? doc["kodeAlarm"] : 0;
  String berita = doc.containsKey("berita") ? doc["berita"].as<String>() : "";
  
  if (kodeVariabel < 11 || kodeVariabel >= MAX_VARIABLES_PER_MODULE + 11) {
    Serial.print("Invalid variable code: "); Serial.println(kodeVariabel);
    return false;
  }

  int varIndex = kodeVariabel - 11;
  int moduleIdx = findOrCreateModuleIndex(kodeModul);
  if (moduleIdx < 0) {
    return false;
  }
  
  noInterrupts();
  
  // LOGIKA BARU YANG PENTING:
  // 1. Jika sensor mengirim sinyal normal, reset bendera pengabaian.
  if (kodeAlarm == 0) {
      dataMatrix[moduleIdx][varIndex].warningCleared = false;
  }

  // 2. Hanya reset timer hening jika alarm baru muncul dari kondisi normal.
  if (dataMatrix[moduleIdx][varIndex].kodeAlarm == 0 && kodeAlarm > 0) {
      dataMatrix[moduleIdx][varIndex].alarmSilencedTime = 0;
  }

  // 3. Selalu perbarui data dari sensor.
  dataMatrix[moduleIdx][varIndex].kodeModul = kodeModul;
  dataMatrix[moduleIdx][varIndex].kodeVariabel = kodeVariabel;
  dataMatrix[moduleIdx][varIndex].kodeData = kodeData;
  dataMatrix[moduleIdx][varIndex].kodeAlarm = kodeAlarm;
  dataMatrix[moduleIdx][varIndex].berita = berita;
  dataMatrix[moduleIdx][varIndex].isUsed = true;
  
  interrupts();
  
  return true;
}
// =========================================================== AKHIR FUNGSI PARSING ==========================================================================

int findOrCreateModuleIndex(String moduleCode) {
  for (int i = 0; i < numModules; i++) {
    if (moduleNames[i] == moduleCode) {
      return i;
    }
  }
  if (numModules < MAX_MODULES) {
    moduleNames[numModules] = moduleCode;
    return numModules++;
  }
  Serial.println("Warning: Maximum modules reached");
  return -1;
}