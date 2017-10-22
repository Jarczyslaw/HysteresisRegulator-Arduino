# HysteresisRegulator-Arduino
## Intro
It's just a simple temperature regulator made with Arduino (I used Leonardo board but it should work also with Uno and others). It uses two-state controller with hysteresis to steer relay's output and popular DS18B20 sensor to measure temperature. 

This is a Visual Micro project which is far better than Arduino IDE.

There is also control panel made in WPF to read and write data from board: [HysteresisRegulator-WPF](https://github.com/Jarczyslaw/HysteresisRegulator-WPF)

## Features
A short list of project features:
* control loop with relay controller (with hysteresis)
* customizable parameters: set point, hysteresis width, thermometer resolution
* settings are stored in EEPROM
* uses Modbus protocol to set regulator parameters and to show current devices states
* Leonardo has 2 serials, main Serial is used by Modbus communication, the second one for debugging purposes
* additional input for device's settings reset

## Schematic
![Schematic](http://jtjt.pl/www/pages/regulator-temperatury-arduino/scheme_bb.png)
As you can see, there is only a few elements:
* LED on port 13 which indicates iiterations of control loop
* debug LED which toggles when debug data is sent through serial port (2s interval)
* control LED which indicates current output state. There should be relay circuit to control heater
* DS18B20 thermometer

## Libraries used
Libraries that was used in this projects:
* [EEPROMex](https://playground.arduino.cc/Code/EEPROMex)
* [Modbus Library for Arduino](https://github.com/andresarmento/modbus-arduino)
* [DS18B20 (digital temperature sensor) and Arduino](https://create.arduino.cc/projecthub/TheGadgetBoy/ds18b20-digital-temperature-sensor-and-arduino-9cc806)
