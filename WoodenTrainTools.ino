/*
---->>>>>>  A learning project

Should provide certain tools for wooden trains
March 2017	- Added railroads lights functionality without delay (after experimenting with lots of available timer libraries)
			- Added Rfid functionality	
			- Added LED Matrix
*/

#include <LedControlMS.h>
#include <MFRC522.h>
#include <SPI.h>

int irSensor1 = A0;
const int IR1_THRESHOLD = 150;

//  ------ RFID settings ------ 
#define SDA_PIN 10
#define RST_PIN 9
MFRC522 rfid(SDA_PIN, RST_PIN);
//  ------ RFID settings ------ 

//  ------ LED Matrix settings ------ 
#define NBR_MTX 2 // number of LED
#define DIN_PIN 7
#define CS_PIN 6
#define CLK_PIN 5
LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, NBR_MTX);
//  ------ LED Matrix settings ------ 

//  ------ RailRoad settings ------
const int RAILROAD_DURATION = 10000; // 10 sec
const int LIGHTS_INTERVAL = 500; // 0.5 sec
unsigned long railRoadDuration;
int railRoadLED1 = A4;
int railRoadLED2 = A5;
bool areLightsOn;
//  ------ RailRoad settings ------

void setup()
{
	Serial.begin(9600);	
	SPI.begin();
	rfid.PCD_Init();
	ledMatrixSetup();
	pinMode(railRoadLED1, OUTPUT); 
	pinMode(railRoadLED2, OUTPUT); 
	pinMode(irSensor1, INPUT);		
}

void loop()
{	
	railRoadManager();
	rfidManager();
}


bool state; // just a value for toggling LEDs
unsigned long blinkingDuration;
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