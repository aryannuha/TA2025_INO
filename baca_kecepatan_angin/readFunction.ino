// =============================== FUNGSI readAngin() MEMBACA NILAI DARI RS485 DENGAN STARTING ADDRESS 0x0000 ===============================================
void readAngin() {
  uint8_t result = node.readHoldingRegisters(0x0000, 1);

  if (result == node.ku8MBSuccess)
  {
    uint16_t rawWind = node.getResponseBuffer(0); // Mendapatkan nilai mentah
    windSpeed = rawWind / 10.0; // Sesuai datasheet: nilai dikali 0.1
    windspeedData.data = windSpeed;
  }

  delay(1000);
}
// ============================================= AKHIR FUNGSI readAngin() ====================================================================================