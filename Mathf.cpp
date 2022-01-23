#include "Mathf.h"

void Mathf::Clamp(float* value, float minValue, float maxValue) {
	if (*value > maxValue) {
		*value = maxValue;
		return;
	}

	if (*value < minValue) *value = minValue;
}

void Mathf::Lerp(float* value, float limit, float step) {
	*value = *value + step * (limit - *value);
}

void Mathf::CircleBack(int_fast16_t* value, int_fast16_t minValue, int_fast16_t maxValue) {
	if (*value > maxValue)
		*value = minValue;
	else if (*value < minValue)
		*value = maxValue;
}

uint_fast16_t Mathf::Hex2int(char* hex) {
    Serial.printf("Received Hex: %s\n", hex);
    uint_fast16_t val = 0;
    while (*hex) {
        // get current character then increment
        char byte = *hex++;
        // transform hex character to the 4bit equivalent number, using the ascii table indexes
        if (byte >= '0' && byte <= '9') byte = byte - '0';
        else if (byte >= 'a' && byte <= 'f') byte = byte - 'a' + 10;
        else if (byte >= 'A' && byte <= 'F') byte = byte - 'A' + 10;
        // shift 4 to make space for new digit, and add the 4 bits of the new digit
        val = (val << 4) | (byte & 0xF);
    }
    return val;
}


