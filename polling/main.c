/**
 * @file main.c
 * @author lorang
 * @date 2025-10-29
 * @brief Main function
 */


#define INTERRUPT_PERIODE_ms    1000           // in ms
#define CLK_PRESCALER           1024            // Timer prescaler

#include "led_interface.h"
#include "AC_interface.h"
#include "usart.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>


/**
* Timer Counter A0 Initialization for periodic interrupts.
* parameters:
*   period_ms: Period of the timer in milliseconds.
*   prescaler: Clock prescaler value (1, 2, 4, 8 ... 1024)
*/
void TCA_Init(const int period_ms, const int prescaler)
{
    static int prescaler_;
    switch (prescaler)
    {
        case 1:
            prescaler_ = TCA_SINGLE_CLKSEL_DIV1_gc;
            break;
        case 2:
            prescaler_ = TCA_SINGLE_CLKSEL_DIV2_gc;
            break;
        case 4:
            prescaler_ = TCA_SINGLE_CLKSEL_DIV4_gc;
            break;
        case 8:
            prescaler_ = TCA_SINGLE_CLKSEL_DIV8_gc;
            break;
        case 16:
            prescaler_ = TCA_SINGLE_CLKSEL_DIV16_gc;
            break;
        case 64:
            prescaler_ = TCA_SINGLE_CLKSEL_DIV64_gc;
            break;
        case 256:
            prescaler_ = TCA_SINGLE_CLKSEL_DIV256_gc;
            break;
        case 1024:
            prescaler_ = TCA_SINGLE_CLKSEL_DIV1024_gc;
            break;
        default:
            prescaler_ = TCA_SINGLE_CLKSEL_DIV1_gc; // Default to no prescaling
            USART3_SendString("Warning: Invalid prescaler, defaulting to 1.\n");
            break;
    }

    // Calculate period in timer ticks
    uint32_t period_ticks = (uint32_t)((F_CPU / prescaler) * (period_ms / 1000UL) - 1);

    if (period_ticks > 0xFFFF) {
        period_ticks = 0xFFFF; // Cap to maximum value for 16-bit timer
        USART3_SendString("Warning: Period too long, capping to max value.\n");
    }

    TCA0.SINGLE.PER = (uint16_t)period_ticks;

    TCA0.SINGLE.CTRLA = TCA_SINGLE_ENABLE_bm        |  // Enable TCA0
                        prescaler_                  |  // Set prescaler
                        TCA_SINGLE_RUNSTDBY_bm;        // Run in standby mode
    
    TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;            // Enable overflow interrupt
}


ISR(TCA0_OVF_vect)
{
    TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm; // Clear overflow flag

    // Check if AC output is above threshold. Turn off LED if true, else turn on.
    AC_AboveThreshold() ? LED_Off() : LED_On();
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

    TCA_Init(INTERRUPT_PERIODE_ms, CLK_PRESCALER);

    SLPCTRL.CTRLA = SLPCTRL_SMODE_STDBY_gc; // Set sleep mode to standby

    sei();     // enable global interrupts
    
    while(1) sleep_cpu();    // Put the device to sleep. Interrupts will wake it up.
    return 0;
}
