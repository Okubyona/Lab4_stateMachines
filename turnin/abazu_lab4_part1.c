/*	Author: Andrew Bazua
 *  Partner(s) Name:
 *	Lab Section:023
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: [PB0 and PB1 each connect to an LED, and PB0's LED is 
        initially on. Pressing a button connected to PA0 turns off PB0's LED and 
        turns on PB1's LED, staying that way after button release. Pressing the 
        button again turns off PB1's LED and turns on PB0's LED.]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

typedef enum States {start, waitUnLit, unLit, waitLit, lit} States;

int lightTick(int);

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;

    States state = start;

    /* Insert your solution below */
    while (1) {
        state = lightTick(state);
    }
    return 1;
}

int lightTick(int state) {
    static unsigned char b;

    unsigned char A0 = PINA & 0x01;

    switch (state) {        //TRANSITIONS
        case start:
            state = waitUnLit;
            break;

        case waitUnLit:
            state = A0? unLit: waitUnLit;
            break;

        case unLit:
            state = A0? unLit: waitLit;
            break;

        case waitLit:
            state = A0? lit: waitLit;
            break;
        
        case lit:
            state = A0? lit: waitUnLit;
            break;

        default:
            state = start;
            break;
    }

    switch (state) {        //ACTIONS
        case start: break;

        case waitUnLit: break;

        case unLit:
            b = 0x01;            
            break;
    
        case waitLit: break;

        case lit:
            b = 0x02;
            break;
    }   
    
    PORTB = b;
    return state;
}
