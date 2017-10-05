#include "StartupReset.h"

StartupReset::StartupReset(uint8_t port)
{
	this->port = port;
	pinMode(port, INPUT);
	digitalWrite(port, HIGH);
}

bool StartupReset::CheckReset()
{
	return digitalRead(port) == 0;
}
