/*	Author: Andrew Bazua
 *  Partner(s) Name:
 *	Lab Section:023
 *	Assignment: Lab #4  Exercise #3
 *	Exercise Description: [A household has a digital combination deadbolt lock 
        system on the doorway. The system has buttons on a keypad. Button 'X' 
        connects to PA0, 'Y' to PA1, and '#' to PA2. Pressing and releasing 
        '#', then pressing 'Y', should unlock the door by setting PB0 to 1. 
        Any other sequence fails to unlock. Pressing a button from inside the 
        house (PA7) locks the door (PB0=0). For debugging purposes, give each 
        state a number, and always write the current state to PORTC (consider 
        using the enum state variable). Also, be sure to check that only one 
        button is pressed at a time.]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

typedef enum States {init, wait, pressX, pressY, press#, pressIn} States;

int securityDoor(int);

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;

    States state = init;

    /* Insert your solution below */
    while (1) {
        state = counter(state);
    }
    return 1;
}

int securityDoor(int state) {
    static unsigned char tmpB;
    static unsigned char prevState;

    unsigned char tmpA = PINA;


    switch (state) {        //TRANSITIONS
        case init:
            state = wait;
            break;

        case wait:
            if (tmpA == 0x01) { state = pressX; }
            else if (tmpA == 0x02) { state = pressY; }
            else if (tmpA == 0x03) { state = press#; }
            else if (tmpA == 0x07) { state = pressIn; }
            else { state = wait; }
            break;
        
        case pressX;
            state = tmpA ? pressX: wait;
            break;
    }

    switch (state) {        //ACTIONS
        
    }

    PORTC = tmpC;
    return state;
}
