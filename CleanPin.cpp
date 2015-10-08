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
  for (int i = 0; i < 10; i++)
    _reads[i] = analogRead(_pin);

  _prevRead = _read;
  int sum = 0;
  for (int i = 0; i < _numAvg; i++)
    sum += _reads[(_avgFrom-1)+i];
  _read = (int)(sum/_numAvg);
}

int CleanPin::getRead() {
  return _read;
}

int CleanPin::getVar() {

  int diff = _read - _prevRead;
  diff *= (diff < 0) ? -1 : 1;

  if (diff > 1) return 0;
  else if (_read > 1020) return 1;
  else if (_read >= 510 && _read <= 511) return 2;
  else if(_read < 5) return 3;
  else return 0;
}
