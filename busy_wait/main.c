/**
 * @file main.c
 * @author Lorang Strand
 * @date 2025-10-23
 * @brief Busy wait example using USART3 and LED interface on AVR128DB48 microcontroller
 */

 #include "AC_interface.h"
 #include "led_interface.h"
 #include <util/delay.h>

void disableUnusedPins(){


    PORTB.PINCONFIG = PORT_ISC_INPUT_DISABLE_gc | PORT_PULLUPEN_bm;
    PORTB.PINCTRLUPD = 0xFF; // Disable all pins on PORTB
    
    PORTC.PINCONFIG = PORT_ISC_INPUT_DISABLE_gc | PORT_PULLUPEN_bm;
    PORTC.PINCTRLUPD = 0xFF;
}

int main(){
    disableUnusedPins();
    LED_Init();
    AC_Init();
    VREF_Init();
    while(1){
        while(AC_AboveThreshold()){}
        LED_On();
        while(!AC_AboveThreshold()){}
        LED_Off();
    }
    return 0;
}
