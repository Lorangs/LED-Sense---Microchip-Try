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

 
#define INTERRUPT_PERIODE_ms    10       
#define TIMER_PRESCALER         TCA_SINGLE_CLKSEL_DIV1_gc       
#define TIMER_PRESCALER_VALUE   1
#define TIMER_PERIODE           40000

/**
* Timer Counter A0 Initialization for periodic interrupts.
*/
void TCA_Init(void)
{

    TCA0.SINGLE.PER = TIMER_PERIODE - 1; // Set period for overflow interrupt

    TCA0.SINGLE.CTRLA = TCA_SINGLE_ENABLE_bm        |  // Enable TCA0
                        TIMER_PRESCALER             |  // Set prescaler
                        TCA_SINGLE_RUNSTDBY_bm;        // Run in standby mode
    
    TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;           // Enable overflow interrupt
}


ISR(TCA0_OVF_vect)
{
    TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm; // Clear interrupt flag
    
    if (LED_GetState())
    {
        if(AC_AboveThreshold())
        {
            LED_Off();
        }
    } 
    else 
    {
        if(!AC_AboveThreshold())
        {
            LED_On();
        }
    }
}

/**
* Disable all inputs on the microcontroller to avoid floating
* Pin used will be reconfigured later.
* This function must be called at the start of main before any peripheral initialization.
*/
void disableInputs()
{
    PORTA.PINCONFIG = PORT_ISC_INPUT_DISABLE_gc | PORT_PULLUPEN_bm; // Disable input buffer and enable pull-up resistors
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
    VREF_Init();
    AC_Init();
    TCA_Init();
    LED_Init();

    set_sleep_mode(SLEEP_MODE_STANDBY);
    sleep_enable(); 
    sei();          // enable global interrupts
    
    while(1) sleep_cpu(); // Enter sleep mode
    return 0;
}
