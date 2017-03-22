
const int RAILROAD_DURATION = 10000; // 10 sec
const int LIGHTS_INTERVAL = 500; // 0.5 sec
unsigned long railRoadDuration;
bool areLightsOn;

bool state; // just a value for toggling LEDs
unsigned long blinkingDuration;

/*
Determines if and how long the railroad lights blinks.
Reads value from IR sensor and manages time for the lamps
*/
void railRoadManager()
{
	unsigned long d = millis() - railRoadDuration;
	if (areLightsOn && d <= RAILROAD_DURATION)
	{
		// should still blinking, the duration is less than the set timeout
		railRoadBlink();
		return;
	}

	// check if the sensor analog value is less than the set threshold
	// if so, start blinking, if not switch the lamps off 
	//(NOTE: if the time hasn't timed out yet, the function is exited above)
	areLightsOn = false;
	if (analogRead(irSensor1) < IR1_THRESHOLD)
	{
		areLightsOn = true;
		railRoadDuration = millis();
		railRoadBlink();
	}
	else
	{
		railRoadDuration = 0;
		manageLights(true, false);
	}
}

/*
Blinks the LEDs in set interval
*/
void railRoadBlink()
{
	if (blinkingDuration == 0) blinkingDuration = millis();

	unsigned long d = millis() - blinkingDuration;
	if (d >= LIGHTS_INTERVAL)
	{
		manageLights(false, state);
		state = !state;
		blinkingDuration = 0;
	}
}

// Changes the values for the railroad LEDs
void manageLights(bool isOff, bool ledState)
{
	if (isOff)
	{
		digitalWrite(railRoadLED1, LOW);
		digitalWrite(railRoadLED2, LOW);
		return;
	}

	digitalWrite(railRoadLED1, ledState);
	digitalWrite(railRoadLED2, !ledState);

}
