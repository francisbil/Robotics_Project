#ifndef UART_H
#define UART_H

#include <avr/io.h>
#define F_CPU 8000000UL
#include <avr/interrupt.h>

class Uart
{
public:
    Uart();
    void transmission(uint8_t donnee);
    unsigned char reception(void);
};

#endif