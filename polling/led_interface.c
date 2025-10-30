#include "led_interface.h"

/**
* @file led_interface.c
* @author L. Strand
* @date 2025-10-23
* @brief LED interface implementation for AVR128DB48 microcontroller
*/

/**
* Initialize the LED on PA2 as output
*/
void LED_Init(void)
{
    PORTA.DIRSET = PIN2_bm; // Set PA2 as output
    PORTA.OUTSET = PIN2_bm; // Turn off LED initially
}

/**
* Turn on the LED
*/
void LED_On(void)
{
    PORTA.OUTCLR = PIN2_bm; // LED is active low, set PA2 low to turn on LED
}

/**
* Turn off the LED
*/
void LED_Off(void)
{
    PORTA.OUTSET = PIN2_bm; // LED is active low, set PA2 high to turn off LED
}

/**
* Toggle the LED state
*/
void LED_Toggle(void)
{
    PORTA.OUTTGL = PIN2_bm; // Toggle PA2 state
}

/**
* Get the current state of the LED
*/
bool LED_GetState(void)
{
    return (PORTA.OUT & PIN2_bm) ? false : true; // Return 1 if LED is on, 0 if off (active low)
}