// ================================ FUNGSI proses() UNTUK KONVERSI MENJADI STRING SEBELUM KIRIM KE MQTT =====================================================
void proses(){
  // PANGGIL FUNGSI parsing()
  parsing();
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