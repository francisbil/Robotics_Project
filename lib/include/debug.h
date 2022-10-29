#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#define F_CPU 8000000UL
#include "can.h"

#ifdef DEBUG
    #define DEBUG_PRINT(x) debug(x)
    #define DEBUG_PRINTV() debug_v()
    #define DEBUG_PRINTD() debug_d()
    #define DEBUG_PRINTP() debug_p()
#else
    #define DEBUG_PRINT(x) do {} while (0)
    #define DEBUG_PRINTV() do {} while (0)
    #define DEBUG_PRINTD() do {} while (0)
    #define DEBUG_PRINTP() do {} while (0)
#endif

void debug(uint16_t donnee);
void debug_v();
void debug_d();
void debug_p();

#endif