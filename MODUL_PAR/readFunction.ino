/* 
 Nama File      : readFunction.ino
 Tanggal Update : 09 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
    1. Fungsi readPar() digunakan untuk membaca nilai PAR dari sensor yang terhubung melalui RS485.
    2. Fungsi ini menggunakan Modbus untuk membaca nilai dari starting address 0x0000.
    3. Nilai yang dibaca akan disimpan dalam variabel parValue dan juga dimasukkan ke dalam structure parData.
*/

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