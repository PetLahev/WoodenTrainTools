
#include <AsyncDelay.h>
void setup() {

	Serial.begin(9600);
	Serial.println("Setup pins");
	pinMode(A4, OUTPUT);
	pinMode(A5, OUTPUT);
	pinMode(A0, INPUT);
}

unsigned long duration;
bool state;
void trafficLamp()
{
	if (duration == 0)
	{
		Serial.println("Initialization");
		Serial.print("State: ");
		Serial.println(state);
		duration = millis();
	}

	unsigned d = millis() - duration;
	Serial.print("Duration: ");
	Serial.println(d);
	if (d >= 500)
	{
		Serial.println("Blinking: ");
		Serial.print("State: ");
		Serial.println(state);
		digitalWrite(A4, state);
		digitalWrite(A5, !state);
		state = !state;
		duration = 0;
	}
}

bool isOn;
unsigned long semafor;
void loop() {

	Serial.print("Is on ");
	Serial.println(isOn);
	unsigned long d = millis() - semafor;
	if (isOn && d <= 10000)
	{
		trafficLamp();
		return;
	}
	else
	{
		Serial.println(d);
		isOn = false;
	}

	int v = analogRead(A0);
	if (v < 150)
	{
		isOn = true;
		semafor = millis();
		trafficLamp();
	}
	else
	{
		semafor = 0;
		digitalWrite(A4, LOW);
		digitalWrite(A5, LOW);
	}
}