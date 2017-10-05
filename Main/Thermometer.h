#pragma once

#include "DallasTemperature.h"
#include "OneWire.h"
#include "TickTock.h"

class Thermometer
{
    public:
        enum Resolution
        {
            RESOLUTION0_5 =		9,
            RESOLUTION0_25 =	10,
            RESOLUTION0_125 =	11,
            RESOLUTION0_0625 =	12
        };
        Thermometer(int);
        void Begin(Thermometer::Resolution);
        bool IsConnected();
        void RequestTemperature();
        bool TemperatureReady();
        float ReadTemperature();
        float GetLastTemperature();
        uint32_t GetLastMeasureTime();
        void SetResolution(Thermometer::Resolution);
		void SetResolution(word);
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
};
