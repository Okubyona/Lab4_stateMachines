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

typedef enum States {init, wait, pressX, buttonY, pressPound, lock, unlock} States;

int securityDoor(int);

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;

    States state = init;

    /* Insert your solution below */
    while (1) {
        state = securityDoor(state);
    }
    return 1;
}

int securityDoor(int state) {
    static unsigned char tmpC;
    static unsigned char tmpB;
    static unsigned char prevState;

    unsigned char tmpA = PINA;


    switch (state) {        //TRANSITIONS
        case init:
            state = wait;
            break;

        case wait:
            if (tmpA == 0x01) { state = pressX; }
            else if (tmpA  == 0x02) { state = buttonY; }
            else if (tmpA == 0x04) { state = pressPound; }
            else if (tmpA == 0x80) { state = lock; }
            else { state = wait; }
            break;
        
        case pressX:
            if (tmpA == 0x01) { state = pressX; }
            else { state = wait; }
            break;

	    case buttonY: 
		    if (prevState == pressPound) { state = unlock; }
            else if (state == 0x02) { state = buttonY; }
            else { state = wait; }
            break;

        case pressPound:
            if (tmpA == 0x04) { state = pressPound; }
            else { state = wait; }
            break;

        case lock: 
            if (tmpA == 0x80) { state = lock; }
            else { state = wait; }
            break;

        case unlock:
            if (tmpA) { state = unlock; }
            else { state = wait; }
            break;
    }

    switch (state) {        //ACTIONS
        case init: 
            tmpB = 0x00;
            prevState = init;
            tmpC = 0x00;            
            break;

        case wait: 
            tmpC = wait;
            break;

        case pressX: 
            tmpC = pressX;        
            break;    

        case buttonY: 
            tmpC = buttonY;
            break;

        case pressPound:
            tmpC = pressPound;
            prevState = pressPound;
            break;
        
        case lock:
            tmpB = 0x00;
            tmpC = lock;
            break;

        case unlock:
            tmpB = 0x01;
            tmpC = unlock;
            break;
    }

    PORTB = tmpB;
    PORTC = tmpC;
    return state;
}
