
String digits = "1234567890";

void smajlik()
{
	Serial.println("Smajlik START");
	lc.setLed(0, 1, 5, true);
	lc.setLed(0, 1, 6, true);
	lc.setLed(0, 2, 5, true);
	lc.setLed(0, 2, 6, true);

	lc.setLed(0, 5, 5, true);
	lc.setLed(0, 5, 6, true);
	lc.setLed(0, 6, 5, true);
	lc.setLed(0, 6, 6, true);

	lc.setLed(0, 3, 3, true);
	lc.setLed(0, 4, 3, true);
	lc.setLed(0, 3, 2, true);
	lc.setLed(0, 4, 2, true);

	lc.setLed(0, 2, 1, true);
	lc.setLed(0, 3, 0, true);
	lc.setLed(0, 4, 0, true);
	lc.setLed(0, 5, 1, true);
	

	char ch0 = 'A';
	lc.displayChar(1, lc.getCharArrayPosition(ch0));
	delay(2000);

}