// =========================================== FUNGSI displaySerial() UNTUK MENAMPILKAN DATA YANG DIKIRIM KE MQTT ========================================
void displaySerial(){
  Serial.print("Suhu -> ");
  Serial.print(suhuData.kodeModul);
  Serial.print(" ");
  Serial.print(suhuData.kodeVariabel);
  Serial.print(" ");
  Serial.print(suhuData.data);
  Serial.print(" ");
  Serial.print(suhuData.kodeAlarm);
  Serial.print(" ");
  Serial.print(suhuData.berita); 
  Serial.println(); 

  Serial.print("Kelembaban -> ");
  Serial.print(kelembabanData.kodeModul);
  Serial.print(" ");
  Serial.print(kelembabanData.kodeVariabel);
  Serial.print(" ");
  Serial.print(kelembabanData.data);
  Serial.print(" ");
  Serial.print(kelembabanData.kodeAlarm);
  Serial.print(" ");
  Serial.print(kelembabanData.berita); 
  Serial.println(); 

  Serial.print("CO2 -> ");
  Serial.print(co2Data.kodeModul);
  Serial.print(" ");
  Serial.print(co2Data.kodeVariabel);
  Serial.print(" ");
  Serial.print(co2Data.data);
  Serial.print(" ");
  Serial.print(co2Data.kodeAlarm);
  Serial.print(" ");
  Serial.print(co2Data.berita); 
  Serial.println(); 

  Serial.print("Rainfall -> ");
  Serial.print(rainfallData.kodeModul);
  Serial.print(" ");
  Serial.print(rainfallData.kodeVariabel);
  Serial.print(" ");
  Serial.print(rainfallData.data);
  Serial.print(" ");
  Serial.print(rainfallData.kodeAlarm);
  Serial.print(" ");
  Serial.print(rainfallData.berita); 
  Serial.println(); 

  Serial.print("Windspeed -> ");
  Serial.print(windspeedData.kodeModul);
  Serial.print(" ");
  Serial.print(windspeedData.kodeVariabel);
  Serial.print(" ");
  Serial.print(windspeedData.data);
  Serial.print(" ");
  Serial.print(windspeedData.kodeAlarm);
  Serial.print(" ");
  Serial.print(windspeedData.berita); 
  Serial.println(); 

  Serial.print("PAR -> ");
  Serial.print(parData.kodeModul);
  Serial.print(" ");
  Serial.print(parData.kodeVariabel);
  Serial.print(" ");
  Serial.print(parData.data);
  Serial.print(" ");
  Serial.print(parData.kodeAlarm);
  Serial.print(" ");
  Serial.print(parData.berita); 
  Serial.println(); 

  Serial.print("Suhu Out -> ");
  Serial.print(suhuOutData.kodeModul);
  Serial.print(" ");
  Serial.print(suhuOutData.kodeVariabel);
  Serial.print(" ");
  Serial.print(suhuOutData.data);
  Serial.print(" ");
  Serial.print(suhuOutData.kodeAlarm);
  Serial.print(" ");
  Serial.print(suhuOutData.berita); 
  Serial.println(); 

  Serial.print("Kelembaban Out -> ");
  Serial.print(kelembabanOutData.kodeModul);
  Serial.print(" ");
  Serial.print(kelembabanOutData.kodeVariabel);
  Serial.print(" ");
  Serial.print(kelembabanOutData.data);
  Serial.print(" ");
  Serial.print(kelembabanOutData.kodeAlarm);
  Serial.print(" ");
  Serial.print(kelembabanOutData.berita); 
  Serial.println(); 

  Serial.print("Tegangan DC -> ");
  Serial.print(tegangandcData.kodeModul);
  Serial.print(" ");
  Serial.print(tegangandcData.kodeVariabel);
  Serial.print(" ");
  Serial.print(tegangandcData.data);
  Serial.print(" ");
  Serial.print(tegangandcData.kodeAlarm);
  Serial.print(" ");
  Serial.print(tegangandcData.berita); 
  Serial.println(); 

  Serial.print("Arus DC -> ");
  Serial.print(arusdcData.kodeModul);
  Serial.print(" ");
  Serial.print(arusdcData.kodeVariabel);
  Serial.print(" ");
  Serial.print(arusdcData.data);
  Serial.print(" ");
  Serial.print(arusdcData.kodeAlarm);
  Serial.print(" ");
  Serial.print(arusdcData.berita); 
  Serial.println(); 

  Serial.print("Daya DC -> ");
  Serial.print(dayadcData.kodeModul);
  Serial.print(" ");
  Serial.print(dayadcData.kodeVariabel);
  Serial.print(" ");
  Serial.print(dayadcData.data);
  Serial.print(" ");
  Serial.print(dayadcData.kodeAlarm);
  Serial.print(" ");
  Serial.print(dayadcData.berita); 
  Serial.println(); 

  Serial.print("Tegangan AC -> ");
  Serial.print(teganganacData.kodeModul);
  Serial.print(" ");
  Serial.print(teganganacData.kodeVariabel);
  Serial.print(" ");
  Serial.print(teganganacData.data);
  Serial.print(" ");
  Serial.print(teganganacData.kodeAlarm);
  Serial.print(" ");
  Serial.print(teganganacData.berita); 
  Serial.println(); 

  Serial.print("Arus AC -> ");
  Serial.print(arusacData.kodeModul);
  Serial.print(" ");
  Serial.print(arusacData.kodeVariabel);
  Serial.print(" ");
  Serial.print(arusacData.data);
  Serial.print(" ");
  Serial.print(arusacData.kodeAlarm);
  Serial.print(" ");
  Serial.print(arusacData.berita); 
  Serial.println(); 

  Serial.print("Daya AC -> ");
  Serial.print(dayaacData.kodeModul);
  Serial.print(" ");
  Serial.print(dayaacData.kodeVariabel);
  Serial.print(" ");
  Serial.print(dayaacData.data);
  Serial.print(" ");
  Serial.print(dayaacData.kodeAlarm);
  Serial.print(" ");
  Serial.print(dayaacData.berita); 
  Serial.println(); 
}
// ============================================================ AKHIR FUNGSI displaySerial() =============================================================