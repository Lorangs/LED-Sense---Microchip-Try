/**
 * @file main.c
 * @author lorang
 * @date 2025-10-23
 * @brief Main function
 */

 #include <avr/io.h>
 #include <util/delay.h>

 
int main(){
    // Set the led as an output
    PORTB.DIRSET = PIN3_bm;
    while(1){
        // Toggle the led
        PORTB.OUTTGL = PIN3_bm;
        _delay_ms(500);
    }
    
    return 0;
}
