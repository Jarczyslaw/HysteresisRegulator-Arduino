#pragma once

#include "DallasTemperature.h"
#include "OneWire.h"
#include "TickTock.h"

class Thermometer
{
    public:
        enum Resolution
        {
            RESOLUTION9Bits =		9,
            RESOLUTION10Bits =		10,
            RESOLUTION11Bits =		11,
            RESOLUTION12Bits =		12
        };
        Thermometer(int);
        void Begin(Thermometer::Resolution);
        bool IsConnected();
        void RequestTemperature();
        bool TemperatureReady();
        float ReadTemperature();
        float GetLastTemperature();
        uint32_t GetLastMeasureTime();
        void RequestNewResolution(Thermometer::Resolution);
		void RequestNewResolution(word);
		bool ApplyNewResolution();
        Thermometer::Resolution GetResolution();
    protected:
    private:
        OneWire* oneWire;
        DallasTemperature* sensor;
        TickTock* measureTick;
        DeviceAddress address;
        Thermometer::Resolution resolution;
        bool connected;
        bool measureInProgress;
        bool measureDone;
        float lastTemperature;
        uint32_t lastMeasureTime;
		const float INVALID_TEMPERATURE;
		bool newResolutionRequest;
		Thermometer::Resolution newResolutionValue;
};
