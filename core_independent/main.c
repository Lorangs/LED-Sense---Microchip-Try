/**
* @file main.c
* @author lorang
* @date 2025-10-31
* @brief Event-driven main loop for AVR128DB48 microcontroller.
*/

#include"led_interface.h"
#include "AC_interface.h"
#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>


/**
* Set up core independent peripherals and enter sleep mode.
*/
void CIP_Init(void)
{

    EVSYS_CHANNEL1 = 0;
    EVSYS_CHANNEL2 = 0;
    EVSYS_CHANNEL3 = 0;
    EVSYS_CHANNEL4 = 0;
    EVSYS_CHANNEL5 = 0;

    EVSYS_CHANNEL0 = EVSYS_CHANNEL0_AC0_OUT_gc; // Route AC0 output to Event System Channel 0
    EVSYS.USEREVSYSEVOUTA = EVSYS_USER_CHANNEL0_gc; // Route Event System Channel 0 to LED peripheral
}

void disable_Inputs(void)
{
    PORTA.PINCONFIG = PORT_ISC_INPUT_DISABLE_gc | PORT_PULLUPEN_bm;
    PORTA.PINCTRLUPD = 0xFF; // Disable all pins on PORTA

    PORTB.PINCONFIG = PORT_ISC_INPUT_DISABLE_gc | PORT_PULLUPEN_bm;
    PORTB.PINCTRLUPD = 0xFF; // Disable all pins on PORTB
    
    PORTC.PINCONFIG = PORT_ISC_INPUT_DISABLE_gc | PORT_PULLUPEN_bm;
    PORTC.PINCTRLUPD = 0xFF;

    PORTD.PINCONFIG = PORT_ISC_INPUT_DISABLE_gc | PORT_PULLUPEN_bm;
    PORTD.PINCTRLUPD = 0xFF;

    AC1.CTRLA = 0; // Disable AC1 to save power
    AC2.CTRLA = 0; // Disable AC2 to save power

    TCA0.SINGLE.CTRLA = 0; // Disable TCA to save power
    TCB0.CTRLA = 0;      // Disable TCB to save power
    TCB1.CTRLA = 0;      // Disable TCB1 to save power
    TCB2.CTRLA = 0;      // Disable TCB2 to save power
    TCB3.CTRLA = 0;      // Disable TCB3 to save power
    TCD0.CTRLA = 0;      // Disable TCD to save power

    ADC0.CTRLA = 0;    // Disable ADC to save power

    DAC0.CTRLA = 0;   // Disable DAC to save power
    TWI0.CTRLA = 0;  // Disable TWI to save power
    SPI0.CTRLA = 0;  // Disable SPI to save power   
    CCL.CTRLA = 0; // Disable Configurable Custom Logic to save power
    USART0.CTRLA = 0; // Disable USART0 to save power
    USART1.CTRLA = 0; // Disable USART1 to save power
    USART2.CTRLA = 0; // Disable USART2 to save power
    USART3.CTRLA = 0; // Disable USART3 to save power
}

int main()
{
    disable_Inputs();
    VREF_Init();
    AC_Init();
    LED_Init();
    CIP_Init();

    set_sleep_mode(SLEEP_MODE_STANDBY);
    sleep_enable();

    cli();                  // Disable global interrupts

    while(1) sleep_cpu();   // Enter sleep mode. Peripherals handle the rest with events.
    return 0;
}
