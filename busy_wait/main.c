/**
 * @file main.c
 * @author Lorang Strand
 * @date 2025-10-23
 * @brief Busy wait example using USART3 and LED interface on AVR128DB48 microcontroller
 */

 #include "usart.h"
 #include "led_interface.h"
 #include <util/delay.h>

int main(){
    USART3_Init();
    LED_Init();

    USART3_SendString("Hello, World!\r\n");
    while(1){
        LED_Toggle();
        LED_GetState() ? USART3_SendString("LED is ON\r\n") : USART3_SendString("LED is OFF\r\n");
        _delay_ms(1000);
    }
    return 0;
}
