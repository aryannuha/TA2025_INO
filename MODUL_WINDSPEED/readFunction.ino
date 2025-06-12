/* 
 Nama File      : readFunction.ino
 Tanggal Update : 09 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
    1. Fungsi readAngin() digunakan untuk membaca nilai kecepatan angin dari sensor yang terhubung melalui RS485.
    2. Fungsi ini menggunakan Modbus untuk membaca nilai dari starting address 0x0000.
    3. Nilai yang dibaca akan disimpan dalam variabel windSpeed dan juga dimasukkan ke dalam structure windspeedData.
*/

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