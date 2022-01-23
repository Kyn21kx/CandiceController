#include "SingleStrip.h"

SingleStrip::SingleStrip(uint_fast16_t pinR, uint_fast16_t pinG, uint_fast16_t pinB) {
	this->pinR = pinR;
	this->pinG = pinG;
	this->pinB = pinB;
	this->color = Color();
}

SingleStrip::~SingleStrip() {
	delete this;
}

void SingleStrip::SetColor(Color color) {
	this->color.SetRGB(color.GetRed(), color.GetGreen(), color.GetBlue());
	this->LightUp();
}

void SingleStrip::SetColor(float red, float green, float blue) {
	this->color.SetRGB(red, green, blue);
	this->LightUp();
}

void SingleStrip::FadeCycle(float step) {
	if (this->colorBuffer == Color::BLACK) {
		//Set the color buffer to the current color
		this->colorBuffer = this->color;
	}
	bool reachedBlack = Color::Lerp(&this->color, Color::BLACK, step);
	if (reachedBlack) {

	}
}

void SingleStrip::LightUp() {
	analogWrite(pinR, this->color.GetRed());
	analogWrite(pinG, this->color.GetGreen());
	analogWrite(pinB, this->color.GetBlue());
}
