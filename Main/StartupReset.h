#pragma once

#include <Arduino.h>

class StartupReset
{
public:
	StartupReset(uint8_t);
	bool CheckReset();
private:
	uint8_t port;
};

