/*
  CleanPin.h - Library for cleaning noise from analog input
  Created by José María Campaña, October 4 2015
*/

#include "Arduino.h"
#include "CleanPin.h"

CleanPin::CleanPin(int pin, int avgFrom, int numAvg) {
  _pin = pin;
  _avgFrom = avgFrom;
  _numAvg = numAvg;
  _currentRead = 0;
  for (int i = 0; i < 10; i++)
    _reads[i] = analogRead(_pin);
}

void CleanPin::update() {
  _reads[_currentRead] = analogRead(_pin);
  _currentRead = (_currentRead == 9) ? 0 : _currentRead+1;
}

int CleanPin::getRead() {
  int sum = 0;
  for (int i = 0; i < _numAvg; i++)
    sum += _reads[(_avgFrom-1)+i];
  return (int)(sum/_numAvg);
}

int CleanPin::getVar() {
  int var = getRead();
  if (var > 1000) return 1;
  else if (var > 600 && var < 700) return 2;
  else if(var < 20) return 3;
  else return 0;
}
