#include <Arduino.h>
#include "DigitalOut.h"

DigitalOut::DigitalOut(int port, uint8_t initialState)
{
    this->port = port;
    pinMode(port, OUTPUT);
    Set(initialState);
}

void DigitalOut::Set(uint8_t state)
{
    digitalWrite(this->port, state);
}

void DigitalOut::Toggle()
{
    uint8_t currentState = Get();
    if (currentState == LOW)
        Set(HIGH);
    else
        Set(LOW);
}

uint8_t DigitalOut::Get()
{
    return digitalRead(this->port);
}
