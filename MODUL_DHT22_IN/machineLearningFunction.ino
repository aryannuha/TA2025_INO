/* 
 Nama File      : machineLearningFunction.ino
 Tanggal Update : 09 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
    1. Fungsi machine_learning_temp() digunakan untuk melakukan regresi linear pada data suhu.
    2. Fungsi machine_learning_humidity() digunakan untuk melakukan regresi linear pada data kelembaban.
    3. Fungsi add_data_point_temp() digunakan untuk menambahkan data suhu baru ke dalam model regresi.
    4. Fungsi add_data_point_humid() digunakan untuk menambahkan data kelembaban baru ke dalam model regresi.
    5. Fungsi predictTemp() digunakan untuk memprediksi nilai suhu berdasarkan model regresi. 
    6. Fungsi predictHumid() digunakan untuk memprediksi nilai kelembaban berdasarkan model regresi.
    7. Fungsi reset_regression() digunakan untuk mengatur ulang semua variabel regresi dan menyimpan data ke EEPROM.
*/

// ======================================= AWAL FUNGSI machine_learning_temp() ===========================================================================
void machine_learning_temp(){
  // Linear regression: y = a + bX
  // where a = intercept, b = slope, X = predictor
  
  if (n < 2) return; // Need at least 2 points
  
  // Calculate slope (b)
  float numerator = (n * sum_xy) - (sum_x * sum_y);
  float denominator = (n * sum_x_squared) - (sum_x * sum_x);
  
  if (denominator != 0) {
    b = numerator / denominator;
  } else {
    b = 0; // Handle division by zero
  }
  
  // Calculate intercept (a)
  // a = (sum_y/n) - b*(sum_x/n)
  float y_mean = sum_y / n;
  float x_mean = sum_x / n;
  a = y_mean - (b * x_mean);
}
// =========================================== AKHIR FUNGSI machine_learning_temp() =======================================================================

// ============================================= AWAL machine_learning_humidity() =========================================================================
void machine_learning_humidity(){
  // Linear regression: y = a + bX
  // where a = intercept, b = slope, X = predictor
  
  if (n_humid < 2) return; // Need at least 2 points
  
  // Calculate slope (b)
  float numerator = (n_humid * sum_xy_humid) - (sum_x_humid * sum_y_humid);
  float denominator = (n * sum_x_squared_humid) - (sum_x_humid * sum_x_humid);
  
  if (denominator != 0) {
    b_humid = numerator / denominator;
  } else {
    b_humid = 0; // Handle division by zero
  }
  
  // Calculate intercept (a)
  // a = (sum_y/n) - b*(sum_x/n)
  float y_mean = sum_y_humid / n_humid;
  float x_mean = sum_x_humid / n_humid;
  a_humid = y_mean - (b * x_mean);
}
// ==================================================== AKHIR FUNGSI machine_learning_humidity() ============================================================

// =================================================== AWAL FUNGSI add_data_point_temp() ====================================================================
void add_data_point_temp(float x_value, float y_value) {
  // Add new data point to running totals
  n++;
  sum_x += x_value;
  sum_y += y_value;
  sum_xy += (x_value * y_value);
  sum_x_squared += (x_value * x_value);
  
  // Recalculate regression coefficients
  machine_learning_temp();
}
// =================================================== AKHIR FUNGSI add_data_point_temp() ===================================================================

// =================================================== AWAL FUNGSI add_data_point_humid() ===================================================================
void add_data_point_humid(float x_value, float y_value) {
  // Add new data point to running totals
  n_humid++;
  sum_x_humid += x_value;
  sum_y_humid += y_value;
  sum_xy_humid += (x_value * y_value);
  sum_x_squared_humid += (x_value * x_value);
  
  // Recalculate regression coefficients
  machine_learning_humidity();
}
// =================================================== AKHIR FUNGSI add_data_point_humid() =================================================================

// ================================================== AWAL FUNGSI predictTemp() ============================================================================
float predictTemp(float x_future) {
  // Predict y value for future x
  return a + (b * x_future);
}
// ================================================== AKHIR FUNGSI predictTemp() ===========================================================================

// ================================================== AWAL FUNGSI predictHumid() ===========================================================================
float predictHumid(float x_future) {
  // Predict y value for future x
  return a_humid + (b_humid * x_future);
}
// ================================================== AKHIR FUNGSI predictHumid() ==========================================================================

void reset_regression() {
  // Reset all variables to initial state
  a = b = a_humid = b_humid = 0;
  sum_x = sum_y = sum_xy = sum_x_squared = 0;
  sum_x_humid = sum_y_humid = sum_xy_humid = sum_x_squared_humid = 0;
  n = n_humid = 0;
  time_counter = time_counter_humid = 1;
  
  // Clear EEPROM magic number
  EEPROM.writeULong(ADDR_MAGIC, 0);
  EEPROM.commit();
  
  Serial.println("ML data reset");
}
