#pragma once

#include <Arduino.h>

class DigitalOut
{
    public:
        DigitalOut(int, uint8_t);
        void Toggle();
        void Set(uint8_t);
        uint8_t Get();
    private:
        int port;
};
