#include "Color.h"

const Color Color::BLACK = Color();

const Color Color::WHITE = Color(255, 255, 255);

Color::Color() {
	this->red = 0;
	this->green = 0;
	this->blue = 0;
}

Color::Color(float red, float green, float blue) {
	this->SetRed(red);
	this->SetGreen(green);
	this->SetBlue(blue);
}

Color Color::operator+(Color const& other) const {
	Color res = *this;
	res.red += other.red;
	res.green += other.green;
	res.blue += other.blue;
	return res;
}

Color Color::operator-(Color const& other) const {
	Color res = *this;
	res.red -= other.red;
	res.green -= other.green;
	res.blue -= other.blue;
	return res;
}

bool Color::operator==(Color const& other) const {
	return this->blue == other.blue && this->red == other.red && this->green == other.green;
}

bool Color::operator!=(Color const& other) const {
	return this->blue != other.blue || this->red != other.red || this->green != other.green;
}

float Color::GetRed() const {
	return this->red;
}

float Color::GetGreen() const {
	return this->green;
}

float Color::GetBlue() const {
	return this->blue;
}

float Color::GetSqrMagnitude() const {
	return (this->red * this->red) + (this->green * this->green) + (this->blue * this->blue);
}

float Color::GetMagnitude() const {
	return sqrtf(this->GetSqrMagnitude());
}

float Color::Dot(Color const& other) const {
	float i, j, k;
	i = this->red * other.red;
	j = this->green * other.green;
	k = this->blue * other.blue;
	return i + j + k;
}

void Color::SetRed(float red) {
	this->red = red;
	Mathf::Clamp(&this->red, 0, 255);
}

void Color::SetGreen(float green) {
	this->green = green;
	Mathf::Clamp(&this->green, 0, 255);
}

void Color::SetBlue(float blue) {
	this->blue = blue;
	Mathf::Clamp(&this->blue, 0, 255);
}

void Color::SetRGB(float red, float green, float blue) {
	this->SetRed(red);
	this->SetGreen(green);
	this->SetBlue(blue);
}

String Color::ToString() const {
	//Yeah, don't question it
	String result = "(";
	result.concat(this->red);
	result.concat(", ");
	result.concat(this->green);
	result.concat(", ");
	result.concat(this->blue);
	result.concat(")");
	return result;
}

bool Color::Lerp(Color* a, Color const& b, float step) {
	float threshold = 0.01f;
	float disSqr = Color::DistanceSqr(*a, b);
	if (disSqr < threshold * threshold) return true;
	Mathf::Lerp(&(*a).red, b.red, step);
	Mathf::Lerp(&(*a).green, b.green, step);
	Mathf::Lerp(&(*a).blue, b.blue, step);
	return false;
}

float Color::DistanceSqr(Color const& a, Color const& b) {
	Color adjustedVector = a - b;
	return adjustedVector.GetSqrMagnitude();
}

Color Color::HexToColor(const String& hexString) {
	uint_fast16_t r = Mathf::Hex2int((char*)hexString.substring(0, 2).c_str());
	uint_fast16_t g = Mathf::Hex2int((char*)hexString.substring(2, 4).c_str());
	uint_fast16_t b = Mathf::Hex2int((char*)hexString.substring(4, 6).c_str());
	return Color(r, g, b);
}
