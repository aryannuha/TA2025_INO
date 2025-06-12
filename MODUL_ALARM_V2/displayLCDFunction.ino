/*
 Nama File      : displayLCDFunction.ino
 Tanggal Update : 12 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
   1. Fungsi ini mengelola tampilan LCD untuk modul alarm.
   2. Fungsi ini menggunakan pendekatan non-blocking untuk memperbarui tampilan LCD.
   3. Fungsi ini menampilkan data sensor dari berbagai modul dalam format yang mudah dibaca.
   4. Fungsi ini mendukung mode tampilan otomatis dan manual.
   5. Fungsi ini mengelola perubahan tampilan berdasarkan waktu dan interaksi pengguna.
   6. Fungsi ini juga menampilkan status alarm dan berita terkait pada LCD.
*/

// --- Fungsi untuk memperbarui tampilan LCD (otomatis atau manual) ---
void updateDisplay() {
    static int lastDrawnIndex = -1;
    static int lastDrawnMode = -1;

    if (lastDrawnIndex == currentDisplayIndex && lastDrawnMode == displayMode) {
        if (displayMode == 0) {
            int totalData = countValidData();
            if (totalData > 0 && millis() - lastDisplayChange >= displayInterval) {
                lastDisplayChange = millis();
                currentDisplayIndex = (currentDisplayIndex + 1) % totalData;
            }
        }
        return;
    }
    
    int totalData = countValidData();
    if (totalData == 0) {
        lcd.clear(); lcd.setCursor(0,0); lcd.print("MODUL ALARM V2"); lcd.setCursor(0,1); lcd.print("   Tidak Ada Data   ");
    } else if (displayMode == 1 && currentDisplayIndex >= totalData) {
         displayReturnMenu();
    } else {
        int targetIndex = currentDisplayIndex;
        int dataCount = -1;
        for (int i=0; i<numModules; i++) for (int j=0; j<MAX_VARIABLES_PER_MODULE; j++) if(dataMatrix[i][j].isUsed) {
            dataCount++;
            if (dataCount == targetIndex) { displayData(i, j); goto redraw_done; }
        }
    }
redraw_done:
    lastDrawnIndex = currentDisplayIndex;
    lastDrawnMode = displayMode;
}

// --- Fungsi untuk menampilkan data pada LCD ---
void displayData(int moduleIdx, int varIdx) {
    lcd.clear();
    lcd.setCursor(0, 0); lcd.print("M:" + dataMatrix[moduleIdx][varIdx].kodeModul + " V:" + String(dataMatrix[moduleIdx][varIdx].kodeVariabel));
    lcd.setCursor(0, 1); lcd.print("Data: " + String(dataMatrix[moduleIdx][varIdx].kodeData, 1));
    lcd.setCursor(0, 2); lcd.print("Alarm: " + String(dataMatrix[moduleIdx][varIdx].kodeAlarm));
    // Tampilkan status hening/abaikan
    if (dataMatrix[moduleIdx][varIdx].alarmSilencedTime > 0) {
        lcd.print(" (Hening 2m)");
    } else if (dataMatrix[moduleIdx][varIdx].warningCleared) {
        lcd.print(" (Diabaikan)");
    }
    String beritaToShow = dataMatrix[moduleIdx][varIdx].berita;
    if (beritaToShow.length() > 20) beritaToShow = beritaToShow.substring(0, 20);
    lcd.setCursor(0, 3); lcd.print(beritaToShow);
}

// --- Fungsi untuk menampilkan menu "Kembali ke Default" ---
void displayReturnMenu() {
    lcd.clear();
    lcd.setCursor(0, 1); lcd.print("   Kembali ke Mode   ");
    lcd.setCursor(0, 2); lcd.print("      Otomatis?      ");
}