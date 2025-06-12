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
  // Use larger JSON document to prevent overflow
  DynamicJsonDocument doc(512);
  
  DeserializationError error = deserializeJson(doc, jsonString);
  
  if (error) {
    Serial.print("JSON parse error: ");
    Serial.println(error.c_str());
    Serial.print("Raw data: ");
    Serial.println(jsonString);
    return false;
  }
  
  // Extract data with validation
  if (!doc.containsKey("kodeModul") || !doc.containsKey("kodeVariabel") || 
      !doc.containsKey("kodeData")) {
    Serial.println("Missing required fields in JSON");
    return false;
  }
  
  String kodeModul = doc["kodeModul"].as<String>();
  int kodeVariabel = doc["kodeVariabel"];
  float kodeData = doc["kodeData"];
  int kodeAlarm = doc.containsKey("kodeAlarm") ? doc["kodeAlarm"] : 0;
  String berita = doc.containsKey("berita") ? doc["berita"].as<String>() : "";
  
  // Validate data ranges
  if (kodeVariabel < 0 || kodeVariabel >= MAX_VARIABLES_PER_MODULE) {
    Serial.print("Invalid variable code: ");
    Serial.println(kodeVariabel);
    return false;
  }
  
  // Find or create module index
  int moduleIdx = findOrCreateModuleIndex(kodeModul);
  if (moduleIdx < 0) {
    Serial.println("Failed to find/create module index");
    return false;
  }
  
  // Store data in the matrix with thread safety
  noInterrupts();  // Disable interrupts briefly for atomic operation
  dataMatrix[moduleIdx][kodeVariabel].kodeModul = kodeModul;
  dataMatrix[moduleIdx][kodeVariabel].kodeVariabel = kodeVariabel;
  dataMatrix[moduleIdx][kodeVariabel].kodeData = kodeData;
  dataMatrix[moduleIdx][kodeVariabel].kodeAlarm = kodeAlarm;
  dataMatrix[moduleIdx][kodeVariabel].berita = berita;
  interrupts();  // Re-enable interrupts
  
  // Debug output
  // Serial.printf("Stored: Module=%s, Var=%d, Data=%.2f, Alarm=%d\n", 
  //               kodeModul.c_str(), kodeVariabel, kodeData, kodeAlarm);
  
  return true;
}
// =========================================================== AKHIR FUNGSI PARSING ==========================================================================

int findOrCreateModuleIndex(String moduleCode) {
  // Check if module exists
  for (int i = 0; i < numModules; i++) {
    if (moduleNames[i] == moduleCode) {
      return i;
    }
  }
  
  // Create new module if space available
  if (numModules < MAX_MODULES) {
    moduleNames[numModules] = moduleCode;
    return numModules++;
  }
  
  // No space available
  Serial.println("Warning: Maximum modules reached, data may be overwritten");
  return 0;  // Overwrite first module as fallback
}