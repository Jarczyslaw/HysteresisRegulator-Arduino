#include "Communication.h"

const int DEVICE_ADDRESS = 1;
const word INPUT_OFFSET = 0;

union floatToWords
{
	float f;
	word w[2];
} floatToWords;

Communication::Communication() :
	// master INPUTS
	// slave OUTPUTS
	// input contacts
	ADDRESS_OUTPUT_STATE(0),
	// input registers
	ADDRESS_TIME_HI(0),
	ADDRESS_TIME_LO(1),
	ADDRESS_TEMPERATURE_HI(2),
	ADDRESS_TEMPERATURE_LO(3),
	ADDRESS_MEASURE_TIME_HI(4),
	ADDRESS_MEASURE_TIME_LO(5),
	ADDRESS_SETPOINT_HI(6),
	ADDRESS_SETPOINT_LO(7),
	ADDRESS_INPUTON_HI(8),
	ADDRESS_INPUTON_LO(9),
	ADDRESS_INPUTOFF_HI(10),
	ADDRESS_INPUTOFF_LO(11),
	ADDRESS_RESOLUTION(12),

	// master OUTPUTS
	// slave INPUTS
	// coils
	ADDRESS_NEW_SETPOINT(INPUT_OFFSET + 0),
	ADDRESS_NEW_INPUTON(INPUT_OFFSET + 1),
	ADDRESS_NEW_INPUTOFF(INPUT_OFFSET + 2),
	ADDRESS_NEW_RESOLUTION(INPUT_OFFSET + 3),
	// holding registers
	ADDRESS_NEW_SETPOINT_VALUE_HI(INPUT_OFFSET + 0),
	ADDRESS_NEW_SETPOINT_VALUE_LO(INPUT_OFFSET + 1),
	ADDRESS_NEW_INPUTON_VALUE_HI(INPUT_OFFSET + 2),
	ADDRESS_NEW_INPUTON_VALUE_LO(INPUT_OFFSET + 3),
	ADDRESS_NEW_INPUTOFF_VALUE_HI(INPUT_OFFSET + 4),
	ADDRESS_NEW_INPUTOFF_VALUE_LO(INPUT_OFFSET + 5),
	ADDRESS_NEW_RESOLUTION_VALUE(INPUT_OFFSET + 6)
{
}

void Communication::Setup(Serial_ &serial, uint32_t serialBps)
{
	modbus.config(&serial, serialBps, SERIAL_8N1);
	modbus.setSlaveId(DEVICE_ADDRESS);
	SetupSlaveInputStorage();
	SetupSlaveOutputStorage();
}

void Communication::Update()
{
	modbus.task();
}

void Communication::SetOutputState(uint8_t value)
{
	modbus.Ists(ADDRESS_OUTPUT_STATE, value);
}

void Communication::SetTime(uint32_t value)
{
	modbus.Ireg(ADDRESS_TIME_HI, (value >> 16) & 0xFFFF);
	modbus.Ireg(ADDRESS_TIME_LO, value & 0xFFFF);
}

void Communication::SetTemperature(float value)
{
	floatToWords.f = value;
	modbus.Ireg(ADDRESS_TEMPERATURE_HI, floatToWords.w[1]);
	modbus.Ireg(ADDRESS_TEMPERATURE_LO, floatToWords.w[0]);
}

void Communication::SetMeasureTime(uint32_t value)
{
	modbus.Ireg(ADDRESS_MEASURE_TIME_HI, (value >> 16) & 0xFFFF);
	modbus.Ireg(ADDRESS_MEASURE_TIME_LO, value & 0xFFFF);
}

void Communication::SetSetpoint(float value)
{
	floatToWords.f = value;
	modbus.Ireg(ADDRESS_SETPOINT_HI, floatToWords.w[1]);
	modbus.Ireg(ADDRESS_SETPOINT_LO, floatToWords.w[0]);
}

void Communication::SetInputOn(float value)
{
	floatToWords.f = value;
	modbus.Ireg(ADDRESS_INPUTON_HI, floatToWords.w[1]);
	modbus.Ireg(ADDRESS_INPUTON_LO, floatToWords.w[0]);
}

