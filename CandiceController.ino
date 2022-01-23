#define SERIAL_ON
#include "SingleStrip.h"
#include "WifiHandler.h"
#include <cstring>
#define RED 16
#define GREEN 5
#define BLUE 4
#define SSID "INFINITUMIU45_2.4"
#define PASS "7uu7YddZbQ"


Color* targetColors;
const Color BI_COLORS[] = { Color(255, 5, 128), Color(170, 0, 200), Color(0, 56, 168) }; //Bi
const Color PAN_COLORS[] = { Color(255, 27, 141), Color(255, 218, 0), Color(27, 179, 255)}; //Pan
//Color targetColors[] = { Color(0, 255, 72), Color(255, 255, 255), Color(255, 0, 38) }; //México
Color initialColor;
int_fast16_t colorIndex;
uint_fast16_t currentLength;
SingleStrip* strip;

void ColorInit();

void StepThroughColors();

void ProcessRequest(const String& request);

void FreeTarget();

void CopyArray(const Color* src, Color* dest, uint_fast16_t length);

void setup() {
	Serial.begin(115200);
	InitializeWifi(SSID, PASS);
	ColorInit();
}

void loop() {
	bool reached = Color::Lerp(&initialColor, targetColors[colorIndex], (1.0f / 100.0f) * 20.0f);
	strip->SetColor(initialColor);
	//Serial.println(initialColor.ToString());
	if (reached) {
		colorIndex++;
		Mathf::CircleBack(&colorIndex, 0, currentLength - 1);
	}

	ReadGetRequestContent(ProcessRequest);
	delay(100);
}

void ColorInit() {
	strip = new SingleStrip(RED, GREEN, BLUE);
	initialColor = Color(0, 0, 0);
	strip->SetColor(initialColor);
	colorIndex = 0;
	currentLength = 3;
	colorIndex = 0;
	targetColors = new Color[currentLength];
	CopyArray(BI_COLORS, targetColors, currentLength);
	Serial.println(targetColors->ToString());
}

void ProcessRequest(const String& request) {
	if (request == "") return;
	Serial.println(request);
	if (request == "Bi") {
		if (targetColors != nullptr) FreeTarget();
		targetColors = new Color[3];
		currentLength = 3;
		colorIndex = 0;
		CopyArray(BI_COLORS, targetColors, currentLength);
		return;
	}
	//Gather the values of the colors in the following format
	//[number]/[hex]/[hex]/[hex]/...
	//Get the first substring by delimitter which is the number of colors in the request
	String nStr = GetSubStrDelimitter(request, '/', 0);
	int n = nStr.toInt();
	int stepLength = nStr.length();
	if (targetColors != nullptr) FreeTarget();
	targetColors = new Color[n];
	currentLength = n;

	//Create a loop to get all the other colors
	String buffer;
	for (uint_fast16_t i = 0; i < n; i++) {
		//Get the color with a delimitter offsetting the request by the accumulative length
		buffer = GetSubStrDelimitter(request, '/', stepLength);
		Serial.print("Hex: ");
		Serial.println(buffer);
		//The buffer now contains the entire hex value, we can feed it to the color
		targetColors[i] = Color::HexToColor(buffer);
		Serial.print("Color: ");
		Serial.println(targetColors[i].ToString());
		//Increment current Length by 6 (hex) + 1 (diagonal)
		stepLength += 7;
	}
	colorIndex = 0;
}

void FreeTarget() {
	delete[] targetColors;
}

void CopyArray(const Color* src, Color* dest, uint_fast16_t length) {
	for (uint_fast16_t i = 0; i < length; i++) {
		dest[i] = src[i];
	}
}