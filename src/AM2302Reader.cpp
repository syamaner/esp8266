
#include "include/AM2302Reader.h"

DHT dht(DHTPIN, DHTTYPE);
void AM2302Reader::start(){
  dht.begin();
}

  AM2302Reader::TempHumReading AM2302Reader::read(){
     TempHumReading reading=  TempHumReading();

        reading.Humidity = dht.readHumidity();
        reading.Temperature = dht.readTemperature();

        return reading;
  }
