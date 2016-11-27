#ifndef Piezo_h
#define Piezo_h

#include <stdint.h>
#include <Arduino.h>

#define c 261
#define d 294
#define e 329
#define f 349
#define g 391
#define gS 415
#define a 440
#define aS 455
#define b 466
#define cH 523
#define cSH 554
#define dH 587
#define dSH 622
#define eH 659
#define fH 698
#define fSH 740
#define gH 784
#define gSH 830
#define aH 880

//frequencies for the tones we're going to use
//used http://home.mit.bme.hu/~bako/tonecalc/tonecalc.htm to get these
class Piezo{
public:
  void march();
  void setup();
  Piezo(int _speakerPin);
private:
  int speakerPin;// = 15;
  void beep (unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds);

};

#endif
