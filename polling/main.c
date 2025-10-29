/**
 * @file main.c
 * @author lorang
 * @date 2025-10-29
 * @brief Main function
 */


#define INTERRUPT_PERIODE_ms 10000  // in ms

#include "led_interface.h"
#include "AC_interface.h"
#include "usart.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

//Timer/Counter A0 Initialization
void TCA_Init(const int period_ms)
{
    // Periode = (F_CPU / prescaler) * period_ms / 1000 
    TCA0.SINGLE.PER = (F_CPU / 2000) * period_ms; // Set period for overflow

    
    TCA0.SINGLE.CTRLA = TCA_SINGLE_ENABLE_bm        |   // Enable TCA0
                        TCA_SINGLE_CLKSEL_DIV2_gc   |   // prescaler set to 2
                        TCA_SINGLE_RUNSTDBY_bm;         // Run in standby mode
    
    TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;            // Enable overflow interrupt
}


ISR(TCA0_OVF_vect)
{
    TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm; // Clear overflow flag

    // Check if AC output is above threshold
    if(AC_AboveThreshold())
    {
        LED_Off();
        USART3_SendString("AC above threshold!\n");
    }
    else
    {
        LED_On();
        USART3_SendString("AC below threshold!\n");
    }
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
    USART3_Init();
    TCA_Init(INTERRUPT_PERIODE_ms);


    // enable global interrupts
    sei();

    USART3_SendString("Hello World!\n");

    // setup sleep controller register
    SLPCTRL.CTRLA = SLPCTRL_SMODE_STDBY_gc; // Set sleep mode to standby

    
    while(1) sleep_cpu();    // Put the device to sleep. Interrupts will wake it up.
    return 0;
}
