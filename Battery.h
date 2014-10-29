#ifndef BATTERY_H
#define BATTERY_H

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
 #include <pins_arduino.h>
#endif

// Code to work out the supply voltage to your Arduino (Vcc)
// Taken from http://provideyourown.com/2012/secret-arduino-voltmeter-measure-battery-voltage/

long readVcc();

#endif
