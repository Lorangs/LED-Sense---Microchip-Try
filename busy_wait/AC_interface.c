#include "AC_interface.h"
#include <avr/io.h>

/**
* Initialize the Analog Comparator  for Ambient Light Sensor
* Positive input on PA0, Negative input on VREF
*/
void AC_Init(void)
{
    VREF_Init();

    // Set Port D, pin 2 as an input (PD2)
    PORTD.DIRCLR    = PIN2_bm; 

    // Disable digital input bufffer and pull-up resistor for pin PD2
    PORTD.PIN2CTRL  = PORT_ISC_INPUT_DISABLE_gc;
    
    AC0.MUXCTRL     = AC_MUXPOS_AINP2_gc    |   // Positive input on PA0 (AINP2)
                      AC_MUXNEG_DACREF_gc;      // Negative input on VREF

    AC0.CTRLA       = AC_ENABLE_bm          |   // Enable AC0
                      AC_HYSMODE_SMALL_gc   |   // Set hysteresis to small
                      AC_POWER_PROFILE2_gc  |   // Set power profile to Profile 2 (lowest power consumption)
                      AC_RUNSTDBY_bm;           // Run in standby mode

    // Set Analog Comparator Refenrence to trigger when voltage exceeds 100mV 
    // According to equation from section 32.3.2.2 in datasheet
    // V_DACREF = (DACREF / 256) * V_REF
    // Given a desired V_DACREF of 0.1V and V_REF of 1.024V:
    // DACREF = (V_DACREF / V_REF) * 256 = (0.1 / 1.024) * 256 ≈ 0d26 = 0x20
    AC0.DACREF      = 0x20;  
}

void VREF_Init(void)
{
    // Configure VREF to 1.024V
    VREF.ACREF = VREF_REFSEL_1V024_gc;
}

int8_t AC_AboveThreshold(void)
{
    // Return the output state of the Analog Comparator
    return AC0.STATUS & AC_CMPSTATE_bm;
}
