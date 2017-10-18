#include <Arduino.h>
#include "DigitalOut.h"
#include "EEPROMex.h"
#include "TickTock.h"
#include "Thermometer.h"
#include "Relay.h"
#include "UserPrefs.h"
#include "Communication.h"
#include "StartupReset.h"

// CONSTS
const uint32_t SERIAL_BPS = 115200;
const uint32_t INITIALIZE_DELAY = 2000;
const bool SERIAL_DEBUG_ENABLED = true;
const uint32_t SERIAL_DEBUG_INTERVAL = 2000;

const int PIN_THERMOMETER = A0;
const int PIN_CONTROL_LED = 13;
const int PIN_DEBUG_LED = A1;
const int PIN_CONTROL_OUTPUT = A2;
const int PIN_RESET = A5;

// DEVICES
DigitalOut controlLed(PIN_CONTROL_LED, LOW);
DigitalOut debugLed(PIN_DEBUG_LED, LOW);
DigitalOut controlOutput(PIN_CONTROL_OUTPUT, LOW);
Thermometer thermometer(PIN_THERMOMETER);
StartupReset startupReset(PIN_RESET);

// GLOBALS
bool initialized = false;
float setPoint = 25;
Relay relay;
TickTock debugTick;
ModbusSerial modbus;
UserPrefs userPrefs;
Communication comm;

void initCheck()
{
	delay(INITIALIZE_DELAY);

	// start other tasks only if temperature is ready
	if (thermometer.TemperatureReady())
	{
		debugTick.Tick();
		initialized = true;
	}
}

void control()
{
	// wait until new measurement is done
	if (!thermometer.TemperatureReady())
		return;

	float temperature = thermometer.ReadTemperature();
	uint32_t measureTime = thermometer.GetLastMeasureTime();

	// perform control loop and update outputs
	float error = setPoint - temperature;
	uint8_t controlValue = relay.GetOutput(error);
	controlOutput.Set(controlValue);
	controlLed.Toggle();

	// update modbus data with current results
	comm.SetOutputState(controlValue);
	comm.SetTemperature(temperature);
	comm.SetMeasureTime(measureTime);

	// request new temperature measure
	thermometer.RequestTemperature();
}

void sendDebug()
{
#ifdef __AVR_ATmega32U4__
	if (!SERIAL_DEBUG_ENABLED)
		return;

	if (debugTick.Tock() > SERIAL_DEBUG_INTERVAL)
	{
		Serial1.print("Relay:");
		Serial1.print(controlOutput.Get());
		Serial1.print(" Time:");
		Serial1.print(millis());
		Serial1.print(" Temp:");
		Serial1.print(thermometer.GetLastTemperature());
		Serial1.print(" MeasureTime:");
		Serial1.print(thermometer.GetLastMeasureTime());
		Serial1.print(" Resolution:");
		Serial1.print(thermometer.GetResolution());
		Serial1.print(" SetPoint:");
		Serial1.print(setPoint);
		Serial1.print(" InputOn:");
		Serial1.print(relay.GetInputOn());
		Serial1.print(" InputOff:");
		Serial1.print(relay.GetInputOff());
		Serial1.println();

		debugLed.Toggle();
		debugTick.Tick();
	}
#endif
}

void communication()
{
	comm.Update();

	// update time through modbus
	comm.SetTime(millis());

	// check all inputs from modbus
	if (comm.CheckNewSetpoint())
	{
		setPoint = comm.GetNewSetPoint();
		userPrefs.SetSetPoint(setPoint);
		comm.SetSetpoint(setPoint);
	}

	if (comm.CheckNewInputOn())
	{
		relay.SetInputOn(comm.GetNewInputOn());
		float inputOn = relay.GetInputOn();
		userPrefs.SetRelayInputOn(inputOn);
		comm.SetInputOn(inputOn);
	}

	if (comm.CheckNewInputOff())
	{
		relay.SetInputOff(comm.GetNewInputOff());
		float inputOff = relay.GetInputOff();
		userPrefs.SetRelayInputOff(inputOff);
		comm.SetInputOff(inputOff);
	}

	if (comm.CheckNewResolution())
	{
		thermometer.SetResolution(comm.GetNewResolution());
		Thermometer::Resolution resolution = thermometer.GetResolution();
		userPrefs.SetResolution(resolution);
		comm.SetResolution(resolution);
	}
}

void setup()
{
	// if reset than clear all settings to restore its default values
	if (startupReset.CheckReset())
		userPrefs.Clear();

	// load settings stored in EEPROM or its default values
	setPoint = userPrefs.GetSetPoint(30);
	float inputOn = userPrefs.GetRelayInputOn(2);
	float inputOff = userPrefs.GetRelayInputOff(-2);
	Thermometer::Resolution resolution = userPrefs.GetThermometerResolution(Thermometer::RESOLUTION0_0625);

	// setup serial communication
	comm.Setup(Serial, SERIAL_BPS);
#ifdef __AVR_ATmega32U4__
	Serial1.begin(SERIAL_BPS);
#endif

	// update modbus registers
	comm.SetSetpoint(setPoint);
	comm.SetInputOn(inputOn);
	comm.SetInputOff(inputOff);
	comm.SetResolution(resolution);

	// initialize thermometer and relay
	thermometer.Begin(resolution);
	thermometer.RequestTemperature();
	relay.Setup(HIGH, LOW, inputOn, inputOff);

	initCheck();
}

void loop()
{
	if (!initialized)
		return;

	control();
	communication();
	sendDebug();
}

