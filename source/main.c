/*	Author: Andrew Bazua
 *  Partner(s) Name:
 *	Lab Section:024
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

typedef enum States {start, waitPress, buttonPress, waitA0} States;

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
    static unsigned char b = 0x01;

    unsigned char A0 = PINA & 0x01;

    switch (state) {        //TRANSITIONS
        case start:
            state = waitPress;
            break;

        case waitPress:
            state = A0 ? buttonPress : waitPress;
            break;

        case buttonPress:
            state = waitA0;
            break;

        case waitA0:
            state = A0 ? waitA0 : waitPress;
            break;
        default:
            state = start;
            break;
    }

    switch (state) {        //ACTIONS
        case start:
            b = 0x01;
        break;

        case waitPress: break;

        case buttonPress:
            b = (!b) & 0x03;
            break;
        case waitA0: break;
    }

    PORTB = b;
    return state;
}
