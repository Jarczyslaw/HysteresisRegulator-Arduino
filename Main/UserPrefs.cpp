#include "UserPrefs.h"
#include "EEPROMex.h"

UserPrefs::UserPrefs() { }

void UserPrefs::SetSetPoint(float setPoint)
{
    Set<float>(ADDRESS_FLAG_SET_POINT, ADDRESS_SET_POINT, setPoint);
}

float UserPrefs::GetSetPoint(float defaultValue)
{
    return Get<float>(ADDRESS_FLAG_SET_POINT, ADDRESS_SET_POINT, defaultValue);
}

void UserPrefs::SetRelayInputOn(float inputOn)
{
    Set<float>(ADDRESS_FLAG_RELAY_INPUT_ON, ADDRESS_RELAY_INPUT_ON, inputOn);
}

float UserPrefs::GetRelayInputOn(float defaultValue)
{
    return Get<float>(ADDRESS_FLAG_RELAY_INPUT_ON, ADDRESS_RELAY_INPUT_ON, defaultValue);
}

void UserPrefs::SetRelayInputOff(float inputOn)
{
    Set<float>(ADDRESS_FLAG_RELAY_INPUT_OFF, ADDRESS_RELAY_INPUT_OFF, inputOn);
}

float UserPrefs::GetRelayInputOff(float defaultValue)
{
    return Get<float>(ADDRESS_FLAG_RELAY_INPUT_OFF, ADDRESS_RELAY_INPUT_OFF, defaultValue);
}

void UserPrefs::SetResolution(Thermometer::Resolution resolution)
{
    Set<int>(ADDRESS_FLAG_THERM_RESOLUTION, ADDRESS_THERM_RESOLUTION, resolution);
}

Thermometer::Resolution UserPrefs::GetThermometerResolution(Thermometer::Resolution defaultValue)
{
    int res = Get<int>(ADDRESS_FLAG_THERM_RESOLUTION, ADDRESS_THERM_RESOLUTION, defaultValue);
    return static_cast<Thermometer::Resolution>(res);
}

void UserPrefs::Clear()
{
    for(int i = 0;i < 12;i++)
        EEPROM.writeByte(i, 0);
}
