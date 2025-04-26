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