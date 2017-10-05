#pragma once

#include <Arduino.h>

class TickTock
{
    public:
        TickTock();
        void Tick();
        uint32_t Tock();
    protected:
    private:
        uint32_t tickTime;
};
