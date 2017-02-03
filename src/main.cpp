#include <ESP8266WiFi.h>
#include "include/domoticz-client.h"
#include "include/tsl2591Reader.h"
#include "include/AM2302Reader.h"
#include "include/Piezo.h"
#include "include/onewire.h"
#include "include/dallastemperature.h"

DomoticzClient client("192.168.1.160",8080);

Tsl2591Reader tsl2591Reader;
AM2302Reader am2302Reader;

short seconds = 1;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting Adafruit TSL2591 Test!");
  // tsl2591Reader.start();
  // am2302Reader.start();

  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  //wifi credentials ssdid, wpa key
  WiFi.begin("", "");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void readLux(){
  uint16_t val = tsl2591Reader.simpleRead();
  if (isnan(val)) {
    Serial.println("Failed to read lux level");
  }
  if(val != 654){
    client.callDomoticz(client.buildLuxUrl(161,(short)val));
  }
}

void readtemp() {

  AM2302Reader::TempHumReading reading  = am2302Reader.read();
  if (isnan(reading.Temperature) || isnan(reading.Humidity)) {
    Serial.println("Failed to read from DHT");
  }
  else {
    Serial.print(reading.Humidity);
    Serial.print(" Temp:");
    Serial.println(reading.Temperature);
    if(reading.Temperature>0 && reading.Humidity> 0){
      client.callDomoticz(client.buildTempHumidityUrl(163,reading.Temperature,reading.Humidity));
    }
    delay(1000);
  }
}


void loop() {
    //piezo.march();
    // short seconds = 60;
    // readtemp();
    // delay(1000 );
    // readLux();
    delay(1000 * seconds );
}
