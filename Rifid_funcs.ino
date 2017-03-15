
// Increase the first dimension of the trains arrays when a new train is added
int trains[2][4] = {
	{ 0x2B, 0x45, 0xE7, 0xB9 }, // train 1 
	{ 0x2A, 0x48, 0xA9, 0xAB }  // train 2
};

/*
Responsible for managing the RFID reader
If a tag is recognized, sends a message LED matrix
*/
void rfidManager()
{
	// no card
	if (!rfid.PICC_IsNewCardPresent()) return;

	// check if we can read the tag
	if (!rfid.PICC_ReadCardSerial())return;

	if (isRecognized())
	{
		//TODO: Print the MIFARE_Key		
		Serial.println("train found");
	}
	else
	{
		Serial.print("The card is not recognized:");
		writeCardTag(rfid.uid.uidByte, rfid.uid.size);
	}

	// finish the communication and crypting
	rfid.PICC_HaltA();
	rfid.PCD_StopCrypto1();
}

/*
Checks if a train is found in the array of trains
Returns true if train is found, otherwise false
*/
bool isRecognized()
{	
	int numOfTrains =	sizeof(trains) / sizeof(trains[0]);
	bool retVal = true;
	for (int i = 0; i < numOfTrains; i++)
	{
		retVal = true;
		for (int j = 0; j < 4; j++)
		{			
			if (rfid.uid.uidByte[j] != trains[i][j]) {				
				retVal = false;
				break;
			}
		}
	}	
	return retVal;
}

/*
Writes card rags into the serial monitor
*/
void writeCardTag(byte *buffer, byte bufferSize) {
	for (byte i = 0; i < bufferSize; i++) {
		Serial.print(buffer[i] < 0x10 ? " 0" : " ");
		Serial.print(buffer[i], HEX);
	}
}
