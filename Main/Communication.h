#pragma once

#include <Arduino.h>
#include "Modbus.h"
#include "ModbusSerial.h"

class Communication
{
public:
	Communication();

	void Setup(Serial_&, uint32_t);
	void Update();

	void SetOutputState(uint8_t);
	void SetTime(uint32_t);
	void SetTemperature(float);
	void SetMeasureTime(uint32_t);
	void SetSetpoint(float);
	void SetInputOn(float);
	void SetInputOff(float);
	void SetResolution(short);

	bool CheckNewSetpoint();
	bool CheckNewInputOn();
	bool CheckNewInputOff();
	bool CheckNewResolution();
	float GetNewSetPoint();
	float GetNewInputOn();
	float GetNewInputOff();
	word GetNewResolution();
private:
	void SetupSlaveInputStorage();
	void SetupSlaveOutputStorage();

	float GetFloat(word addresHi, word addressLo);
	bool CheckNewFlag(word flagAddress);

	ModbusSerial modbus;

	// MODBUS ADDRESSES
	const word ADDRESS_OUTPUT_STATE;

	const word ADDRESS_TIME_HI;
	const word ADDRESS_TIME_LO;
	const word ADDRESS_TEMPERATURE_HI;
	const word ADDRESS_TEMPERATURE_LO;
	const word ADDRESS_MEASURE_TIME_HI;
	const word ADDRESS_MEASURE_TIME_LO;
	const word ADDRESS_SETPOINT_HI;
	const word ADDRESS_SETPOINT_LO;
	const word ADDRESS_INPUTON_HI;
	const word ADDRESS_INPUTON_LO;
	const word ADDRESS_INPUTOFF_HI;
	const word ADDRESS_INPUTOFF_LO;
	const word ADDRESS_RESOLUTION;

	const word ADDRESS_NEW_SETPOINT;
	const word ADDRESS_NEW_INPUTON;
	const word ADDRESS_NEW_INPUTOFF;
	const word ADDRESS_NEW_RESOLUTION;

	const word ADDRESS_NEW_SETPOINT_VALUE_HI;
	const word ADDRESS_NEW_SETPOINT_VALUE_LO;
	const word ADDRESS_NEW_INPUTON_VALUE_HI;
	const word ADDRESS_NEW_INPUTON_VALUE_LO;
	const word ADDRESS_NEW_INPUTOFF_VALUE_HI;
	const word ADDRESS_NEW_INPUTOFF_VALUE_LO;
	const word ADDRESS_NEW_RESOLUTION_VALUE;
};
