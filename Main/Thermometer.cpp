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
    RequestNewResolution(resolution);
	ApplyNewResolution();
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

void Thermometer::RequestNewResolution(Thermometer::Resolution resolution)
{
	newResolutionRequest = true;
	newResolutionValue = resolution;
}

void Thermometer::RequestNewResolution(word value)
{
	if (value < Thermometer::RESOLUTION9Bits)
		value = Thermometer::RESOLUTION9Bits;
	else if (value > Thermometer::RESOLUTION12Bits)
		value = Thermometer::RESOLUTION12Bits;
	RequestNewResolution(static_cast<Thermometer::Resolution>(value));
}

bool Thermometer::ApplyNewResolution()
{
	if (newResolutionRequest)
	{
		sensor->setResolution((uint8_t*)address, newResolutionValue, true);
		this->resolution = newResolutionValue;
		newResolutionRequest = false;
		return true;
	}
	else
		return false;
}

Thermometer::Resolution Thermometer::GetResolution()
{
    return static_cast<Thermometer::Resolution>(resolution);
}
