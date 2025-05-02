// // ========================================== FUNGSI displayLCD() ===========================================================================================
// void displayLCD() {
//   lcd.clear();
  
//   // Display different data based on displayMode
//   switch(displayMode) {
//     case 0:  // Suhu Indoor
//       displaySuhuIndoor();
//       break;
      
//     case 1:  // Kelembaban Indoor
//       displayKelembabanIndoor();
//       break;
      
//     case 2:  // Suhu Outdoor
//       displaySuhuOutdoor();
//       break;
      
//     case 3:  // Kelembaban Outdoor
//       displayKelembabanOutdoor();
//       break;
      
//     case 4:  // CO2
//       displayCO2();
//       break;
      
//     case 5:  // Wind Speed
//       displayWindSpeed();
//       break;
      
//     case 6:  // Rainfall
//       displayRainfall();
//       break;
      
//     case 7:  // PAR
//       displayPAR();
//       break;
//   }
  
//   // Increment display mode or reset to 0
//   displayMode = (displayMode + 1) % 8;  // 8 is the number of different displays
// }
// // ================================================ AKHIR FUNGSI displayLCD() ==============================================================================

// // ============================================= FUNGSI displaySuhuIndoor() ================================================================================
// void displaySuhuIndoor() {
//   // kolom 0, baris 0
//   lcd.setCursor(0, 0);
//   lcd.print(suhuData.berita);
  
//   // kolom 0, baris 1
//   lcd.setCursor(0, 1);
//   lcd.print("SUHU: ");
  
//   // kolom 9, baris 1
//   lcd.setCursor(9, 1);
//   lcd.print(suhuData.data);
//   lcd.print(" \xDF""C");
// }
// // ========================================== AKHIR FUNGSI displaySuhuIndoor() ==============================================================================

// // ======================================================== FUNGSI displayKelembabanIndoor() ================================================================
// void displayKelembabanIndoor() {  
//   // Kolom 0, baris 0
//   lcd.setCursor(0, 0);
//   lcd.print(kelembabanData.berita);
  
//   // kolom 0, baris 1
//   lcd.setCursor(0, 1);
//   lcd.print("KELEMBABAN: ");

//   // kolom 14, baris 1
//   lcd.setCursor(14, 1);
//   lcd.print(kelembabanData.data);
//   lcd.print(" %");
// }
// // ============================================== AKHIR FUNGSI displayKelembabanOutdoor() ===================================================================

// // ============================================== FUNGSI displaySuhuOutdoor() ===============================================================================
// void displaySuhuOutdoor() {
//    // kolom 0, baris 0
//   lcd.setCursor(0, 0);
//   lcd.print(suhuOutData.berita);
  
//   // kolom 0, baris 1
//   lcd.setCursor(0, 1);
//   lcd.print("SUHU: ");
  
//   // kolom 9, baris 1
//   lcd.setCursor(9, 1);
//   lcd.print(suhuOutData.data);
//   lcd.print(" \xDF""C");
// }
// // ================================================== AKHIR FUNGSI displaySuhuOutdoor() =====================================================================

// // ================================================== FUNGSI displayKelembabanOutdoor() =====================================================================
// void displayKelembabanOutdoor() {
//   lcd.setCursor(0, 0);
//   lcd.print(kelembabanOutData.berita);
  
//   lcd.setCursor(0, 1);
//   lcd.print("KELEMBABAN: ");
  
//   lcd.setCursor(14, 1);
//   lcd.print(kelembabanOutData.data);
//   lcd.print(" %");
// }
// // ==================================================== AKHIR FUNGSI displayKelembabanOutdoor() =============================================================

// // ============================================ FUNGSI displayCO2() =========================================================================================
// void displayCO2() {
//   lcd.setCursor(0, 0);
//   lcd.print(co2Data.berita);
  
//   lcd.setCursor(0, 1);
//   lcd.print("CO2: ");
  
//   lcd.setCursor(9, 1);
//   lcd.print(co2Data.data);
//   lcd.print(" PPM");
// }
// // ========================================= AKHIR FUNGSI displayCO2() ======================================================================================

// // ======================================================= FUNGSI displayWindspeed() ========================================================================
// void displayWindSpeed() {
//   lcd.setCursor(0, 0);
//   lcd.print(windspeedData.berita);
  
//   lcd.setCursor(0, 1);
//   lcd.print("WINDSPEED: ");
  
//   lcd.setCursor(14, 1);
//   lcd.print(windspeedData.data);
//   lcd.print(" m/s");
// }
// // ======================================================== AKHIR FUNGSI displayWindspeed() ================================================================

// // ======================================================== FUNGSI displayRainfall() =======================================================================
// void displayRainfall() {
//   lcd.setCursor(0, 0);
//   lcd.print(rainfallData.berita);
  
//   lcd.setCursor(0, 1);
//   lcd.print("CURAH HUJAN: ");
  
//   lcd.setCursor(14, 1);
//   lcd.print(rainfallData.data);
//   lcd.print(" mm");
// }
// // ======================================================= AKHIR FUNGSI displayRainfall() ==================================================================

// // =================================================== FUNGSI displayPAR() =================================================================================
// void displayPAR() {
//   lcd.setCursor(0, 0);
//   lcd.print(parData.berita);
  
//   lcd.setCursor(0, 1);
//   lcd.print("PAR: ");
  
//   lcd.setCursor(9, 1);
//   lcd.print(parData.data);
//   lcd.print(" \xE4mol/m\xB2/s"); // µmol/m²/s
// }
// // ===================================================== AKHIR FUNGSI displayPAR() =========================================================================