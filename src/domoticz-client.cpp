#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "include/domoticz-client.h"
#include "Arduino.h"

DomoticzClient::DomoticzClient(const char* _host, const int _httpPort){
 host= _host;
 httpPort=_httpPort;
}

void DomoticzClient::callDomoticz(String url){
  WiFiClient client;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  Serial.print("Requesting URL: ");
  Serial.println(url);
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
    "Host: " + host + "\r\n" +
    "Connection: close\r\n\r\n");
    while (client.available()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
    Serial.println();
    Serial.println("closing connection");
}

String DomoticzClient::buildTempHumidityUrl(short sensorIdx, float temp, float humidity){
  short stat = 0;
  if(humidity<45)
    stat=2;//dry
  else if(humidity<55)
    stat = 1;
  else if(humidity < 65)
    stat = 0;
  else
    stat=3;
  String  url = "/json.htm?type=command&param=udevice&idx="+String(sensorIdx)+"&nvalue=0&svalue=" + String(temp) + ";"+ String(humidity) + ";" + String(stat);
  return url;
}

String DomoticzClient::buildLuxUrl(short sensorIdx, short lux){
  String url = "/json.htm?type=command&param=udevice&idx="+String(sensorIdx)+"&svalue=" + String(lux);
  return url;
}
