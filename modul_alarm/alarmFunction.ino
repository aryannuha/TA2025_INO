// ======================================= FUNGSI alarm() UNTUK MENENTUKAN OUTPUT SESUAI KEADAAN ALARM ========================================================
void alarm(){
  // kondisi berdasarkan kode alarm suhu
  switch(suhuData.kodeAlarm){
    case 0:
      Serial.print(suhuData.berita);
      Serial.print(" ");
      Serial.print(suhuData.data);
      Serial.println(" °C");

      normal();
      break;
    case 1:
      Serial.print(suhuData.berita);
      Serial.print(" ");
      Serial.print(suhuData.data);
      Serial.println(" °C");

      // fungsi bunyi buzzer danger
      danger();
      break;
    case 2:
      Serial.print(suhuData.berita);
      Serial.print(" ");
      Serial.print(suhuData.data);
      Serial.println(" °C");

      // fungsi bunyi buzzer warning
      warning();
      break;
    case 3:
      Serial.print(suhuData.berita);
      Serial.print(" ");
      Serial.print(suhuData.data);
      Serial.println(" °C");

      // fungsi bunyi buzzer warning
      warning();
      break;
    case 4:
      Serial.print(suhuData.berita);
      Serial.print(" ");
      Serial.print(suhuData.data);
      Serial.println(" °C");

      // fungsi bunyi buzzer danger
      danger();
      break;
  }

  // kondisi berdasarkan kode alarm kelembaban
  switch(kelembabanData.kodeAlarm){
    case 0:
      Serial.print(kelembabanData.berita);
      Serial.print(" ");
      Serial.print(kelembabanData.data);
      Serial.println(" %");

      normal();
      break;
    case 1:
      Serial.print(kelembabanData.berita);
      Serial.print(" ");
      Serial.print(kelembabanData.data);
      Serial.println(" %");

      // fungsi bunyi buzzer danger
      danger();
      break;
    case 2:
      Serial.print(kelembabanData.berita);
      Serial.print(" ");
      Serial.print(kelembabanData.data);
      Serial.println(" %");

      // fungsi bunyi buzzer warning
      warning();
      break;
    case 3:
      Serial.print(kelembabanData.berita);
      Serial.print(" ");
      Serial.print(kelembabanData.data);
      Serial.println(" %");

      // fungsi bunyi buzzer warning
      warning();
      break;
    case 4:
      Serial.print(kelembabanData.berita);
      Serial.print(" ");
      Serial.print(kelembabanData.data);
      Serial.println(" %");

      // fungsi bunyi buzzer danger
      danger();
      break;
  }

    // kondisi berdasarkan kode alarm co2
  switch(co2Data.kodeAlarm){
    case 0:
      Serial.print(co2Data.berita);
      Serial.print(" ");
      Serial.print(co2Data.data);
      Serial.println(" PPM");

      normal();
      break;
    case 1:
      Serial.print(co2Data.berita);
      Serial.print(" ");
      Serial.print(co2Data.data);
      Serial.println(" PPM");

      // fungsi bunyi buzzer danger
      danger();
      break;
    case 2:
      Serial.print(co2Data.berita);
      Serial.print(" ");
      Serial.print(co2Data.data);
      Serial.println(" PPM");

      // fungsi bunyi buzzer warning
      warning();
      break;
    case 3:
      Serial.print(co2Data.berita);
      Serial.print(" ");
      Serial.print(co2Data.data);
      Serial.println(" PPM");

      // fungsi bunyi buzzer warning
      warning();
      break;
    case 4:
      Serial.print(co2Data.berita);
      Serial.print(" ");
      Serial.print(co2Data.data);
      Serial.println(" PPM");

      // fungsi bunyi buzzer danger
      danger();
      break;
  }

    // kondisi berdasarkan kode alarm windspeed
  switch(windspeedData.kodeAlarm){
    case 0:
      Serial.print(windspeedData.berita);
      Serial.print(" ");
      Serial.print(windspeedData.data);
      Serial.println(" m/s");

      normal();
      break;
    case 1:
      Serial.print(windspeedData.berita);
      Serial.print(" ");
      Serial.print(windspeedData.data);
      Serial.println(" m/s");

      // fungsi bunyi buzzer danger
      danger();
      break;
    case 2:
      Serial.print(windspeedData.berita);
      Serial.print(" ");
      Serial.print(windspeedData.data);
      Serial.println(" m/s");

      // fungsi bunyi buzzer warning
      warning();
      break;
    case 3:
      Serial.print(windspeedData.berita);
      Serial.print(" ");
      Serial.print(windspeedData.data);
      Serial.println(" m/s");

      // fungsi bunyi buzzer warning
      warning();
      break;
    case 4:
      Serial.print(windspeedData.berita);
      Serial.print(" ");
      Serial.print(windspeedData.data);
      Serial.println(" m/s");

      // fungsi bunyi buzzer danger
      danger();
      break;
  }

    // kondisi berdasarkan kode alarm rainfall
  switch(rainfallData.kodeAlarm){
    case 0:
      Serial.print(rainfallData.berita);
      Serial.print(" ");
      Serial.print(rainfallData.data);
      Serial.println(" mm");

      normal();
      break;
    case 1:
      Serial.print(rainfallData.berita);
      Serial.print(" ");
      Serial.print(rainfallData.data);
      Serial.println(" mm");

      // fungsi bunyi buzzer danger
      danger();
      break;
    case 2:
      Serial.print(rainfallData.berita);
      Serial.print(" ");
      Serial.print(rainfallData.data);
      Serial.println(" mm");

      // fungsi bunyi buzzer warning
      warning();
      break;
    case 3:
      Serial.print(rainfallData.berita);
      Serial.print(" ");
      Serial.print(rainfallData.data);
      Serial.println(" mm");

      // fungsi bunyi buzzer warning
      warning();
      break;
    case 4:
      Serial.print(rainfallData.berita);
      Serial.print(" ");
      Serial.print(rainfallData.data);
      Serial.println(" mm");

      // fungsi bunyi buzzer danger
      danger();
      break;
  }

    // kondisi berdasarkan kode alarm par
  switch(parData.kodeAlarm){
    case 0:
      Serial.print(parData.berita);
      Serial.print(" ");
      Serial.print(parData.data);
      Serial.println(" µmol/m²/s");

      normal();
      break;
    case 1:
      Serial.print(parData.berita);
      Serial.print(" ");
      Serial.print(parData.data);
      Serial.println(" µmol/m²/s");

      // fungsi bunyi buzzer danger
      danger();
      break;
    case 2:
      Serial.print(parData.berita);
      Serial.print(" ");
      Serial.print(parData.data);
      Serial.println(" µmol/m²/s");

      // fungsi bunyi buzzer warning
      warning();
      break;
    case 3:
      Serial.print(parData.berita);
      Serial.print(" ");
      Serial.print(parData.data);
      Serial.println(" µmol/m²/s");

      // fungsi bunyi buzzer warning
      warning();
      break;
    case 4:
      Serial.print(parData.berita);
      Serial.print(" ");
      Serial.print(parData.data);
      Serial.println(" µmol/m²/s");

      // fungsi bunyi buzzer danger
      danger();
      break;
  }

  // kondisi berdasarkan kode alarm suhu OUTDOOR
  switch(suhuOutData.kodeAlarm){
    case 0:
      Serial.print(suhuOutData.berita);
      Serial.print(" ");
      Serial.print(suhuOutData.data);
      Serial.println(" °C");

      normal();
      break;
    case 1:
      Serial.print(suhuOutData.berita);
      Serial.print(" ");
      Serial.print(suhuOutData.data);
      Serial.println(" °C");

      // fungsi bunyi buzzer danger
      danger();
      break;
    case 2:
      Serial.print(suhuOutData.berita);
      Serial.print(" ");
      Serial.print(suhuOutData.data);
      Serial.println(" °C");

      // fungsi bunyi buzzer warning
      warning();
      break;
    case 3:
      Serial.print(suhuOutData.berita);
      Serial.print(" ");
      Serial.print(suhuOutData.data);
      Serial.println(" °C");

      // fungsi bunyi buzzer warning
      warning();
      break;
    case 4:
      Serial.print(suhuOutData.berita);
      Serial.print(" ");
      Serial.print(suhuOutData.data);
      Serial.println(" °C");

      // fungsi bunyi buzzer danger
      danger();
      break;
  }

  // kondisi berdasarkan kode alarm kelembaban OUTDOOR
  switch(kelembabanOutData.kodeAlarm){
    case 0:
      Serial.print(kelembabanOutData.berita);
      Serial.print(" ");
      Serial.print(kelembabanOutData.data);
      Serial.println(" %");

      normal();
      break;
    case 1:
      Serial.print(kelembabanOutData.berita);
      Serial.print(" ");
      Serial.print(kelembabanOutData.data);
      Serial.println(" %");

      // fungsi bunyi buzzer danger
      danger();
      break;
    case 2:
      Serial.print(kelembabanOutData.berita);
      Serial.print(" ");
      Serial.print(kelembabanOutData.data);
      Serial.println(" %");

      // fungsi bunyi buzzer warning
      warning();
      break;
    case 3:
      Serial.print(kelembabanOutData.berita);
      Serial.print(" ");
      Serial.print(kelembabanOutData.data);
      Serial.println(" %");

      // fungsi bunyi buzzer warning
      warning();
      break;
    case 4:
      Serial.print(kelembabanOutData.berita);
      Serial.print(" ");
      Serial.print(kelembabanOutData.data);
      Serial.println(" %");

      // fungsi bunyi buzzer danger
      danger();
      break;
  }

  // kondisi berdasarkan kode alarm tegangan ac
  switch(teganganacData.kodeAlarm){
    case 0:
      Serial.print(teganganacData.berita);
      Serial.print(" ");
      Serial.print(teganganacData.data);
      Serial.println(" V");

      normal();
      break;
    case 1:
      Serial.print(teganganacData.berita);
      Serial.print(" ");
      Serial.print(teganganacData.data);
      Serial.println(" V");

      // fungsi bunyi buzzer danger
      danger();
      break;
    case 2:
      Serial.print(teganganacData.berita);
      Serial.print(" ");
      Serial.print(teganganacData.data);
      Serial.println(" V");

      // fungsi bunyi buzzer warning
      warning();
      break;
    case 3:
      Serial.print(teganganacData.berita);
      Serial.print(" ");
      Serial.print(teganganacData.data);
      Serial.println(" V");

      // fungsi bunyi buzzer warning
      warning();
      break;
    case 4:
      Serial.print(teganganacData.berita);
      Serial.print(" ");
      Serial.print(teganganacData.data);
      Serial.println(" V");

      // fungsi bunyi buzzer danger
      danger();
      break;
  }

    // kondisi berdasarkan kode alarm arus ac
  switch(arusacData.kodeAlarm){
    case 0:
      Serial.print(arusacData.berita);
      Serial.print(" ");
      Serial.print(arusacData.data);
      Serial.println(" A");

      normal();
      break;
    case 1:
      Serial.print(arusacData.berita);
      Serial.print(" ");
      Serial.print(arusacData.data);
      Serial.println(" A");

      // fungsi bunyi buzzer danger
      danger();
      break;
    case 2:
      Serial.print(arusacData.berita);
      Serial.print(" ");
      Serial.print(arusacData.data);
      Serial.println(" A");

      // fungsi bunyi buzzer warning
      warning();
      break;
    case 3:
      Serial.print(arusacData.berita);
      Serial.print(" ");
      Serial.print(arusacData.data);
      Serial.println(" A");

      // fungsi bunyi buzzer warning
      warning();
      break;
    case 4:
      Serial.print(arusacData.berita);
      Serial.print(" ");
      Serial.print(arusacData.data);
      Serial.println(" A");

      // fungsi bunyi buzzer danger
      danger();
      break;
  }

  // kondisi berdasarkan kode alarm daya ac
  switch(dayaacData.kodeAlarm){
    case 0:
      Serial.print(dayaacData.berita);
      Serial.print(" ");
      Serial.print(dayaacData.data);
      Serial.println(" W");

      normal();
      break;
    case 1:
      Serial.print(dayaacData.berita);
      Serial.print(" ");
      Serial.print(dayaacData.data);
      Serial.println(" W");

      // fungsi bunyi buzzer danger
      danger();
      break;
    case 2:
      Serial.print(dayaacData.berita);
      Serial.print(" ");
      Serial.print(dayaacData.data);
      Serial.println(" W");

      // fungsi bunyi buzzer warning
      warning();
      break;
    case 3:
      Serial.print(dayaacData.berita);
      Serial.print(" ");
      Serial.print(dayaacData.data);
      Serial.println(" W");

      // fungsi bunyi buzzer warning
      warning();
      break;
    case 4:
      Serial.print(dayaacData.berita);
      Serial.print(" ");
      Serial.print(dayaacData.data);
      Serial.println(" W");

      // fungsi bunyi buzzer danger
      danger();
      break;
  }

    // kondisi berdasarkan kode alarm tegangan dc
  switch(tegangandcData.kodeAlarm){
    case 0:
      Serial.print(tegangandcData.berita);
      Serial.print(" ");
      Serial.print(tegangandcData.data);
      Serial.println(" V");

      normal();
      break;
    case 1:
      Serial.print(tegangandcData.berita);
      Serial.print(" ");
      Serial.print(tegangandcData.data);
      Serial.println(" V");

      // fungsi bunyi buzzer danger
      danger();
      break;
    case 2:
      Serial.print(tegangandcData.berita);
      Serial.print(" ");
      Serial.print(tegangandcData.data);
      Serial.println(" V");

      // fungsi bunyi buzzer warning
      warning();
      break;
    case 3:
      Serial.print(tegangandcData.berita);
      Serial.print(" ");
      Serial.print(tegangandcData.data);
      Serial.println(" V");

      // fungsi bunyi buzzer warning
      warning();
      break;
    case 4:
      Serial.print(tegangandcData.berita);
      Serial.print(" ");
      Serial.print(tegangandcData.data);
      Serial.println(" V");

      // fungsi bunyi buzzer danger
      danger();
      break;
  }

    // kondisi berdasarkan kode alarm arus dc
  switch(arusdcData.kodeAlarm){
    case 0:
      Serial.print(arusdcData.berita);
      Serial.print(" ");
      Serial.print(arusdcData.data);
      Serial.println(" mA");

      normal();
      break;
    case 1:
      Serial.print(arusdcData.berita);
      Serial.print(" ");
      Serial.print(arusdcData.data);
      Serial.println(" mA");

      // fungsi bunyi buzzer danger
      danger();
      break;
    case 2:
      Serial.print(arusdcData.berita);
      Serial.print(" ");
      Serial.print(arusdcData.data);
      Serial.println(" mA");

      // fungsi bunyi buzzer warning
      warning();
      break;
    case 3:
      Serial.print(arusdcData.berita);
      Serial.print(" ");
      Serial.print(arusdcData.data);
      Serial.println(" mA");

      // fungsi bunyi buzzer warning
      warning();
      break;
    case 4:
      Serial.print(arusdcData.berita);
      Serial.print(" ");
      Serial.print(arusdcData.data);
      Serial.println(" mA");

      // fungsi bunyi buzzer danger
      danger();
      break;
  }

  // kondisi berdasarkan kode alarm daya dc
  switch(dayadcData.kodeAlarm){
    case 0:
      Serial.print(dayadcData.berita);
      Serial.print(" ");
      Serial.print(dayadcData.data);
      Serial.println(" mW");

      normal();
      break;
    case 1:
      Serial.print(dayadcData.berita);
      Serial.print(" ");
      Serial.print(dayadcData.data);
      Serial.println(" mW");

      // fungsi bunyi buzzer danger
      danger();
      break;
    case 2:
      Serial.print(dayadcData.berita);
      Serial.print(" ");
      Serial.print(dayadcData.data);
      Serial.println(" mW");

      // fungsi bunyi buzzer warning
      warning();
      break;
    case 3:
      Serial.print(dayadcData.berita);
      Serial.print(" ");
      Serial.print(dayadcData.data);
      Serial.println(" mW");

      // fungsi bunyi buzzer warning
      warning();
      break;
    case 4:
      Serial.print(dayadcData.berita);
      Serial.print(" ");
      Serial.print(dayadcData.data);
      Serial.println(" mW");

      // fungsi bunyi buzzer danger
      danger();
      break;
  }
}
// =================================================== AKHIR FUNGSI alarm() ==================================================================================