#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H

#include <avr/io.h>
#include <stdbool.h>

void LED_Init(void);
void LED_On(void);
void LED_Off(void);
void LED_Toggle(void);
bool LED_GetState(void);

#endif  // LED_INTERFACE_H