void proses(){
  saveDataToSD();
}

void saveDataToSD() {
  DateTime now = rtc.now();
  char waktuStr[20];
  sprintf(waktuStr, "%04d-%02d-%02d %02d:%02d:%02d",
          now.year(), now.month(), now.day(),
          now.hour(), now.minute(), now.second());

  File file = SD.open(filename, FILE_APPEND);
  if (file) {
    file.print(waktuStr);
    file.print(",");
    file.print(suhuData.data);
    file.print(",");
    file.print(kelembabanData.data);
    file.print(",");
    file.print(suhuOutData.data);
    file.print(",");
    file.print(kelembabanOutData.data);
    file.print(",");
    file.print(co2Data.data);
    file.print(",");
    file.print(windspeedData.data);
    file.print(",");
    file.print(rainfallData.data);
    file.print(",");
    file.print(tegangandcData.data);
    file.print(",");
    file.print(arusdcData.data);
    file.print(",");
    file.print(dayadcData.data);
    file.print(",");
    file.print(teganganacData.data);
    file.print(",");
    file.print(arusacData.data);
    file.print(",");
    file.println(dayaacData.data);
    file.close();
    Serial.println("Data tersimpan ke SD Card.");
  } else {
    Serial.println("Gagal membuka file untuk menulis.");
  }
}

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
  }else if(kodeModul_R == "08" && kodeVariabel_R == 11){
    tegangandcData.kodeModul = kodeModul_R;
    tegangandcData.kodeVariabel = kodeVariabel_R;
    tegangandcData.data = data_R;
    tegangandcData.kodeAlarm = kodeAlarm_R;
    tegangandcData.berita = berita_R;  
  }else if(kodeModul_R == "08" && kodeVariabel_R == 12){
    arusdcData.kodeModul = kodeModul_R;
    arusdcData.kodeVariabel = kodeVariabel_R;
    arusdcData.data = data_R;
    arusdcData.kodeAlarm = kodeAlarm_R;
    arusdcData.berita = berita_R;  
  }else if(kodeModul_R == "08" && kodeVariabel_R == 13){
    dayadcData.kodeModul = kodeModul_R;
    dayadcData.kodeVariabel = kodeVariabel_R;
    dayadcData.data = data_R;
    dayadcData.kodeAlarm = kodeAlarm_R;
    dayadcData.berita = berita_R;  
  }else if(kodeModul_R == "09" && kodeVariabel_R == 11){
    teganganacData.kodeModul = kodeModul_R;
    teganganacData.kodeVariabel = kodeVariabel_R;
    teganganacData.data = data_R;
    teganganacData.kodeAlarm = kodeAlarm_R;
    teganganacData.berita = berita_R;  
  }else if(kodeModul_R == "09" && kodeVariabel_R == 12){
    arusacData.kodeModul = kodeModul_R;
    arusacData.kodeVariabel = kodeVariabel_R;
    arusacData.data = data_R;
    arusacData.kodeAlarm = kodeAlarm_R;
    arusacData.berita = berita_R;  
  }else if(kodeModul_R == "09" && kodeVariabel_R == 13){
    dayaacData.kodeModul = kodeModul_R;
    dayaacData.kodeVariabel = kodeVariabel_R;
    dayaacData.data = data_R;
    dayaacData.kodeAlarm = kodeAlarm_R;
    dayaacData.berita = berita_R;  
  }else{
    Serial.println("Tidak ada modul");
  }
}
// =========================================================== AKHIR FUNGSI PARSING ==========================================================================