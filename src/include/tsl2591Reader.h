#ifndef Tsl2591Reader_h
#define Tsl2591Reader_h

#include <stdint.h>
#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_TSL2591.h"


/* TSL2591 Digital Light Sensor */
/* Dynamic Range: 600M:1 */
/* Maximum Lux: 88K */

// Example for demonstrating the TSL2591 library - public domain!

// connect SCL to analog 5
// connect SDA to analog 4
// connect Vin to 3.3-5V DC
// connect GROUND to common ground

class Tsl2591Reader{
public:
  Tsl2591Reader();
  void start();
  uint16_t simpleRead(void);
  void advancedRead(void);
  void unifiedSensorAPIRead(void);
private:
  Adafruit_TSL2591 tsl;
  void displaySensorDetails(void);
  void configureSensor(void);
};

#endif
