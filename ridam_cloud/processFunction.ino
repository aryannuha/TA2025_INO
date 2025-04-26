// ================================ FUNGSI proses() UNTUK KONVERSI MENJADI STRING SEBELUM KIRIM KE MQTT =====================================================
void proses(){
  // KONVERSI UNTUK SUHU INDOOR
  strcpy(kodeModulSuhuIn_str, suhuData.kodeModul.c_str());
  itoa(suhuData.kodeVariabel, kodeVariabelSuhuIn_str, 10);
  dtostrf(suhuData.data, 4, 3, kodeDataSuhuIn_str);
  itoa(suhuData.kodeAlarm, kodeAlarmSuhuIn_str, 10);
  strcpy(beritaSuhuIn_str, suhuData.berita.c_str());

  // KONVERSI UNTUK KELEMBABAN INDOOR
  strcpy(kodeModulKelembabanIn_str, kelembabanData.kodeModul.c_str());
  itoa(kelembabanData.kodeVariabel, kodeVariabelKelembabanIn_str, 10);
  dtostrf(kelembabanData.data, 4, 3, kodeDataKelembabanIn_str);
  itoa(kelembabanData.kodeAlarm, kodeAlarmKelembabanIn_str, 10);
  strcpy(beritaKelembabanIn_str, kelembabanData.berita.c_str());

  // KONVERSI UNTUK SUHU OUTDOOR
  strcpy(kodeModulSuhuOut_str, suhuOutData.kodeModul.c_str());
  itoa(suhuOutData.kodeVariabel, kodeVariabelSuhuOut_str, 10);
  dtostrf(suhuOutData.data, 4, 3, kodeDataSuhuOut_str);
  itoa(suhuOutData.kodeAlarm, kodeAlarmSuhuOut_str, 10);
  strcpy(beritaSuhuOut_str, suhuOutData.berita.c_str());

  // KONVERSI UNTUK KELEMBABAN OUTDOOR
  strcpy(kodeModulKelembabanOut_str, kelembabanOutData.kodeModul.c_str());
  itoa(kelembabanOutData.kodeVariabel, kodeVariabelKelembabanOut_str, 10);
  dtostrf(kelembabanOutData.data, 4, 3, kodeDataKelembabanOut_str);
  itoa(kelembabanOutData.kodeAlarm, kodeAlarmKelembabanOut_str, 10);
  strcpy(beritaKelembabanOut_str, kelembabanOutData.berita.c_str());

  // KONVERSI UNTUK CO2
  strcpy(kodeModulCo2_str, co2Data.kodeModul.c_str());
  itoa(co2Data.kodeVariabel, kodeVariabelCo2_str, 10);
  dtostrf(co2Data.data, 4, 3, kodeDataCo2_str);
  itoa(co2Data.kodeAlarm, kodeAlarmCo2_str, 10);
  strcpy(beritaCo2_str, co2Data.berita.c_str());

  // KONVERSI UNTUK KECEPATAN ANGIN
  strcpy(kodeModulWindspeed_str, windspeedData.kodeModul.c_str());
  itoa(windspeedData.kodeVariabel, kodeVariabelWindspeed_str, 10);
  dtostrf(windspeedData.data, 4, 3, kodeDataWindspeed_str);
  itoa(windspeedData.kodeAlarm, kodeAlarmWindspeed_str, 10);
  strcpy(beritaWindspeed_str, windspeedData.berita.c_str());

  // KONVERSI UNTUK CURAH HUJAN
  strcpy(kodeModulRainfall_str, rainfallData.kodeModul.c_str());
  itoa(rainfallData.kodeVariabel, kodeVariabelRainfall_str, 10);
  dtostrf(rainfallData.data, 4, 3, kodeDataRainfall_str);
  itoa(rainfallData.kodeAlarm, kodeAlarmRainfall_str, 10);
  strcpy(beritaRainfall_str, rainfallData.berita.c_str());

  // KONVERSI UNTUK PAR
  strcpy(kodeModulPar_str, parData.kodeModul.c_str());
  itoa(parData.kodeVariabel, kodeVariabelPar_str, 10);
  dtostrf(parData.data, 4, 3, kodeDataPar_str);
  itoa(parData.kodeAlarm, kodeAlarmPar_str, 10);
  strcpy(beritaPar_str, parData.berita.c_str());
}
// ====================================================== AKHIR FUNGSI proses() ==============================================================================

// ======================================== FUNGSI parsing() UNTUK MEMASUKAN DATA JSON KE STRUCT MASING-MASING =================================================
void parsing(){
  if(kodeModul_R == "02" && kodeVariabel_R == 11){
    suhuData.kodeModul = kodeModul_R;
    suhuData.kodeVariabel = kodeVariabel_R;
    suhuData.data = data_R;
    suhuData.kodeAlarm = kodeAlarm_R;
    suhuData.berita = berita_R;       
  }else if(kodeModul_R == "02" && kodeVariabel_R == 12){
    kelembabanData.kodeModul = kodeModul_R;
    kelembabanData.kodeVariabel = kodeVariabel_R;
    kelembabanData.data = data_R;
    kelembabanData.kodeAlarm = kodeAlarm_R;
    kelembabanData.berita = berita_R;  
  }else if(kodeModul_R == "03"){
    co2Data.kodeModul = kodeModul_R;
    co2Data.kodeVariabel = kodeVariabel_R;
    co2Data.data = data_R;
    co2Data.kodeAlarm = kodeAlarm_R;
    co2Data.berita = berita_R;  
  }else if(kodeModul_R == "04"){
    windspeedData.kodeModul = kodeModul_R;
    windspeedData.kodeVariabel = kodeVariabel_R;
    windspeedData.data = data_R;
    windspeedData.kodeAlarm = kodeAlarm_R;
    windspeedData.berita = berita_R;  
  }else if(kodeModul_R == "05"){
    rainfallData.kodeModul = kodeModul_R;
    rainfallData.kodeVariabel = kodeVariabel_R;
    rainfallData.data = data_R;
    rainfallData.kodeAlarm = kodeAlarm_R;
    rainfallData.berita = berita_R;  
  }else if(kodeModul_R == "06"){
    parData.kodeModul = kodeModul_R;
    parData.kodeVariabel = kodeVariabel_R;
    parData.data = data_R;
    parData.kodeAlarm = kodeAlarm_R;
    parData.berita = berita_R;  
  }else if(kodeModul_R == "07" && kodeVariabel_R == 11){
    suhuOutData.kodeModul = kodeModul_R;
    suhuOutData.kodeVariabel = kodeVariabel_R;
    suhuOutData.data = data_R;
    suhuOutData.kodeAlarm = kodeAlarm_R;
    suhuOutData.berita = berita_R;  
  }else if(kodeModul_R == "07" && kodeVariabel_R == 12){
    kelembabanOutData.kodeModul = kodeModul_R;
    kelembabanOutData.kodeVariabel = kodeVariabel_R;
    kelembabanOutData.data = data_R;
    kelembabanOutData.kodeAlarm = kodeAlarm_R;
    kelembabanOutData.berita = berita_R;  
  }else{
    Serial.println("Tidak ada modul");
  }
}
// =========================================================== AKHIR FUNGSI PARSING ==========================================================================