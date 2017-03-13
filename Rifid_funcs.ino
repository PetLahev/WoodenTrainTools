
// Increase the first dimension of the trains arrays when a new train is added
int trains[1][4] = {
	{ 0x52, 0x3D, 0x5A, 0xFF } // train 1
};

/*

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
	// TODO: Can I use sizeOf instead of hardcoded values?
	// int size = sizeof(trains[0]) / sizeof(int);
	bool retVal = true;
	for (int i = 0; i < 1; i++)
	{
		retVal = true;
		for (int j = 0; j < 4; i++)
		{
			if (rfid.uid.uidByte[j] != trains[i][j]) {
				retVal = false;
				break;
			}
		}
	}	
	return retVal;
}