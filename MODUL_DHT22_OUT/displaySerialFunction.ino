/* 
 Nama File      : displaySerialFunction.ino
 Tanggal Update : 09 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
    1. Fungsi displayDebug() digunakan untuk menampilkan nilai-nilai dari persamaan regresi linear suhu dan kelembaban.
    2. Fungsi ini akan mencetak nilai-nilai seperti suhu, kelembaban, jumlah data, dan koefisien regresi ke serial monitor.
    3. Fungsi showPredict() digunakan untuk menampilkan prediksi nilai suhu dan kelembaban untuk periode waktu t+1 hingga t+5.
    4. Fungsi ini akan mencetak nilai prediksi suhu dan kelembaban ke serial monitor.
*/

// ======================================= FUNGSI displayDebug() UNTUK MENAMPILKAN UPDATE NILAI PERSAMAAN REGRESI LINEAR ====================================
void displayDebug(){
  Serial.print("Suhu: ");
  Serial.print(time_counter); Serial.print(", ");
  Serial.print(suhuData.data); Serial.print(", ");
  Serial.print(n); Serial.print(", ");
  Serial.print(sum_x, 2); Serial.print(", ");
  Serial.print(sum_y, 2); Serial.print(", ");
  Serial.print(sum_xy, 2); Serial.print(", ");
  Serial.print(sum_x_squared, 2); Serial.print(", ");
  Serial.print(b, 6); Serial.print(", ");
  Serial.println(a, 6);

  Serial.print("Kelembaban: ");
  Serial.print(time_counter_humid); Serial.print(", ");
  Serial.print(kelembabanData.data); Serial.print(", ");
  Serial.print(n_humid); Serial.print(", ");
  Serial.print(sum_x_humid, 2); Serial.print(", ");
  Serial.print(sum_y_humid, 2); Serial.print(", ");
  Serial.print(sum_xy_humid, 2); Serial.print(", ");
  Serial.print(sum_x_squared_humid, 2); Serial.print(", ");
  Serial.print(b_humid, 6); Serial.print(", ");
  Serial.println(a_humid, 6);
}
// =================================== AKHIR FUNGSi =========================================================================================================

// ================================================ FUNGSI showPredict() UNTUK MENAMPILKAN PREDIKSI t+1 - t+5 ===============================================
void showPredict(){
  // Predict next 5 time periods
  Serial.println("Predictions:");
  Serial.println("Suhu: ");
  for (int i = 0; i < 5; i++) {
    predicted_value_temp[i] = predictTemp(time_counter + i + 1);
    Serial.print("  t+"); Serial.print(i + 1); 
    Serial.print(": "); Serial.println(predicted_value_temp[i], 2);
  }
  Serial.println("Kelembaban: ");
  for (int i = 0; i < 5; i++) {
    predicted_value_humidity[i] = predictHumid(time_counter_humid + i + 1);
    Serial.print("  t+"); Serial.print(i + 1); 
    Serial.print(": "); Serial.println(predicted_value_humidity[i], 2);
  }
  Serial.println("---");
}