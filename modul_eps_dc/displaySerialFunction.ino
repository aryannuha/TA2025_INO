void displaySerial(){
  Serial.println("== Pembacaan INA219 ==");
  Serial.print("Tegangan Bus   : "); Serial.print(voltage_kalibrasi); Serial.println(" V");
  Serial.print("Tegangan Shunt : "); Serial.print(shuntVoltage); Serial.println(" mV");
  Serial.print("Arus           : "); Serial.print(current_kalibrasi); Serial.println(" mA");
  Serial.print("Daya           : "); Serial.print(power_kalibrasi); Serial.println(" mW");
  Serial.println();
}