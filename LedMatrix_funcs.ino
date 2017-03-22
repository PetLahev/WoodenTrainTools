
/* we always wait a bit between updates of the display */
unsigned long ledDelayTime = 300;
char ch0, ch1; // just two matrixes
int nextCharIndex = 0;

/*
Responsible for setting up the LED Matrix displays
*/
void ledMatrixSetup()
{
	for (int i = 0; i< NBR_MTX; i++) {
		lc.shutdown(i, false);
		/* Set the brightness to a medium values */
		lc.setIntensity(i, 8);
		/* and clear the display */
		lc.clearDisplay(i);
	}
	lc.clearAll();	
}

/*
Display the given text, scrolling left
*/
void display(String text)
{		
	lc.clearAll();
	delay(25);
	
	int stringLength = text.length();
	ch0 = text[0];
	ch1 = text[1];
	nextCharIndex = 2;
	
	for (int i = 0; i < (stringLength-1); i++)
	{		
		lc.displayChar(0, lc.getCharArrayPosition(ch0));
		lc.displayChar(1, lc.getCharArrayPosition(ch1));
		ch0 = ch1;
		ch1 = text[nextCharIndex++];
		if (nextCharIndex >= stringLength) nextCharIndex = 0;
		delay(ledDelayTime);
		lc.clearAll();
	}	
}