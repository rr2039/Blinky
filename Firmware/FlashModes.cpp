/*
 * FlashModes.cpp
 *
 *  Created on: Jan 1, 2018
 *      Author: Logan Power
 */
#include "FlashModes.h"

// potValue and ledValues[] from main file
extern uint8_t ledValues[];
extern uint16_t potValue;

// Function for solid light mode.  Inline it to save a cycle, because why not?
inline void solid()
{
	for(uint8_t i = 0; i < 4; i++)
	{
		ledValues[i] = 255;
	}
}

// Function for flashing light mode.  I'll suggest the compiler inline it.
inline void flashing()
{
	static bool state; /* 0 for off, 1 for on */
	uint16_t interval = 512; /* Sets interval (in ms) to change states */
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
	uint16_t interval = 64;
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
	static register uint8_t value; /* Since value is uniform throughout all lights, just work with one variable. */
	uint8_t increment; /* How much to change the value by. */
	bool reverse; /* False: Negative.  True: Positive. */

	increment = 1; /* TODO: Make this depend on the potentiometer.*/

	value += (increment)
}
