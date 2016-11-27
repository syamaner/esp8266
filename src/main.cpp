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
int speakerPin = 15;
Piezo piezo(speakerPin);
short seconds = 1;
int numberOfSensors;
// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);


// Based on http://www.hacktronics.com/Tutorials/arduino-1-wire-address-finder.html
int discoverOneWireDevices(void) {
  byte i;
  byte present = 0;
  byte data[12];
  byte addr[8];
  int count = 0;

  Serial.println("Looking for 1-Wire devices...");
  while(oneWire.search(addr)) {
    Serial.print("Found \'1-Wire\' device with address: ");
    for( i = 0; i < 8; i++) {
      Serial.print("0x");
      if (addr[i] < 16) {
        Serial.print('0');
      }
      Serial.print(addr[i], HEX);
      if (i < 7) {
        Serial.print(", ");
      }
    }
    if ( OneWire::crc8( addr, 7) != addr[7]) {
        Serial.println("CRC is not valid!");
        return 0;
    }
    Serial.println();
    count++;
  }
  Serial.println("That's it.");
  oneWire.reset_search();
  return count;
}
void setup() {
  Serial.begin(115200);
  Serial.println("Starting Adafruit TSL2591 Test!");

  // tsl2591Reader.start();
  // am2302Reader.start();
  //piezo.setup();


  // Start up the library
  sensors.begin();
  numberOfSensors = discoverOneWireDevices();
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
  // put your main code here, to run repeatedly:
  //displaySensorDetails();
  uint16_t val = tsl2591Reader.simpleRead();

//  tsl2591Reader.advancedRead();

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
    // call sensors.requestTemperatures() to issue a global temperature
      // request to all devices on the bus
      Serial.print("Requesting temperatures...");
      sensors.requestTemperatures(); // Send the command to get temperatures
      Serial.println("DONE");

        // Read each of our sensors and print the value
        for(int i=0; i < numberOfSensors; i++) {
         Serial.print("Temperature for Device ");
         Serial.print( i );
         Serial.print(" is: ");
         // Why "byIndex"? You can have more than one IC on the same bus.
         // 0 refers to the first IC on the wire
         Serial.println( sensors.getTempCByIndex(i) );
        }

      // Serial.print("Temperature for the device 1 (index 0) is: ");
      // Serial.println(sensors.getTempCByIndex(0));

    delay(1000 * seconds );

}
