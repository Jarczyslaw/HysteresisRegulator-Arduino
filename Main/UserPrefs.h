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

        
    protected:
    private:
        enum
        {
            ADDRESS_FLAG_SET_POINT =        0,
            ADDRESS_SET_POINT =             1,
            ADDRESS_FLAG_RELAY_INPUT_ON =   5,
            ADDRESS_RELAY_INPUT_ON =        6,
            ADDRESS_FLAG_RELAY_INPUT_OFF =  10,
            ADDRESS_RELAY_INPUT_OFF =       11,
            ADDRESS_FLAG_THERM_RESOLUTION = 15,
            ADDRESS_THERM_RESOLUTION =      16
        };
		int totalBytesUsed = 20;

		template <class T> void Set(int flagAddress, int valueAddress, T value)
		{
			EEPROM.updateByte(flagAddress, true);
			EEPROM.updateBlock<T>(valueAddress, value);
		}

		template <class T> T Get(int flagAddress, int valueAddress, T defaultValue)
		{
			if (EEPROM.readByte(flagAddress))
			{
				T value;
				EEPROM.readBlock<T>(valueAddress, value);
				return value;
			}
			else
				return defaultValue;
		}
};
