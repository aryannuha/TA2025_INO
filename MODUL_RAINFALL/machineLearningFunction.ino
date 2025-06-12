/* 
 Nama File      : machineLearningFunction.ino
 Tanggal Update : 09 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
    1. Fungsi machine_learning() digunakan untuk melakukan regresi linear pada data rainfall.
    2. Fungsi add_data_point() digunakan untuk menambahkan data baru ke dalam model regresi.
    3. Fungsi predict() digunakan untuk memprediksi nilai rainfall berdasarkan model regresi.
    4. Fungsi reset_regression() digunakan untuk mengatur ulang semua variabel regresi dan menyimpan data ke EEPROM.
*/

// ======================================= AWAL FUNGSI machine_learning_temp() ===========================================================================
void machine_learning(){
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
// =========================================== AKHIR FUNGSI machine_learning() =======================================================================

// =================================================== AWAL FUNGSI add_data_point() ====================================================================
void add_data_point(float x_value, float y_value) {
  // Add new data point to running totals
  n++;
  sum_x += x_value;
  sum_y += y_value;
  sum_xy += (x_value * y_value);
  sum_x_squared += (x_value * x_value);
  
  // Recalculate regression coefficients
  machine_learning();
}
// =================================================== AKHIR FUNGSI add_data_point_temp() ===================================================================

// ================================================== AWAL FUNGSI predictTemp() ============================================================================
float predict(float x_future) {
  // Predict y value for future x
  return a + (b * x_future);
}
// ================================================== AKHIR FUNGSI predictTemp() ===========================================================================

void reset_regression() {
  // Reset all variables to initial state
  a = b = 0;
  sum_x = sum_y = sum_xy = sum_x_squared = 0;
  n = 0;
  time_counter = 1;
  
  // Clear EEPROM magic number
  EEPROM.writeULong(ADDR_MAGIC, 0);
  EEPROM.commit();
  
  Serial.println("ML data reset");
}
