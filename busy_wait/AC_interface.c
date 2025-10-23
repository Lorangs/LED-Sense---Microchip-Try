#include "AC_interface.h"

/**
* Initialize the Analog Comparator  for Ambient Light Sensor
* Positive input on PA0, Negative input on VREF
*/
void AC_Init(void)
{
    // Set Port D, pin 2 as an input (PD2)
    PORTD.DIRCLR = PIN2_bm; 
    // Disable digital input bufffer and pull-up resistor for pin PD2
    PORTD.PIN2CTRL = PORT_ISC_INPUT_DISABLE_gc;
    
}

void VREF_Init(void)
{
    // Configure VREF to 1.024V
    VREF.ACREF = VREF_REFSEL_1V024_gc;
}