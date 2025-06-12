/* 
 Nama File      : displaySerialFunction.ino
 Tanggal Update : 09 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
    1. Fungsi displayDebug() digunakan untuk menampilkan nilai-nilai dari persamaan regresi linear CO2.
    2. Fungsi ini akan mencetak nilai-nilai seperti suhu, kelembaban, jumlah data, dan koefisien regresi ke serial monitor.
    3. Fungsi showPredict() digunakan untuk menampilkan prediksi nilai CO2 untuk periode waktu t+1 hingga t+5.
    4. Fungsi ini akan mencetak nilai prediksi suhu dan kelembaban ke serial monitor.
*/

// =============================================== FUNGSI displayMonitor() UNTUK MENAMPILKAN PEMBACAAN CO2 ==================================================
void displayMonitor(){
  Serial.print("TEGANGAN: ");
  Serial.print(volts, 3);            // Print with 3 decimal places
  Serial.print("V           ");

  Serial.print("CO2: ");
  // if (percentage == -1) {
  //   Serial.print("< 400");
  // } else {
  //   Serial.print(percentage);
  // }

  // Serial.print(co2Data.dataCO2);
  Serial.print(rawCO2);

  Serial.print(" PPM");
  Serial.println();
}
// ============================================================ AKHIR FUNGSI displayMonitor() ================================================================

// ======================================= FUNGSI displayDebug() UNTUK MENAMPILKAN UPDATE NILAI PERSAMAAN REGRESI LINEAR ====================================
void displayDebug(){
  Serial.print("CO2 Angin: ");
  Serial.print(time_counter); Serial.print(", ");
  Serial.print(co2Data.data); Serial.print(", ");
  Serial.print(n); Serial.print(", ");
  Serial.print(sum_x, 2); Serial.print(", ");
  Serial.print(sum_y, 2); Serial.print(", ");
  Serial.print(sum_xy, 2); Serial.print(", ");
  Serial.print(sum_x_squared, 2); Serial.print(", ");
  Serial.print(b, 6); Serial.print(", ");
  Serial.println(a, 6);
}
// =================================== AKHIR FUNGSi =========================================================================================================

// ================================================ FUNGSI showPredict() UNTUK MENAMPILKAN PREDIKSI t+1 - t+5 ===============================================
void showPredict(){
  // Predict next 5 time periods
  Serial.println("Predictions:");
  for (int i = 0; i < 5; i++) {
    predicted_value[i] = predict(time_counter + i + 1);
    Serial.print("  t+"); Serial.print(i + 1); 
    Serial.print(": "); Serial.println(predicted_value[i], 2);
  }
  Serial.println("---");
}