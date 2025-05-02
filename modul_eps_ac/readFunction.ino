void readPzem(){
  rawVoltage = pzem.voltage();
  rawCurrent = pzem.current();
  rawPower   = pzem.power();
}