/*
---->>>>>>  A learning project  <<<<<<<----

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
#define NBR_MTX 2 // number of LED matrixes
#define DIN_PIN 7
#define CS_PIN 6
#define CLK_PIN 5
LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, NBR_MTX);
//  ------ LED Matrix settings ------ 

//  ------ RailRoad settings ------
int railRoadLED1 = A4;
int railRoadLED2 = A5;
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