void Communication::SetInputOff(float value)
{
	floatToWords.f = value;
	modbus.Ireg(ADDRESS_INPUTOFF_HI, floatToWords.w[1]);
	modbus.Ireg(ADDRESS_INPUTOFF_LO, floatToWords.w[0]);
}

void Communication::SetResolution(short value)
{
	modbus.Ireg(ADDRESS_RESOLUTION, value);
}

float Communication::GetFloat(word addresHi, word addressLo)
{
	word hi = modbus.Hreg(addresHi);
	word lo = modbus.Hreg(addressLo);
	floatToWords.w[1] = hi;
	floatToWords.w[0] = lo;
	return floatToWords.f;
}

bool Communication::CheckNewFlag(word flagAddress)
{
	if (modbus.Coil(flagAddress))
	{
		modbus.Coil(flagAddress, false);
		return true;
	}
	else
		return false;
}

bool Communication::CheckNewSetpoint()
{
	return CheckNewFlag(ADDRESS_NEW_SETPOINT);
}

bool Communication::CheckNewInputOn()
{
	return CheckNewFlag(ADDRESS_NEW_INPUTON);
}

bool Communication::CheckNewInputOff()
{
	return CheckNewFlag(ADDRESS_NEW_INPUTOFF);
}

bool Communication::CheckNewResolution()
{
	return CheckNewFlag(ADDRESS_NEW_RESOLUTION);
}

float Communication::GetNewSetPoint()
{
	return GetFloat(ADDRESS_NEW_SETPOINT_VALUE_HI, ADDRESS_NEW_SETPOINT_VALUE_LO);
}

float Communication::GetNewInputOn()
{
	return GetFloat(ADDRESS_NEW_INPUTON_VALUE_HI, ADDRESS_NEW_INPUTON_VALUE_LO);
}

float Communication::GetNewInputOff()
{
	return GetFloat(ADDRESS_NEW_INPUTOFF_VALUE_HI, ADDRESS_NEW_INPUTOFF_VALUE_LO);
}

word Communication::GetNewResolution()
{
	return modbus.Hreg(ADDRESS_NEW_RESOLUTION_VALUE);
}

void Communication::SetupSlaveInputStorage()
{
	modbus.addCoil(ADDRESS_NEW_SETPOINT);
	modbus.addCoil(ADDRESS_NEW_INPUTON);
	modbus.addCoil(ADDRESS_NEW_INPUTOFF);
	modbus.addCoil(ADDRESS_NEW_RESOLUTION);

	modbus.addHreg(ADDRESS_NEW_SETPOINT_VALUE_HI);
	modbus.addHreg(ADDRESS_NEW_SETPOINT_VALUE_LO);
	modbus.addHreg(ADDRESS_NEW_INPUTON_VALUE_HI);
	modbus.addHreg(ADDRESS_NEW_INPUTON_VALUE_LO);
	modbus.addHreg(ADDRESS_NEW_INPUTOFF_VALUE_HI);
	modbus.addHreg(ADDRESS_NEW_INPUTOFF_VALUE_LO);
	modbus.addHreg(ADDRESS_NEW_RESOLUTION_VALUE);
}

void Communication::SetupSlaveOutputStorage()
{
	modbus.addIsts(ADDRESS_OUTPUT_STATE);
	
	modbus.addIreg(ADDRESS_TIME_HI);
	modbus.addIreg(ADDRESS_TIME_LO);
	modbus.addIreg(ADDRESS_TEMPERATURE_HI);
	modbus.addIreg(ADDRESS_TEMPERATURE_LO);
	modbus.addIreg(ADDRESS_MEASURE_TIME_HI);
	modbus.addIreg(ADDRESS_MEASURE_TIME_LO);
	modbus.addIreg(ADDRESS_SETPOINT_HI);
	modbus.addIreg(ADDRESS_SETPOINT_LO);
	modbus.addIreg(ADDRESS_INPUTON_HI);
	modbus.addIreg(ADDRESS_INPUTON_LO);
	modbus.addIreg(ADDRESS_INPUTOFF_HI);
	modbus.addIreg(ADDRESS_INPUTOFF_LO);
	modbus.addIreg(ADDRESS_RESOLUTION);
}