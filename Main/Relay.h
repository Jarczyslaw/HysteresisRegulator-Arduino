#pragma once

#include <Arduino.h>

class Relay
{
	public:
		enum State
		{
			OFF,
			OFFMIDDLE,
			ONMIDDLE,
			ON
		};
		Relay();
		Relay(int, int, float, float);

		void Setup(int, int, float, float);
		void SetOutputOn(int);
		void SetOutputOff(int);
		void SetInputOn(float);
		void SetInputOff(float);
		float GetInputOn();
		float GetInputOff();
		int GetOutput(float);
		int GetOutput();
		State GetState();
	private:
		int output;
		int outputOn;
		int outputOff;
		float inputOn;
		float inputOff;
		State currentState;
};
