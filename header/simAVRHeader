/* Debug information for SimAVR */
#include <stdio.h>
#ifndef F_CPU
#define F_CPU 8000000
#endif

#include <avr/sleep.h>
#include "/home/papercrane/cs120b_labs/simavr/simavr/sim/avr/avr_mcu_section.h"
AVR_MCU(F_CPU,"atmega1284");
AVR_MCU_VCD_FILE("build/results/lab3_bitManipulation_trace.vcd",1000);

const struct avr_mmcu_vcd_trace_t _mytrace[] _MMCU_ = {
    //{ AVR_MCU_VCD_SYMBOL("PINA0"), .mask = 1 << 0,.what = (void*)&PINA, } ,
    { AVR_MCU_VCD_SYMBOL("PINA"), .what = (void*)&PINA, } ,
    { AVR_MCU_VCD_SYMBOL("PORTC"), .what = (void*)&PORTC, } ,
    //Added individual output pins for completeness
    { AVR_MCU_VCD_SYMBOL("PORTC0"), .mask = 1 << 0, .what = (void*)&PORTC, } ,
    { AVR_MCU_VCD_SYMBOL("PORTC1"), .mask = 1 << 1, .what = (void*)&PORTC, } ,
    { AVR_MCU_VCD_SYMBOL("PORTC2"), .mask = 1 << 2, .what = (void*)&PORTC, } ,
    { AVR_MCU_VCD_SYMBOL("PORTC3"), .mask = 1 << 3, .what = (void*)&PORTC, } ,
    { AVR_MCU_VCD_SYMBOL("PORTC4"), .mask = 1 << 4, .what = (void*)&PORTC, } ,
    { AVR_MCU_VCD_SYMBOL("PORTC5"), .mask = 1 << 5, .what = (void*)&PORTC, } ,
    { AVR_MCU_VCD_SYMBOL("PORTC6"), .mask = 1 << 6, .what = (void*)&PORTC, } ,
};

/* Function to output through UART */
static int uart_putchar(char c, FILE *stream) {
    if (c == '\n') {
        uart_putchar('\r',stream);
    }
    loop_until_bit_is_set(UCSR0A,UDRE0);
    UDR0 = c;
    return 0;
}

/* Setup filestream for debugging */
FILE mystdout = FDEV_SETUP_STREAM(uart_putchar,NULL,_FDEV_SETUP_WRITE);
/* End SimAVR section */
