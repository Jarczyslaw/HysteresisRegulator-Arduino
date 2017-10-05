#include "Thermometer.h"

Thermometer::Thermometer(int port): INVALID_TEMPERATURE(-127)
{
    oneWire = new OneWire(port);
    sensor = new DallasTemperature(oneWire);
    measureTick = new TickTock();
    measureDone = false;
    measureInProgress = false;
}

void Thermometer::Begin(Thermometer::Resolution resolution)
{
    sensor->begin();
    connected = sensor->getAddress(address, 0);
    SetResolution(resolution);
}

void Thermometer::RequestTemperature()
{
    if (!connected)
        return;

    if (!measureInProgress)
    {
        measureTick->Tick();
        sensor->requestTemperaturesNoDelay();
        measureInProgress = true;
    }
}

bool Thermometer::TemperatureReady()
{
    if (!connected)
        return false;

    if (!sensor->isConversionComplete())
        return false;

    measureInProgress = false;
    measureDone = true;
    lastMeasureTime = measureTick->Tock();
    return true;
}

float Thermometer::ReadTemperature()
{
    if (measureDone)
    {
        lastTemperature = sensor->getTempC((uint8_t*)address);
        return lastTemperature;
    }
    else
        return INVALID_TEMPERATURE;
}

float Thermometer::GetLastTemperature()
{
    if (measureDone)
        return lastTemperature;
    else
        return INVALID_TEMPERATURE;
}

uint32_t Thermometer::GetLastMeasureTime()
{
    if (measureDone)
        return lastMeasureTime;
    else
        return 0;
}

bool Thermometer::IsConnected()
{
    return connected;
}

void Thermometer::SetResolution(Thermometer::Resolution resolution)
{
	this->resolution = resolution;
    sensor->setResolution((uint8_t*)address, resolution, true);
}

void Thermometer::SetResolution(word value)
{
	if (value < Thermometer::RESOLUTION0_5)
		value = Thermometer::RESOLUTION0_5;
	else if (value > Thermometer::RESOLUTION0_0625)
		value = Thermometer::RESOLUTION0_0625;
	Thermometer::Resolution resolution = static_cast<Thermometer::Resolution>(value);
	SetResolution(resolution);
}

Thermometer::Resolution Thermometer::GetResolution()
{
    return static_cast<Thermometer::Resolution>(resolution);
}
