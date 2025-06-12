/*
 Nama File      : displaySerialFunction.ino
 Tanggal Update : 12 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
   1. Fungsi ini digunakan untuk menampilkan status matriks data rida-M ke Serial Monitor.
   2. Fungsi ini mencetak nama modul, kode variabel, kode data, kode alarm, dan berita untuk setiap variabel dalam matriks.
   3. Fungsi ini juga menampilkan statistik jumlah paket yang diterima dan diproses, serta jumlah modul aktif.
   4. Fungsi ini digunakan untuk debugging dan pemantauan status sistem.
*/

// =========================================== FUNGSI displaySerial() UNTUK MENAMPILKAN DATA YANG DIKIRIM KE MQTT ========================================
void displaySerial(){
 Serial.println("\n===== RIDAM Matrix Status =====");
  for (int i = 0; i < numModules; i++) {
    Serial.print("Module: ");
    Serial.println(moduleNames[i]);
    
    for (int j = 0; j < MAX_VARIABLES_PER_MODULE; j++) {
        Serial.printf("  Var[%d]: %.2f (Alarm:%d) [%s]\n", 
                     dataMatrix[i][j].kodeVariabel,
                     dataMatrix[i][j].kodeData,
                     dataMatrix[i][j].kodeAlarm,
                     dataMatrix[i][j].berita.c_str());
    }
  }
  Serial.println("==============================\n");
}
// ============================================================ AKHIR FUNGSI displaySerial() =============================================================

void printStatistics() {
  Serial.println("\n===== Statistics =====");
  Serial.printf("Packets received: %lu\n", packetsReceived);
  Serial.printf("Packets processed: %lu\n", packetsProcessed);
  Serial.printf("Processing rate: %.2f%%\n", 
                packetsReceived > 0 ? (float)packetsProcessed/packetsReceived*100 : 0);
  Serial.printf("Active modules: %d\n", numModules);
  Serial.printf("Free heap: %d bytes\n", ESP.getFreeHeap());
  Serial.println("=====================\n");
}