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

  // PUBLISH TEGANGAN DC
  client.publish("mcs/kodeModulTeganganDc", kodeModulTeganganDc_str, true);
  client.publish("mcs/kodeVariabelTeganganDc", kodeVariabelTeganganDc_str, true);
  client.publish("mcs/kodeDataTeganganDc", kodeDataTeganganDc_str, true);
  client.publish("mcs/kodeAlarmTeganganDc", kodeAlarmTeganganDc_str, true);
  client.publish("mcs/beritaTeganganDc", beritaTeganganDc_str, true);

  // PUBLISH ARUS DC
  client.publish("mcs/kodeModulArusDc", kodeModulArusDc_str, true);
  client.publish("mcs/kodeVariabelArusDc", kodeVariabelArusDc_str, true);
  client.publish("mcs/kodeDataArusDc", kodeDataArusDc_str, true);
  client.publish("mcs/kodeAlarmArusDc", kodeAlarmArusDc_str, true);
  client.publish("mcs/beritaArusDc", beritaArusDc_str, true);

  // PUBLISH DAYA DC
  client.publish("mcs/kodeModulDayaDc", kodeModulDayaDc_str, true);
  client.publish("mcs/kodeVariabelDayaDc", kodeVariabelDayaDc_str, true);
  client.publish("mcs/kodeDataDayaDc", kodeDataDayaDc_str, true);
  client.publish("mcs/kodeAlarmDayaDc", kodeAlarmDayaDc_str, true);
  client.publish("mcs/beritaDayaDc", beritaDayaDc_str, true);

  // PUBLISH TEGANGAN AC
  client.publish("mcs/kodeModulTeganganAc", kodeModulTeganganAc_str, true);
  client.publish("mcs/kodeVariabelTeganganAc", kodeVariabelTeganganAc_str, true);
  client.publish("mcs/kodeDataTeganganAc", kodeDataTeganganAc_str, true);
  client.publish("mcs/kodeAlarmTeganganAc", kodeAlarmTeganganAc_str, true);
  client.publish("mcs/beritaTeganganAc", beritaTeganganAc_str, true);

  // PUBLISH ARUS AC
  client.publish("mcs/kodeModulArusAc", kodeModulArusAc_str, true);
  client.publish("mcs/kodeVariabelArusAc", kodeVariabelArusAc_str, true);
  client.publish("mcs/kodeDataArusAc", kodeDataArusAc_str, true);
  client.publish("mcs/kodeAlarmArusAc", kodeAlarmArusAc_str, true);
  client.publish("mcs/beritaArusAc", beritaArusAc_str, true);

  // PUBLISH DAYA AC
  client.publish("mcs/kodeModulDayaAc", kodeModulDayaAc_str, true);
  client.publish("mcs/kodeVariabelDayaAc", kodeVariabelDayaAc_str, true);
  client.publish("mcs/kodeDataDayaAc", kodeDataDayaAc_str, true);
  client.publish("mcs/kodeAlarmDayaAc", kodeAlarmDayaAc_str, true);
  client.publish("mcs/beritaDayaAc", beritaDayaAc_str, true);
}
// =============================================== AKHRI FUNGSI sendData() ====================================================================================