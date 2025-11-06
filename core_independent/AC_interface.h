/**
* @file AC_interface.h
* @author L. Strand
* @date 2025-10-23
* @brief AC interface header for AVR128DB48 microcontroller for the Ambient Light Sensor.
* 
*/

#ifndef AC_INTERFACE_H
#define AC_INTERFACE_H

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>



void AC_Init(void);
void VREF_Init(void);
bool AC_AboveThreshold(void);


#endif // AC_INTERFACE_H