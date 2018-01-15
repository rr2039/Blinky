#include "DriverStation2_0.hpp"
#include "FlashModes.hpp"

// Constants for pin numbers
const uint8_t LEDPINS[4] = {5, 6, 9, 10}; /* IC pins 16, 15, 12, and 11 */
const uint8_t BUTTONPIN = 2; /* Change mode button, IC Pin 4. */
const uint8_t AWHEELPIN = 2; /* Potentiometer for looping speed. This means Analog pin 2 */

// Modes of operation.  Setup is our initial mode and should not be used any time other
// 		than at startup.
enum Modes {SETUP, SOLID, FLASHING, LOOPING, PULSING, OFF};
volatile Modes mode = SETUP; /* Current mode.  Volatile due to ISR */
uint8_t ledValues[4] = {0, 0, 0, 0};
uint16_t potValue = 0;

// Counter variable.  Earlier iterations of this design had problems skipping wraps and modulos on millisecond timer, so use counter instead.
uint16_t counter;

//The setup function is called once at startup of the sketch
void setup()
{
	// Initialize the LED pins and set them all HIGH to start with.
	for(int i = 0; i<4; i++)
	{
		// pinMode(LEDPINS[i], OUTPUT);
		analogWrite(10, 255);
	}
	pinMode(BUTTONPIN, INPUT_PULLUP);

	// Register the interrupt for the change mode button.
	attachInterrupt(digitalPinToInterrupt(BUTTONPIN), changeMode, FALLING);

	// Finally, change our mode to solid.
	mode = SOLID;
}

void changeMode()  // ISR for BUTTONPIN
{
	if(digitalRead(BUTTONPIN) == 0)
	{
		if (mode == OFF)
			mode = SOLID;
		else
			// "increment" mode.  Since we can't do it natively, we have to do casting magic.
			mode = (Modes)(1+(uint8_t)mode);
	}
}

// The loop function is called in an endless loop
void loop()
{
	// Increment the counter value of this frame
	counter++;

	// Run the frame function of whatever mode we're in.
	switch(mode)
	{
	case SETUP:
		// Dunno why you'd be here, but whatevs.
		mode = SOLID;
		break;
	case SOLID:
		solid();
		break;
	case FLASHING:
		flashing();
		break;
	case LOOPING:
		looping();
		break;
	case PULSING:
		pulsing();
		break;
	case OFF:
		off();
		break;
	}

	// Update the output pins with the value of ledValues[]
	for(int i = 0; i < 4; i++)
	{
		analogWrite(LEDPINS[i], ledValues[i]);
	}
}
