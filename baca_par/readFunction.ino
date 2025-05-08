// =============================== FUNGSI readPar() MEMBACA NILAI DARI RS485 DENGAN STARTING ADDRESS 0x0000 ===============================================
void readPar() {
  uint8_t result = node.readHoldingRegisters(0x0000, 1);

  if (result == node.ku8MBSuccess)
  {
    uint16_t rawPar = node.getResponseBuffer(0); // Mendapatkan nilai mentah
    parValue = rawPar;
    parData.data = parValue;
  }

  delay(1000);
}
// ============================================= AKHIR FUNGSI readPar() ====================================================================================