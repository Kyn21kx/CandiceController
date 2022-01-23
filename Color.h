#include "Mathf.h"
#include "arduino.h"

class Color {
public:
	static const Color BLACK;

	static const Color WHITE;

	Color();

	Color(float red, float green, float blue);

	Color operator + (Color const& other) const;

	Color operator - (Color const& other) const;

	bool operator == (Color const& other) const;

	bool operator != (Color const& other) const;

	float GetRed() const;

	float GetGreen() const;

	float GetBlue() const;

	float GetSqrMagnitude() const;

	float GetMagnitude() const;

	float Dot(Color const& other) const;

	void SetRed(float red);

	void SetGreen(float green);

	void SetBlue(float blue);

	void SetRGB(float red, float green, float blue);

	String ToString() const;

	static bool Lerp(Color* a, Color const& b, float step);

	static float DistanceSqr(Color const& a, Color const& b);

	static Color HexToColor(const String& hexString);

private:
	float red, green, blue;
};

