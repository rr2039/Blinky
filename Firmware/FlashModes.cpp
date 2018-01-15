/*
 * FlashModes.cpp
 *
 *  Created on: Jan 1, 2018
 *      Author: Logan Power
 */
#include "FlashModes.hpp"

// potValue and ledValues[] from main file
extern uint8_t ledValues[4];
extern uint16_t counter;

//extern uint16_t potValue; /* TODO: Make potentiometer actually relevant */

// Function for solid light mode.
void solid()
{
	for(uint8_t i = 0; i < 4; i++)
	{
		ledValues[i] = 255;
	}
}

// Function for flashing light mode.
void flashing()
{
	static bool state; /* 0 for off, 1 for on */

	// Counter timing's a bit arbitrary but 2048 seems to be a decently fast flash.
	if ((counter % 2048) == 0)
		state = !state;
	for(uint8_t i = 0; i<4; i++)
	{
		ledValues[i] = ((uint8_t)state) ? 255 : 0 ;
	}

}

// Function for looping light mode
void looping()
{
	static byte bits; /* Just a byte.  Initially set to 0b00000001 by the first part of that if statement down there.*/
	uint16_t interval = 2048; /* Counter timing can vary but usually 2048 is good enough value */

	if (counter % interval == 0) /* only calculate this stuff on the interval */
	{
		if (bits == 0) /* Never let bits be 0.  Always have one bit to shift through. */
			bits = 1;

		/*
		 * Is this switch/case structure the best way to solve this problem?  No.  But for some reason comparisons to
		 * powers of two like in the old versions didn't work, so here we are.
		 */
		switch(bits)
		{
		case 1:
		case 16:
			ledValues[0] = 255;
			ledValues[1] = 0;
			ledValues[2] = 0;
			ledValues[3] = 0;
			break;
		case 2:
		case 32:
			ledValues[0] = 0;
			ledValues[1] = 255;
			ledValues[2] = 0;
			ledValues[3] = 0;
			break;
		case 4:
		case 64:
			ledValues[0] = 0;
			ledValues[1] = 0;
			ledValues[2] = 255;
			ledValues[3] = 0;
			break;
		case 8:
		case 128:
			ledValues[0] = 0;
			ledValues[1] = 0;
			ledValues[2] = 0;
			ledValues[3] = 255;
			break;
		default:
			ledValues[0] = 0;
			ledValues[1] = 255;
			ledValues[2] = 255;
			ledValues[3] = 0;
			break;
		}
		bits <<= 1; /* This is where the magic happens and the bit gets shifted through. */

	}


}

// Function for pulsing light mode
void pulsing()
{
	; //TODO: Fix this function too.
}

// Function for off light mode.  I know, this probably doesn't need to exist, but oh well.
void off()
{
	for(uint8_t i = 0; i<4; i++)
		{
			ledValues[i] = 0;
		}
}
