/**
 * @file main.c
 * @author lorang
 * @date 2025-10-29
 * @brief Main function
 */


#include "led_interface.h"
#include "AC_interface.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>



/**
 * Timer interrupt service routine
 * This ISR is triggered on AC0, and clears the interrupt flag.
 */
ISR(AC0_AC_vect)
{
    AC0.STATUS = AC_CMP_bm; // Clear interrupt flag by writing 1 to it
}

/**
* Disable all inputs on the microcontroller to avoid floating
* Pin used will be reconfigured later.
* This function must be called at the start of main before any peripheral initialization.
*/
void disableInputs()
{
    PORTA.PINCONFIG = PORT_ISC_INPUT_DISABLE_gc | PORT_PULLUPEN_bm;
    PORTA.PINCTRLUPD = 0xFF; // Disable all pins on PORTA

    PORTB.PINCONFIG = PORT_ISC_INPUT_DISABLE_gc | PORT_PULLUPEN_bm;
    PORTB.PINCTRLUPD = 0xFF; // Disable all pins on PORTB
    
    PORTC.PINCONFIG = PORT_ISC_INPUT_DISABLE_gc | PORT_PULLUPEN_bm;
    PORTC.PINCTRLUPD = 0xFF;

    PORTD.PINCONFIG = PORT_ISC_INPUT_DISABLE_gc | PORT_PULLUPEN_bm;
    PORTD.PINCTRLUPD = 0xFF;
}


int main(){
    disableInputs();
    LED_Init();
    VREF_Init();
    AC_Init();    

    set_sleep_mode(SLEEP_MODE_STANDBY);
    sleep_enable();
    sei();     // enable global interrupts
    
    while(1) 
    {
        // If AC is above threshold, turn off LED, else turn it on
        AC_AboveThreshold() ? LED_Off() : LED_On();
        
        sleep_cpu();    // Put the device to sleep. Interrupts will wake it up.
    }

    return 0;
}
