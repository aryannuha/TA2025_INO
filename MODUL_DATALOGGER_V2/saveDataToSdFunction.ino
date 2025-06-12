/*
 Nama File      : saveDataToSdFunction.ino
 Tanggal Update : 12 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
   1. Fungsi ini menyimpan data dari matriks dataMatrix ke dalam file CSV di SD Card.
   2. Data yang disimpan mencakup waktu, suhu indoor, kelembaban indoor, suhu outdoor, kelembaban outdoor, CO2, kecepatan angin, PAR, curah hujan, dan data daya DC/AC.
   3. Data disimpan dalam format CSV dengan pemisah titik koma (;).
   4. Fungsi ini juga menangani penulisan data ke dalam file, termasuk penanganan kesalahan saat membuka file.
*/

void saveDataToSD() {
  DateTime now = rtc.now();
  char waktuStr[25]; // Increased size for safety
  sprintf(waktuStr, "%04d-%02d-%02d %02d:%02d:%02d",
          now.year(), now.month(), now.day(),
          now.hour(), now.minute(), now.second());

  File file = SD.open(filename, FILE_APPEND);
  if (file) {
    file.print(waktuStr);
    file.print(";");

    // Helper function to find the index of a module based on its code.
    // Returns -1 if the module code is not found.
    auto getModuleIndex = [&](const String& moduleCode) {
      for (int i = 0; i < numModules; i++) {
        if (moduleNames[i] == moduleCode) {
          return i;
        }
      }
      return -1; // Not found
    };

    // Helper function to safely get data from the dataMatrix.
    // It checks if the module and variable exist and if data has been received.
    // Returns "0.0" as a default if data is not available.
    auto getData = [&](const String& moduleCode, int varCode) {
      int moduleIdx = getModuleIndex(moduleCode);
      if (moduleIdx != -1 && varCode >= 0 && varCode < MAX_VARIABLES_PER_MODULE) {
        // Check if data is valid (i.e., it has been updated since initialization)
        if (dataMatrix[moduleIdx][varCode].kodeVariabel == varCode) {
          return String(dataMatrix[moduleIdx][varCode].kodeData);
        }
      }
      return String("0.0"); // Return default string if data not found or not yet updated
    };

    // Write data according to the header in setupSD_Card, using the provided mappings.
    // The order here MUST match the column order in `setupSDFunction.ino`.
    
    // Suhu Indoor:           kodeModul = "02", kodeVariabel = 11
    file.print(getData("02", 11));
    file.print(";");

    // Kelembaban Indoor:     kodeModul = "02", kodeVariabel = 12
    file.print(getData("02", 12));
    file.print(";");

    // Suhu Outdoor:          kodeModul = "07", kodeVariabel = 11
    file.print(getData("07", 11));
    file.print(";");

    // Kelembaban Outdoor:    kodeModul = "07", kodeVariabel = 12
    file.print(getData("07", 12));
    file.print(";");

    // CO2:                   kodeModul = "03", kodeVariabel = 11
    file.print(getData("03", 11));
    file.print(";");

    // Kecepatan Angin:       kodeModul = "04", kodeVariabel = 11
    file.print(getData("04", 11));
    file.print(";");

    // PAR:                   kodeModul = "06", kodeVariabel = 11
    file.print(getData("06", 11));
    file.print(";");

    // Curah Hujan:           kodeModul = "05", kodeVariabel = 11
    file.print(getData("05", 11));
    file.print(";");

    // DC Power (Asumsi): V DC, I DC, P DC. kodeModul = "08", kodeVariabel = 11, 12, 13
    // file.print(getData("08", 11)); // V DC
    // file.print(";");
    // file.print(getData("08", 12)); // I DC
    // file.print(";");
    // file.print(getData("08", 13)); // P DC
    // file.print(";");

    // AC Power: V AC, I AC, P AC. kodeModul = "09", kodeVariabel = 11, 12, 13
    file.print(getData("09", 11)); // V AC
    file.print(";");
    file.print(getData("09", 12)); // I AC
    file.print(";");
    file.print(getData("09", 13)); // P AC
    file.print(";");

    // GPS: Latitude, Longitude. kodeModul = "10", kodeVariabel = 11, 12
    file.print(getData("10", 11)); // Latitude
    file.print(";");
    file.println(getData("10", 12)); // Longitude

    file.close();
    Serial.println("Data tersimpan ke SD Card dari dataMatrix.");
  } else {
    Serial.println("Gagal membuka file untuk menulis.");
  }
}