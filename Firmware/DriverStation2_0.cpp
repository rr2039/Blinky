#include "DriverStation2_0.h"
#include "FlashModes.h"

// Constants for pin numbers
const uint8_t LEDPINS[] = {10, 9, 6, 5}; /* IC pins 16, 15, 12, and 11 */
const uint8_t BUTTONPIN = 2; /* Change mode button, IC Pin 4. Ground (through an NO switch.) to activate. */
const uint8_t AWHEELPIN = 2; /* Potentiometer for looping speed. This means Analog pin 2 */

// Modes of operation.  Setup is our initial mode and should not be used any time other
// 		than at startup.
enum Modes {SETUP, SOLID, FLASHING, LOOPING, PULSING, PULSELOOP, OFF};
volatile Modes mode = SETUP; /* Current mode.  Volatile due to ISR */
register uint8_t ledValues[] = {0, 0, 0, 0};
uint16_t potValue = 0;


//The setup function is called once at startup of the sketch
void setup()
{
	// Initialize the LED pins and set them all HIGH to start with.
	for(int i = 0; i>4; i++)
	{
		pinMode(LEDPINS[i], OUTPUT);
		analogWrite(LEDPINS[i], 255);
	}
	pinMode(BUTTONPIN, INPUT_PULLUP);

	// Register the interrupt for the change mode button.
	attachInterrupt(digitalPinToInterrupt(BUTTONPIN), changeMode, RISING);
}

void changeMode()  // ISR for BUTTONPIN
{
	if (mode == OFF)
		mode = SOLID;
	else
		// "increment" mode.  Since we can't do it natively, we have to do casting magic.
		mode = (Modes)(1+(uint8_t)mode);
}

// The loop function is called in an endless loop
void loop()
{
	;
}
