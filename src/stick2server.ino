#include <M5StickCPlus2.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "lib/.secrets.h"

String txt = "";
int count = 0;
bool first = true;

void setup()
{
	M5.begin();

	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(1000);
		M5.Lcd.print(".");
	}

	M5.Lcd.println("Connected to WiFi");
	M5.Lcd.fillScreen(BLACK);
}

void sendMessage(const String &message)
{
	HTTPClient http;
	http.begin(server_url);
	http.addHeader("Content-Type", "application/x-www-form-urlencoded");

	String postData = "message=" + message;
	int statusCode = http.POST(postData);

	if (statusCode == 200)
	{
		String response = http.getString();
		// M5.Lcd.println("Response: " + response);
		// M5.Lcd.println(message);
	}
	else
		M5.Lcd.println("Error: " + String(statusCode));

	http.end();
}

void updateDisplay()
{
	M5.Lcd.fillScreen(BLACK);
	M5.Lcd.drawCentreString(String(count), M5.Lcd.width() / 2, M5.Lcd.height() / 2, 7);
}

void loop()
{
	M5.update();
	M5.Lcd.setCursor(0, 0);
	if (first)
	{
		updateDisplay();
		first = false;
	}
	
	if (M5.BtnA.isPressed())
	{
		count++;
		txt = "Button A pressed " + String(count);
		sendMessage(txt);
		updateDisplay();
	}

	if (M5.BtnB.isPressed())
	{
		count--;
		txt = "Button B pressed " + String(count);
		sendMessage(txt);
		updateDisplay();
	}

	delay(100);
}