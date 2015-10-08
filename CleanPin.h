/*
  CleanPin.h - Library for cleaning noise from analog input
  Created by José María Campaña, October 4 2015
*/

#ifndef CleanPin_h
#define CleanPin_h

#include "Arduino.h"

class CleanPin {
  public:
    CleanPin(int pin, int avgFrom, int numAvg);
    void update();
    int getRead();
    int getVar();
  private:
    int _pin;
    int _reads[10];
    int _avgFrom;
    int _numAvg;
    int _read;
    int _prevRead;
    int _tolerance;
    int _currentRead;
};

#endif
