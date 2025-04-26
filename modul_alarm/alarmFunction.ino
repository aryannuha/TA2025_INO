// ======================================= FUNGSI alarm() UNTUK MENENTUKAN OUTPUT SESUAI KEADAAN ALARM ========================================================
void alarm(){
  // kondisi berdasarkan kode alarm suhu
  switch(suhuData.kodeAlarm){
    case 0:
      Serial.print(suhuData.berita);
      Serial.print(" ");
      Serial.print(suhuData.data);
      Serial.println(" °C");
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
}
// =================================================== AKHIR FUNGSI alarm() ==================================================================================