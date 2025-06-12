/*
 Nama File      : ledFunction.ino
 Tanggal Update : 12 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
   1. Fungsi ini mengelola status LED untuk modul alarm.
   2. Fungsi ini menggunakan pendekatan non-blocking untuk menghindari penundaan dalam eksekusi program.
   3. Fungsi ini mengatur LED berdasarkan prioritas alarm yang diterima dari data sensor.
   4. Fungsi ini memastikan bahwa LED merah berkedip untuk kondisi bahaya, LED kuning menyala untuk kondisi peringatan, dan LED hijau menyala untuk kondisi normal.
   5. Fungsi ini menggunakan millis() untuk mengelola waktu secara non-blocking.
*/

// --- Fungsi untuk memperbarui status LED berdasarkan prioritas alarm ---
void updateLeds() {
    // Variabel statis untuk logika kedip non-blocking
    static unsigned long lastBlinkTime = 0;
    static bool redLedState = LOW;
    const long blinkInterval = 400; // Kecepatan kedip (400ms on, 400ms off)

    // --- Tentukan status alarm saat ini ---
    bool dangerActive = false;
    bool warningActive = false;
    
    for (int i = 0; i < numModules; i++) {
        for (int j = 0; j < MAX_VARIABLES_PER_MODULE; j++) {
            if (dataMatrix[i][j].isUsed) {
                int alarmCode = dataMatrix[i][j].kodeAlarm;
                
                if (alarmCode == 1 || alarmCode == 4) {
                    dangerActive = true;
                    goto end_led_check;
                }
                if (alarmCode == 2 || alarmCode == 3) {
                    warningActive = true;
                }
            }
        }
    }
end_led_check:

    // --- Kontrol LED berdasarkan status ---

    // 1. Jika ada kondisi BAHAYA
    if (dangerActive) {
        // Pastikan LED lain mati
        digitalWrite(ledKuningPin, LOW);
        digitalWrite(ledHijauPin, LOW);

        // Logika untuk membuat LED merah berkedip
        if (millis() - lastBlinkTime > blinkInterval) {
            lastBlinkTime = millis();       // Reset timer
            redLedState = !redLedState;     // Balikkan keadaan LED (ON -> OFF -> ON)
            digitalWrite(ledMerahPin, redLedState);
        }
    } 
    // 2. Jika ada kondisi PERINGATAN (tapi tidak ada bahaya)
    else if (warningActive) {
        digitalWrite(ledMerahPin, LOW);   // Pastikan LED merah mati
        digitalWrite(ledKuningPin, HIGH); // Nyalakan LED kuning (stabil)
        digitalWrite(ledHijauPin, LOW);
    } 
    // 3. Jika semua NORMAL
    else {
        digitalWrite(ledMerahPin, LOW);   // Pastikan LED merah mati
        digitalWrite(ledKuningPin, LOW);
        digitalWrite(ledHijauPin, HIGH);  // Nyalakan LED hijau (stabil)
    }
}