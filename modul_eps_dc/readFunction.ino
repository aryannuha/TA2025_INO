void readIna(){
  busVoltage = ina219.getBusVoltage_V();       // Tegangan di bus (V)
  shuntVoltage = ina219.getShuntVoltage_mV();  // Tegangan shunt (mV)
  current = ina219.getCurrent_mA();            // Arus (mA)
  power = ina219.getPower_mW();                // Daya (mW)
}