#include <Arduino.h>
#include "Relay.h"

Relay::Relay()
{
	Setup(HIGH, LOW, 1, -1);
}

Relay::Relay(int outputOn, int outputOff, float inputOn, float inputOff)
{
    Setup(outputOn, outputOff, inputOn, inputOff);
}

void Relay::Setup(int outputOn, int outputOff, float inputOn, float inputOff)
{
    SetOutputOn(outputOn);
	SetOutputOff(outputOff);
	SetInputOn(inputOn);
	SetInputOff(inputOff);
	currentState = OFF;
	output = outputOff;
}

void Relay::SetOutputOn(int outputOn)
{
	this->outputOn = outputOn;
}

void Relay::SetOutputOff(int outputOff)
{
	this->outputOff = outputOff;
}

void Relay::SetInputOn(float inputOn)
{
	if (inputOn < 0.0f)
		inputOn = 0.0f;
	this->inputOn = inputOn;
}

void Relay::SetInputOff(float inputOff)
{
	if (inputOff > 0.0f)
		inputOff = 0.0f;
	this->inputOff = inputOff;
}

int Relay::GetOutput()
{
	return output;
}

int Relay::GetOutput(float input)
{
	if (input >= inputOn)
	{
		currentState = ON;
		output = outputOn;
	}
	else if (input <= inputOff)
	{
		currentState = OFF;
		output = outputOff;
	}
	else
	{
		if (currentState == ONMIDDLE)
			output = outputOn;
		else if (currentState == OFFMIDDLE)
			output = outputOff;
		else if (currentState == ON)
		{
			currentState = ONMIDDLE;
			output = outputOn;
		}
		else if (currentState == OFF)
		{
			currentState = OFFMIDDLE;
			output = outputOff;
		}
	}
	return output;
}

float Relay::GetInputOn()
{
	return inputOn;
}

float Relay::GetInputOff()
{
	return inputOff;
}

Relay::State Relay::GetState()
{
	return currentState;
}
