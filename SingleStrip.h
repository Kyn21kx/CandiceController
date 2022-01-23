#pragma once
#include "Color.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class SingleStrip {
public:
	SingleStrip(uint_fast16_t pinR, uint_fast16_t pinG, uint_fast16_t pinB);
	
	~SingleStrip();

	void SetColor(Color color);

	void SetColor(float red, float green, float blue);

	//Fades the current color back and forth
	void FadeCycle(float step);

private:
	Color color;
	Color colorBuffer = Color::BLACK;
	uint_fast16_t pinR, pinG, pinB;

	void LightUp();
};
