#pragma once
#include "ESP8266WiFi.h"
//Turn this shit into a macro

WiFiServer server(80);

void InitializeWifi(const char* ssid, const char* pass);

#define ReadGetRequestContent(process) {\
	WiFiClient client = server.available();\
	if (client) {\
		while (!client.available()) delay(1);\
		String request = client.readStringUntil('\r');\
		request = GetSubStrDelimitter(request, ' ', 5);\
		process(request);\
		client.println("HTTP/1.1 200 OK");\
	}\
}

String GetSubStrDelimitter(const String& str, char delimitter, uint16_t offset);

/// <summary>
/// Initializes the Wifi handler connecting to the network and starting the server
/// </summary>
/// <param name="ssid">WiFi network's name</param>
/// <param name="pass">WiFi network's password</param>
void InitializeWifi(const char* ssid, const char* pass) {
	WiFi.begin(ssid, pass);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
#ifdef SERIAL_ON
		Serial.print(".");
#endif
	}
#ifdef SERIAL_ON
	Serial.println("Connected!");
	Serial.print("IP: ");
	Serial.println(WiFi.localIP());
#endif
	server.begin();
}

String GetSubStrDelimitter(const String &str, char delimitter, uint16_t offset) {
	String sub = "";
	for (uint16_t i = offset; i < str.length(); i++) {
		sub += str[i];
		if (str[i] == delimitter) break;
	}
	return sub;
}