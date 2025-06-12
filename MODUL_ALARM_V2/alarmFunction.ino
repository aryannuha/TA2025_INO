/*
 Nama File      : alarmFunction.ino
 Tanggal Update : 12 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
   1. Fungsi ini mengelola logika alarm untuk modul alarm.
   2. Fungsi ini menangani input tombol untuk mengubah mode tampilan dan mengelola alarm.
   3. Fungsi ini memeriksa dan mengaktifkan alarm berdasarkan data sensor yang diterima.
   4. Fungsi ini menggunakan pendekatan non-blocking untuk menghindari penundaan dalam eksekusi program.
   5. Fungsi ini mengelola status alarm global dan memastikan bahwa alarm yang aktif ditangani dengan benar.
*/

// --- Fungsi untuk menangani input tombol (non-blocking) ---
void handleButtons() {
    static int button1State = HIGH, lastButton1State = HIGH;
    static int button2State = HIGH, lastButton2State = HIGH;
    static unsigned long lastDebounceTime1 = 0, lastDebounceTime2 = 0;
    unsigned long debounceDelay = 50, currentTime = millis();

    // Proses Tombol 1
    int reading1 = digitalRead(buttonPin);
    if (reading1 != lastButton1State) { lastDebounceTime1 = currentTime; }
    if ((currentTime - lastDebounceTime1) > debounceDelay) {
        if (reading1 != button1State) {
            button1State = reading1;
            if (button1State == LOW) { // Aksi saat tombol ditekan
                if (displayMode == 0) {
                    displayMode = 1;
                    currentDisplayIndex = 0;
                } else {
                    int totalData = countValidData();
                    currentDisplayIndex = (totalData > 0) ? (currentDisplayIndex + 1) % (totalData + 1) : 0;
                }
            }
        }
    }
    lastButton1State = reading1;

    // Proses Tombol 2
    int reading2 = digitalRead(buttonPin2);
    if (reading2 != lastButton2State) { lastDebounceTime2 = currentTime; }
    if ((currentTime - lastDebounceTime2) > debounceDelay) {
        if (reading2 != button2State) {
            button2State = reading2;
            if (button2State == LOW) { // Aksi saat tombol ditekan
                if (displayMode == 1) { 
                    int totalData = countValidData();
                    if (currentDisplayIndex >= totalData) { // Kembali ke mode otomatis
                        displayMode = 0;
                        currentDisplayIndex = 0;
                        lastDisplayChange = millis();
                    } else { // Matikan alarm
                        int targetIndex = currentDisplayIndex;
                        int dataCount = -1;
                        for (int i=0; i<numModules; i++) for (int j=0; j<MAX_VARIABLES_PER_MODULE; j++) if(dataMatrix[i][j].isUsed) {
                            dataCount++;
                            if (dataCount == targetIndex) {
                                int alarmCode = dataMatrix[i][j].kodeAlarm;
                                if (alarmCode == 1 || alarmCode == 4) {
                                    dataMatrix[i][j].alarmSilencedTime = millis();
                                } else if (alarmCode == 2 || alarmCode == 3) {
                                    dataMatrix[i][j].warningCleared = true;
                                }
                                goto action_done;
                            }
                        }
                        action_done:;
                    }
                }
            }
        }
    }
    lastButton2State = reading2;
}

// --- Fungsi untuk memeriksa dan mengaktifkan alarm ---
void checkAlarms() {
    unsigned long currentTime = millis();
    int highestPriorityAlarm = 0;
    for (int i = 0; i < numModules; i++) {
        for (int j = 0; j < MAX_VARIABLES_PER_MODULE; j++) {
            if (dataMatrix[i][j].isUsed && dataMatrix[i][j].kodeAlarm > 0) {
                // Periksa apakah alarm bahaya harus aktif kembali
                if (dataMatrix[i][j].alarmSilencedTime != 0 && currentTime - dataMatrix[i][j].alarmSilencedTime > alarmDangerDuration) {
                    dataMatrix[i][j].alarmSilencedTime = 0;
                }
                // Lewati jika alarm bahaya sedang diheningkan
                if (dataMatrix[i][j].alarmSilencedTime != 0) continue;
                // Lewati jika alarm peringatan sudah diabaikan
                if (dataMatrix[i][j].warningCleared) continue;
                
                int alarmCode = dataMatrix[i][j].kodeAlarm;
                if (alarmCode == 1 || alarmCode == 4) { highestPriorityAlarm = alarmCode; goto end_alarm_check; }
                highestPriorityAlarm = max(highestPriorityAlarm, alarmCode);
            }
        }
    }
end_alarm_check:
    currentAlarmCode = highestPriorityAlarm;
}

// Fungsi untuk mencari jumlah alarm yang aktif
int countValidData() {
    int count = 0;
    for (int i = 0; i < numModules; i++) for (int j = 0; j < MAX_VARIABLES_PER_MODULE; j++) if(dataMatrix[i][j].isUsed) count++;
    return count;
}