/*
 * FlashModes.cpp
 *
 *  Created on: Jan 1, 2018
 *      Author: Logan Power
 */
#include "FlashModes.hpp"

// potValue and ledValues[] from main file
extern uint8_t ledValues[4];
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
	uint16_t interval = 2048; /* Sets interval (in ms) to change states */
	// TODO: Make it so the potentiometer can change the interval.
	if(millis() % interval == 0)
	{
		state = !state;
		for (uint8_t i = 0; i < 4; i++)
		{
			ledValues[i] = (255 * state);
		}
	}
}

// Function for looping light mode
void looping()
{
	static byte bits; /* Just a byte.  Initially set to 0b00000001 */
	uint16_t interval = 512;
	// TODO: Make it so the potentiometer can change the interval.
	// Make sure at least one bit is always active.
		if(bits == 0)
			bits = 1;
	// Only run when the interval elapses.
	if(millis() % interval == 0)
	{
		for(uint8_t i = 0; i < 4; i++)
		{
			// Turn on the LED set that corresponds to the right power of two.
			// I am definitely not multiplying by a boolean.  Definitely not.
			ledValues[i] = ((bits == pow(2, i)) * 255);
		}
		// Now change which power of two will be active next time.
		bits <<= 1;
	}
}

// Function for pulsing light mode
void pulsing()
{
	static uint8_t value; /* Since value is uniform throughout all lights, just work with one variable. */
	uint8_t increment; /* How much to change the value by. */
	bool reverse; /* False: Negative.  True: Positive. */
	increment = 1; /* TODO: Make this depend on the potentiometer.*/

	if(value == 255 || value == 0)
		reverse = !reverse;
	if(reverse)
		value += increment;
	else
		value -= increment;
	for(uint8_t i = 0; i < 4; i++)
	{
		ledValues[i] = value;
	}
}

// Function for off light mode.  I know, this probably doesn't need to exist, but oh well.
void off()
{
	for(int i = 0; i<4; i++)
		{
			ledValues[i] = 0;
		}
}
