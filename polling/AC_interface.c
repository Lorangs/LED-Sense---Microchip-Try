#include "AC_interface.h"
#include <avr/io.h>

/**
* Initialize the Analog Comparator  for Ambient Light Sensor
* Positive input on PA0, Negative input on VREF
*/
void AC_Init(void)
{
    // Set Port D, pin 2 as an input (PD2)
    PORTD.DIRCLR    = PIN2_bm; 

    // Disable digital input bufffer and pull-up resistor for pin PD2
    PORTD.PIN2CTRL  = PORT_ISC_INPUT_DISABLE_gc;
    
    AC0.MUXCTRL     = AC_MUXPOS_AINP0_gc    |   // Positive input on PD2
                      AC_MUXNEG_DACREF_gc;      // Negative input on VREF

    // Set Analog Comparator Refenrence to trigger when voltage exceeds 100mV 
    // According to equation from section 32.3.2.2 in datasheet
    // V_DACREF = (DACREF / 256) * V_REF
    // Given a desired V_DACREF of 0.1V and V_REF of 1.024V:
    // DACREF = (V_DACREF / V_REF) * 256 = (0.1 / 1.024) * 256 ≈ 0d25 = 0x19
    AC0.DACREF      = 0x19; 

    AC0.CTRLA       = AC_ENABLE_bm                  |   // Enable AC0
                      AC_INTMODE_NORMAL_POSEDGE_gc  |   // Interrupt on positive edge
                      AC_POWER_PROFILE0_gc          |   // Set power profile to Profile 2 (lowest power consumption)
                      AC_RUNSTDBY_bm;                   // Run in standby mode
}   

void VREF_Init(void)
{
    // Configure VREF to 1.024V
    VREF.ACREF      = VREF_REFSEL_1V024_gc | 
                      VREF_ALWAYSON_bm;
                      
    _delay_us(25); // Wait for voltage reference to stabilize
}


bool AC_AboveThreshold(void)
{
    // Return the output state of the Analog Comparator
    return (AC0.STATUS & AC_CMPSTATE_bm) ? true : false;   
}
