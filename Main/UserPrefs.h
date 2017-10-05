#pragma once

#include "EEPROMex.h"
#include "Thermometer.h"

class UserPrefs
{
    public:
        UserPrefs();

        void SetSetPoint(float);
        float GetSetPoint(float);
        void SetRelayInputOn(float);
        float GetRelayInputOn(float);
        void SetRelayInputOff(float);
        float GetRelayInputOff(float);
        void SetResolution(Thermometer::Resolution resolution);
        Thermometer::Resolution GetThermometerResolution(Thermometer::Resolution);
        void Clear();

        template <class T> void Set(int flagAddress, int valueAddress, T value)
        {
            EEPROM.updateBit(flagAddress, 0, true);
            EEPROM.updateBlock<T>(valueAddress, value);
        }

        template <class T> T Get(int flagAddress, int valueAddress, T defaultValue)
        {
            if (EEPROM.readBit(flagAddress, 0))
            {
                T value;
                EEPROM.readBlock<T>(valueAddress, value);
                return value;
            }
            else
                return defaultValue;
        }
    protected:
    private:
        enum
        {
            ADDRESS_FLAG_SET_POINT =        0,
            ADDRESS_SET_POINT =             1,
            ADDRESS_FLAG_RELAY_INPUT_ON =   3,
            ADDRESS_RELAY_INPUT_ON =        4,
            ADDRESS_FLAG_RELAY_INPUT_OFF =  6,
            ADDRESS_RELAY_INPUT_OFF =       7,
            ADDRESS_FLAG_THERM_RESOLUTION = 9,
            ADDRESS_THERM_RESOLUTION =      10
        };
};
