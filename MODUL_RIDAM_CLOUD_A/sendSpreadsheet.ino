/* 
 Nama File      : sendSpreadsheetFunction.ino
 Tanggal Update : 09 Juni 2025
 Dibuat oleh    : Ammar Aryan Nuha
 Penjelasan     : 
    1. Fungsi ini digunakan untuk mengirim data yang telah diproses ke Google Sheets menggunakan Google Apps Script.
    2. Data yang dikirim meliputi suhu dalam ruangan, kelembapan dalam ruangan, suhu luar ruangan, kelembapan luar ruangan, PAR, curah hujan, kecepatan angin, CO2, latitude, longitude, tegangan AC, arus AC, dan daya AC.
    3. Fungsi ini mengatur koneksi HTTPS ke URL Google Apps Script yang telah didefinisikan.
    4. Fungsi ini mengirim data dalam format URL-encoded melalui metode POST.
    5. Fungsi ini juga menangani respons dari Google Sheets dan menampilkan kode respons serta pesan di serial monitor.
    6. Fungsi ini digunakan untuk mengirim data secara periodik sesuai dengan interval yang telah ditentukan.
*/

// ================================================ FUNGSI sendToSpreadsheet() KE GOOGLE SHEETS ================================================================
void sendToSpreadsheet() {
  HTTPClient http;

  // Begin the connection to your Google Apps Script URL
  // We use espClient (a WiFiClientSecure object) to handle the HTTPS connection
  http.begin(espClient, scriptUrl);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  // =================================== GATHER AND MAP DATA HERE ===================================
  // IMPORTANT: Adjust the kodeModul and kodeVariabel to match your setup.
  // These are examples based on your description.
  // ================================================================================================
  float temp_in     = getValueFromMatrix("02", 11);
  float humid_in    = getValueFromMatrix("02", 12);
  float temp_out    = getValueFromMatrix("07", 11); // <-- EXAMPLE, please adjust
  float humid_out   = getValueFromMatrix("07", 12); // <-- EXAMPLE, please adjust
  float par         = getValueFromMatrix("06", 11); // <-- EXAMPLE, please adjust
  float rainfall    = getValueFromMatrix("05", 11); // <-- EXAMPLE, please adjust
  float windspeed   = getValueFromMatrix("04", 11); // <-- EXAMPLE, please adjust
  float co2         = getValueFromMatrix("04", 11); // <-- EXAMPLE, please adjust
  float latitude    = getValueFromMatrix("10", 11); // <-- EXAMPLE, please adjust
  float longitude   = getValueFromMatrix("10", 12); // <-- EXAMPLE, please adjust
  float voltageAc   = getValueFromMatrix("09", 11); // <-- EXAMPLE, please adjust
  float currentAc   = getValueFromMatrix("09", 12); // <-- EXAMPLE, please adjust
  float powerAc   = getValueFromMatrix("09", 13); // <-- EXAMPLE, please adjust

  // Create the payload string for the POST request.
  // The keys (e.g., "temp_in") must match the keys used in the Apps Script (e.parameter.temp_in)
  String payload = "temp_in=" + String(temp_in) +
                   "&humid_in=" + String(humid_in) +
                   "&temp_out=" + String(temp_out) +
                   "&humid_out=" + String(humid_out) +
                   "&par=" + String(par) +
                   "&rainfall=" + String(rainfall) +
                   "&windspeed=" + String(windspeed) +
                   "&co2=" + String(co2) +
                   "&latitude=" + String(latitude, 6) +    // Use 6 decimal places for lat/lon
                   "&longitude=" + String(longitude, 6) +
                   "&voltageAc=" + String(voltageAc) +
                   "&currentAc=" + String(currentAc) +
                   "&powerAc=" + String(powerAc);

  Serial.println("Sending data to Google Sheet...");
  // Send the POST request
  int httpResponseCode = http.POST(payload);

  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.print("Google Sheet Response code: ");
    Serial.println(httpResponseCode);
    Serial.print("Response: ");
    Serial.println(response);
  } else {
    Serial.print("Error sending to Google Sheet. Code: ");
    Serial.println(httpResponseCode);
  }

  // End the connection
  http.end();
}
// =============================================== AKHIR FUNGSI sendToSpreadsheet() ============================================================================

// Returns the kodeData for a given module and variable, or 0.0 if not found.
// This version is more robust and correctly searches all variables for a module.
float getValueFromMatrix(String targetModule, int targetVariable) {
  for (int i = 0; i < numModules; i++) {
    // First, find the correct module by its name
    if (moduleNames[i] == targetModule) {
      // Once the module is found, search through all its possible variables
      for (int j = 0; j < MAX_VARIABLES_PER_MODULE; j++) {
        // Check if the variable code at this position matches our target
        if (dataMatrix[i][j].kodeVariabel == targetVariable) {
          return dataMatrix[i][j].kodeData; // Found it! Return the data.
        }
      }
    }
  }
  return 0.0; // Return a default value if not found after searching everywhere.
}