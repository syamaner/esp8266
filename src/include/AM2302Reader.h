#ifndef AM2302Reader_h
#define AM2302Reader_h

#include <stdint.h>
#include <Arduino.h>
#include "DHT.h"


#define DHTPIN 2     // what pin we're connected to

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

class AM2302Reader{
public:
  struct TempHumReading {
       // members will be public without `private:` keyword
       float Temperature;
       float Humidity;
   };
//  AM2302Reader();
  void start();
  TempHumReading read();

private:

};

#endif
