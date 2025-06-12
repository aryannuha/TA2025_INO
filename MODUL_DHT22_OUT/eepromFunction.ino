/* 
 Nama File      : eepromFunction.ino
 Tanggal Update : 09 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
    1. Fungsi saveMLDataToEEPROM() digunakan untuk menyimpan data machine learning (ML) ke dalam EEPROM.
    2. Data yang disimpan meliputi koefisien regresi suhu dan kelembaban, jumlah data, dan waktu pengukuran.
    3. Fungsi loadMLDataFromEEPROM() digunakan untuk memuat data ML dari EEPROM.
    4. Fungsi ini juga memeriksa apakah EEPROM telah diinisialisasi dengan benar menggunakan magic number.
*/

// ========================== FUNGSI SAVE ML DATA KE EEPROM =============================================================================================
void saveMLDataToEEPROM() {
  // Save temperature regression data
  EEPROM.writeFloat(ADDR_A, a);
  EEPROM.writeFloat(ADDR_B, b);
  EEPROM.writeFloat(ADDR_SUM_X, sum_x);
  EEPROM.writeFloat(ADDR_SUM_Y, sum_y);
  EEPROM.writeFloat(ADDR_SUM_XY, sum_xy);
  EEPROM.writeFloat(ADDR_SUM_X_SQUARED, sum_x_squared);
  EEPROM.writeInt(ADDR_N, n);
  EEPROM.writeFloat(ADDR_TIME_COUNTER, time_counter);
  
  // Save humidity regression data
  EEPROM.writeFloat(ADDR_A_HUMID, a_humid);
  EEPROM.writeFloat(ADDR_B_HUMID, b_humid);
  EEPROM.writeFloat(ADDR_SUM_X_HUMID, sum_x_humid);
  EEPROM.writeFloat(ADDR_SUM_Y_HUMID, sum_y_humid);
  EEPROM.writeFloat(ADDR_SUM_XY_HUMID, sum_xy_humid);
  EEPROM.writeFloat(ADDR_SUM_X_SQUARED_HUMID, sum_x_squared_humid);
  EEPROM.writeInt(ADDR_N_HUMID, n_humid);
  EEPROM.writeFloat(ADDR_TIME_COUNTER_HUMID, time_counter_humid);
  
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
    a = b = a_humid = b_humid = 0;
    sum_x = sum_y = sum_xy = sum_x_squared = 0;
    sum_x_humid = sum_y_humid = sum_xy_humid = sum_x_squared_humid = 0;
    n = n_humid = 0;
    time_counter = time_counter_humid = 1;
    return;
  }
  
  // Load temperature regression data
  a = EEPROM.readFloat(ADDR_A);
  b = EEPROM.readFloat(ADDR_B);
  sum_x = EEPROM.readFloat(ADDR_SUM_X);
  sum_y = EEPROM.readFloat(ADDR_SUM_Y);
  sum_xy = EEPROM.readFloat(ADDR_SUM_XY);
  sum_x_squared = EEPROM.readFloat(ADDR_SUM_X_SQUARED);
  n = EEPROM.readInt(ADDR_N);
  time_counter = EEPROM.readFloat(ADDR_TIME_COUNTER);
  
  // Load humidity regression data
  a_humid = EEPROM.readFloat(ADDR_A_HUMID);
  b_humid = EEPROM.readFloat(ADDR_B_HUMID);
  sum_x_humid = EEPROM.readFloat(ADDR_SUM_X_HUMID);
  sum_y_humid = EEPROM.readFloat(ADDR_SUM_Y_HUMID);
  sum_xy_humid = EEPROM.readFloat(ADDR_SUM_XY_HUMID);
  sum_x_squared_humid = EEPROM.readFloat(ADDR_SUM_X_SQUARED_HUMID);
  n_humid = EEPROM.readInt(ADDR_N_HUMID);
  time_counter_humid = EEPROM.readFloat(ADDR_TIME_COUNTER_HUMID);
  
  Serial.println("ML data loaded from EEPROM");
  Serial.printf("Temperature: a=%.4f, b=%.4f, n=%d\n", a, b, n);
  Serial.printf("Humidity: a=%.4f, b=%.4f, n=%d\n", a_humid, b_humid, n_humid);
}