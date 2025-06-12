/* 
 Nama File      : eepromFunction.ino
 Tanggal Update : 09 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
    1. Fungsi saveMLDataToEEPROM() digunakan untuk menyimpan data machine learning (ML) ke dalam EEPROM.
    2. Data yang disimpan meliputi koefisien regresi CO2, jumlah data, dan waktu pengukuran.
    3. Fungsi loadMLDataFromEEPROM() digunakan untuk memuat data ML dari EEPROM.
    4. Fungsi ini juga memeriksa apakah EEPROM telah diinisialisasi dengan benar menggunakan magic number.
*/

// ========================== FUNGSI SAVE ML DATA KE EEPROM =============================================================================================
void saveMLDataToEEPROM() {
  // Save regression data
  EEPROM.writeFloat(ADDR_A, a);
  EEPROM.writeFloat(ADDR_B, b);
  EEPROM.writeFloat(ADDR_SUM_X, sum_x);
  EEPROM.writeFloat(ADDR_SUM_Y, sum_y);
  EEPROM.writeFloat(ADDR_SUM_XY, sum_xy);
  EEPROM.writeFloat(ADDR_SUM_X_SQUARED, sum_x_squared);
  EEPROM.writeInt(ADDR_N, n);
  EEPROM.writeFloat(ADDR_TIME_COUNTER, time_counter);
  
  // Save magic number to indicate EEPROM has been initialized
  EEPROM.writeULong(ADDR_MAGIC, MAGIC_NUMBER);
  
  EEPROM.commit(); // Save changes to EEPROM
  
  Serial.println("ML data saved to EEPROM");
}

// ========================== FUNGSI LOAD ML DATA DARI EEPROM ===========================================================================================
void loadMLDataFromEEPROM() {
  // Check if EEPROM has been initialized
  unsigned long magic = EEPROM.readULong(ADDR_MAGIC);
  
  if (magic != MAGIC_NUMBER) {
    Serial.println("EEPROM not initialized, using default values");
    // Initialize with default values
    a = b = 0;
    sum_x = sum_y = sum_xy = sum_x_squared = 0;
    n = 0;
    time_counter = 1;
    return;
  }
  
  // Load regression data
  a = EEPROM.readFloat(ADDR_A);
  b = EEPROM.readFloat(ADDR_B);
  sum_x = EEPROM.readFloat(ADDR_SUM_X);
  sum_y = EEPROM.readFloat(ADDR_SUM_Y);
  sum_xy = EEPROM.readFloat(ADDR_SUM_XY);
  sum_x_squared = EEPROM.readFloat(ADDR_SUM_X_SQUARED);
  n = EEPROM.readInt(ADDR_N);
  time_counter = EEPROM.readFloat(ADDR_TIME_COUNTER);
  
  Serial.println("ML data loaded from EEPROM");
  Serial.printf("Regresi Parameter: a=%.4f, b=%.4f, n=%d\n", a, b, n);
}