# LED Night Light - AVR128DB48 Implementation

A low-power ambient light sensing night light system implemented on the AVR128DB48 microcontroller using different programming paradigms to demonstrate power consumption trade-offs and design approaches.

## Overview

This project implements an automatic night light that:
- **Turns ON** when ambient light is below threshold (dark environment)
- **Turns OFF** when ambient light is above threshold (bright environment)
- Uses an analog comparator (AC0) connected to an ambient light sensor on pin PD2
- Controls an LED on pin PA2
- Demonstrates four different implementation approaches with varying power consumption

## Hardware Configuration

- **Microcontroller**: AVR128DB48
- **LED**: Connected to PA3 (Port A, Pin 2)
- **Light Sensor**: Ambient light sensor connected to PD2 (AIN2 input to AC0)
- **Reference**: Internal 1.024V VREF with 100mV threshold via DACREF
- **Power Supply**: 3.3V or 5V depending on configuration

## Implementation Approaches

### 1. Busy Wait (`busy_wait/`)
**Approach**: Continuous polling in active mode
- CPU constantly checks analog comparator status
- No sleep modes used
- **Power Consumption**: Highest (~mA range)
- **Responsiveness**: Immediate
- **Use Case**: When power consumption is not a concern

### 2. Polling (`polling/`)
**Approach**: Periodic wake-up every 10ms using Timer/Counter A (TCA)
- CPU sleeps in standby mode between checks
- Timer interrupt wakes CPU every 10ms to check AC status
- **Power Consumption**: Medium (~hundreds of µA)
- **Responsiveness**: Up to 10ms delay
- **Use Case**: Balance between power and responsiveness

### 3. Interrupt Driven (`interrupt/`)
**Approach**: AC0 interrupt on threshold crossing
- CPU sleeps in standby mode
- Analog comparator interrupt wakes CPU only when light level changes
- **Power Consumption**: Low (~tens of µA)
- **Responsiveness**: Immediate on threshold crossing
- **Use Case**: Optimal balance for most applications

### 4. Core Independent (`core_independent/`)
**Approach**: Event System routing without CPU intervention
- AC0 output routed directly to LED via Event System (EVSYS)
- CPU can remain in deep sleep indefinitely
- **Power Consumption**: Lowest (~µA range)
- **Responsiveness**: Hardware-level immediate response
- **Use Case**: Ultra-low power applications

## Key Features

### Analog Comparator Configuration
- **Positive Input**: PD2 (AIN2) - Ambient light sensor
- **Negative Input**: Internal DACREF (100mV threshold)
- **Reference Voltage**: 1.024V internal VREF
- **Hysteresis**: Optional small hysteresis to prevent noise-induced switching

### Power Management
- Unused peripherals disabled
- All unused pins configured to prevent floating inputs
- Appropriate sleep modes for each implementation
- Clock prescaling where applicable

### Sleep Modes Used
- **Standby Mode**: Used in polling and interrupt approaches
- **Power-down Mode**: Potential for core-independent approach
- **Run-in-Standby**: AC0 and VREF configured to operate during sleep

## Power Consumption Comparison

| Implementation | Estimated Current | Wake Frequency |
|----------------|-------------------|----------------|
| Busy Wait      | ~1-2 mA          | N/A (always active) |
| Polling        | ~200-800 µA      | Every 10ms |
| Interrupt      | ~50-200 µA       | On light change only |
| Core Independent | ~10-50 µA      | Never (hardware only) |

*Note: Actual values depend on supply voltage, temperature, and specific hardware configuration*

## Building and Running

Each implementation is in its own directory with individual build systems:

```bash
# Navigate to desired implementation
cd busy_wait/    # or polling/, interrupt/, core_independent/

# Build (assuming make/cmake setup)
make

# Program the device
make program
```

## File Structure

```
├── busy_wait/           # Continuous polling implementation
├── polling/             # Timer-based periodic checking
├── interrupt/           # AC interrupt-driven approach  
├── core_independent/    # Event system hardware routing
└── README.md            # This file
```

## Key Learning Outcomes

1. **Power Management**: Understanding trade-offs between responsiveness and power consumption
2. **Sleep Modes**: Practical application of different AVR sleep modes
3. **Peripheral Integration**: Using analog comparator, event system, and timers
4. **Interrupt Handling**: Efficient interrupt-driven programming
5. **Hardware Abstraction**: Clean interface design for reusable code

## Circuit Considerations

- **Light Sensor**: Should provide 0-3.3V output proportional to ambient light
- **Threshold Setting**: 100mV threshold suitable for most ambient light sensors
- **LED Current**: Ensure appropriate current limiting for LED on PA2
- **Decoupling**: Proper power supply decoupling for stable analog measurements

## Future Enhancements
- Multiple light level detection zones
- Integration with RTC for time-based control
- Tuning of main clock frequency for "Sprint to Sleep" mode
