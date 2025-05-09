void setupSD_Card() {
  // RTC
  if (!rtc.begin()) {
    Serial.println("RTC tidak ditemukan!");
    while (1); // stop
  }

  // if (rtc.lostPower()) {
  //   Serial.println("RTC kehilangan daya atau belum diset, mengatur waktu...");
  //   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // }

  // SD Card
  if (!SD.begin(SD_CS)) {
    Serial.println("Gagal inisialisasi SD Card!");
    while (1);
  }
  Serial.println("SD Card siap digunakan.");

  if (!SD.exists(filename)) {
    File file = SD.open(filename, FILE_WRITE);
    if (file) {
      file.print("waktu,");
      file.print("Suhu Indoor");
      file.print(",");
      file.print("Kelembaban Indoor");
      file.print(",");
      file.print("Suhu Outdoor");
      file.print(",");
      file.print("Kelembaban Outdoor");
      file.print(",");
      file.print("CO2");
      file.print(",");
      file.print("Kecepatan Angin");
      file.print(",");
      file.print("Curah Hujan");
      file.print(",");
      file.print("V DC");
      file.print(",");
      file.print("I DC");
      file.print(",");
      file.print("P DC");
      file.print(",");
      file.print("V AC");
      file.print(",");
      file.print("I AC");
      file.print(",");
      file.println("P AC");
      file.close();
    }else {
      Serial.println("Gagal membuat file log.csv");
    }
  }else {
    Serial.println("File log.csv sudah ada.");
  }
}