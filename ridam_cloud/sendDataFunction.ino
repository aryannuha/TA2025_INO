// ================================================ FUNGSI sendData() KE MQTT ================================================================================
void sendData(){
  // PUBLISH SUHU INDOOR
  client.publish("mcs/kodeModulSuhuIn", kodeModulSuhuIn_str, true);
  client.publish("mcs/kodeVariabelSuhuIn", kodeVariabelSuhuIn_str, true);
  client.publish("mcs/kodeDataSuhuIn", kodeDataSuhuIn_str, true);
  client.publish("mcs/kodeAlarmSuhuIn", kodeAlarmSuhuIn_str, true);
  client.publish("mcs/beritaSuhuIn", beritaSuhuIn_str, true);

  // PUBLISH KELEMBABAN INDOOR
  client.publish("mcs/kodeModulKelembabanIn", kodeModulKelembabanIn_str, true);
  client.publish("mcs/kodeVariabelKelembabanIn", kodeVariabelKelembabanIn_str, true);
  client.publish("mcs/kodeDataKelembabanIn", kodeDataKelembabanIn_str, true);
  client.publish("mcs/kodeAlarmKelembabanIn", kodeAlarmKelembabanIn_str, true);
  client.publish("mcs/beritaKelembabanIn", beritaKelembabanIn_str, true);

  // PUBLISH SUHU OUTDOOR
  client.publish("mcs/kodeModulSuhuOut", kodeModulSuhuOut_str, true);
  client.publish("mcs/kodeVariabelSuhuOut", kodeVariabelSuhuOut_str, true);
  client.publish("mcs/kodeDataSuhuOut", kodeDataSuhuOut_str, true);
  client.publish("mcs/kodeAlarmSuhuOut", kodeAlarmSuhuOut_str, true);
  client.publish("mcs/beritaSuhuOut", beritaSuhuOut_str, true);

  // PUBLISH KELEMBABAN OUTDOOR
  client.publish("mcs/kodeModulKelembabanOut", kodeModulKelembabanOut_str, true);
  client.publish("mcs/kodeVariabelKelembabanOut", kodeVariabelKelembabanOut_str, true);
  client.publish("mcs/kodeDataKelembabanOut", kodeDataKelembabanOut_str, true);
  client.publish("mcs/kodeAlarmKelembabanOut", kodeAlarmKelembabanOut_str, true);
  client.publish("mcs/beritaKelembabanOut", beritaKelembabanOut_str, true);

  // PUBLISH CO2
  client.publish("mcs/kodeModulCo2", kodeModulCo2_str, true);
  client.publish("mcs/kodeVariabelCo2", kodeVariabelCo2_str, true);
  client.publish("mcs/kodeDataCo2", kodeDataCo2_str, true);
  client.publish("mcs/kodeAlarmCo2", kodeAlarmCo2_str, true);
  client.publish("mcs/beritaCo2", beritaKelembabanOut_str, true);

  // PUBLISH KECEPATAN ANGIN
  client.publish("mcs/kodeModulWindspeed", kodeModulWindspeed_str, true);
  client.publish("mcs/kodeVariabelWindspeed", kodeVariabelWindspeed_str, true);
  client.publish("mcs/kodeDataWindspeed", kodeDataWindspeed_str, true);
  client.publish("mcs/kodeAlarmWindspeed", kodeAlarmWindspeed_str, true);
  client.publish("mcs/beritaWindspeed", beritaWindspeed_str, true);

  // PUBLISH CURAH HUJAN
  client.publish("mcs/kodeModulRainfall", kodeModulRainfall_str, true);
  client.publish("mcs/kodeVariabelRainfall", kodeVariabelRainfall_str, true);
  client.publish("mcs/kodeDataRainfall", kodeDataRainfall_str, true);
  client.publish("mcs/kodeAlarmRainfall", kodeAlarmRainfall_str, true);
  client.publish("mcs/beritaRainfall", beritaRainfall_str, true);

  // PUBLISH PAR
  client.publish("mcs/kodeModulPar", kodeModulPar_str, true);
  client.publish("mcs/kodeVariabelPar", kodeVariabelPar_str, true);
  client.publish("mcs/kodeDataPar", kodeDataPar_str, true);
  client.publish("mcs/kodeAlarmPar", kodeAlarmPar_str, true);
  client.publish("mcs/beritaPar", beritaPar_str, true);
}
// =============================================== AKHRI FUNGSI sendData() ====================================================================================