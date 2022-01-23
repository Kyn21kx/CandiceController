#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

namespace Mathf {

	void Clamp(float* value, float minValue, float maxValue);

	void Lerp(float* value, float limit, float step);

	void CircleBack(int_fast16_t* value, int_fast16_t minValue, int_fast16_t maxValue);

    //Function provided by stack overflow's radhoo
	//https://stackoverflow.com/questions/10324/convert-a-hexadecimal-string-to-an-integer-efficiently-in-c
	uint_fast16_t Hex2int(char* hex);
}
