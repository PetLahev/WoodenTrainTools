
// Increase the first dimension of the trains arrays when a new train is added
int trains[2][4] = {
	{ 0x00, 0x01, 0xB3, 0x4F }, // train 1 
	{ 0x2A, 0x48, 0xA9, 0xAB }  // train 2
};

// Textual representation of tags TODO: Ideally this will be somehow written on the card
String trainsDescription[] = { "Train 1", "Train 2" };

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

	int trainIndex = 0;
	if (isRecognized(trainIndex))
	{		
		Serial.println(trainsDescription[trainIndex]);
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
trainIndex - returns index of the train in the trains array
*/
bool isRecognized(int &trainIndex)
{	
	int numOfTrains = sizeof(trains) / sizeof(trains[0]);	
	bool retVal = true;
	for (int i = 0; i < numOfTrains; i++)
	{
		retVal = true;
		for (int j = 0; j < 4; j++)
		{			
			//printTags(i, j);
			if (rfid.uid.uidByte[j] != trains[i][j]) {				
				retVal = false;
				break;
			}
		}
		trainIndex = i;
		if (retVal) break; // found the train, no need to do another loop
	}	
	return retVal;
}

/* Helper function*/
void printTags(int trainIndex, int j)
{
	Serial.print("Tag[");
	Serial.print(j);
	Serial.print("] = ");
	Serial.print(rfid.uid.uidByte[j]);
	Serial.print(" == ");
	Serial.print("Trains[");
	Serial.print(trainIndex);
	Serial.print("][");
	Serial.print(j);
	Serial.print("] = ");
	Serial.print(trains[trainIndex][j]);
	Serial.print(" => ");
	Serial.println(rfid.uid.uidByte[j] == trains[trainIndex][j]);
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
