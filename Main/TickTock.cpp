#include "TickTock.h"

TickTock::TickTock() { }

void TickTock::Tick()
{
    tickTime = millis();
}

uint32_t TickTock::Tock()
{
    return millis() - tickTime;
}
