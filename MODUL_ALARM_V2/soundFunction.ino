/*
 Nama File      : soundFunction.ino
 Tanggal Update : 12 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
   1. Fungsi ini mengelola suara buzzer untuk modul alarm.
   2. Fungsi ini menggunakan pendekatan non-blocking untuk menghindari penundaan dalam eksekusi program.
   3. Fungsi ini mengatur durasi nada buzzer berdasarkan kode alarm yang diterima.
   4. Fungsi ini mengaktifkan atau menonaktifkan nada buzzer berdasarkan waktu yang telah berlalu.
   5. Fungsi ini memastikan bahwa buzzer tidak berbunyi terus-menerus, tetapi hanya sesuai dengan kondisi alarm yang ada.
   6. Fungsi ini juga mengatur nada buzzer yang berbeda untuk kode alarm yang berbeda.
   7. Fungsi ini menggunakan millis() untuk mengelola waktu secara non-blocking.
*/

// --- Fungsi untuk mengelola suara buzzer (non-blocking) ---
void triggerBuzzer() {
    unsigned long currentTime = millis();
    if (currentAlarmCode == 0) {
        if(buzzerOn) { noTone(buzzPin); buzzerOn = false; }
        return;
    }
    int toneDuration = (currentAlarmCode == 1 || currentAlarmCode == 4) ? 250 : 600;
    if (buzzerOn) {
        if (currentTime - buzzerStartTime >= toneDuration) { noTone(buzzPin); buzzerOn = false; buzzerStartTime = currentTime; }
    } else {
        if (currentTime - buzzerStartTime >= toneDuration) { tone(buzzPin, (currentAlarmCode == 1 || currentAlarmCode == 4) ? 1500 : 800); buzzerOn = true; buzzerStartTime = currentTime; }
    }
}