#ifndef DomoticzClient_h
#define DomoticzClient_h

#include <stdint.h>
#include <Arduino.h>

class DomoticzClient{
public:
  void callDomoticz(String url);
  String buildTempHumidityUrl(short sensorIdx, float temp, float humidity);
  String buildLuxUrl(short sensorIdx, short lux);
  DomoticzClient(const char* _host, const int _httpPort);
private:
  const char* host;
  int httpPort;

};

#endif
