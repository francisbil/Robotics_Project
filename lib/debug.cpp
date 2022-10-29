#include "debug.h"

void debug(uint16_t donnee)
{
    char buffer[20];
    itoa(donnee, buffer, 10);

    uint8_t i = 0;
    while (buffer[i] != 0)
    {
        while (!(UCSR0A & (1 << UDRE0)))
            ;

        UDR0 = buffer[i];
        i++;
    }
    while (!(UCSR0A & (1 << UDRE0)))
            ;

        UDR0 = '\n';
}

void debug_v()
{
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = 'V';
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = '(';
    if (PIND & (1 << PD4))
    {
        while (!(UCSR0A & (1 << UDRE0)))
        ;
        UDR0 = '-';
    }
    char buffer[5];
    uint8_t wheel = OCR2B;
    uint16_t percentage;
    if (wheel == 1)
    {
        percentage = 100;
    }
    else if (wheel == 254)
    {
        percentage = 0;
    }
    else
    {
        percentage = 100 - ((wheel + 1) * 100) / 256;
    }
    itoa(percentage, buffer, 10);
    uint8_t i = 0;
    while (buffer[i] != 0)
    {
        while (!(UCSR0A & (1 << UDRE0)))
            ;
        UDR0 = buffer[i];
        i++;
    }
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = ',';
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = ' ';
    if (PIND & (1 << PD4))
    {
        while (!(UCSR0A & (1 << UDRE0)))
        ;
        UDR0 = '-';
    }
    wheel = OCR2A;
    if (wheel == 1)
    {
        percentage = 100;
    }
    else if (wheel == 254)
    {
        percentage = 0;
    }
    else
    {
        percentage = 100 - ((wheel + 1) * 100) / 256;
    }
    itoa(percentage, buffer, 10);
    i = 0;
    while (buffer[i] != 0)
    {
        while (!(UCSR0A & (1 << UDRE0)))
            ;
        UDR0 = buffer[i];
        i++;
    }
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = ')';
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = '\n';
}

void debug_d()
{
    DDRA &= ~(1 << PA4);
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = 'D';
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = '(';
    can converter;
    uint8_t canValue = converter.lecture(PA4) >> 2;
    char buffer[5];
    itoa(canValue, buffer, 10);
    uint8_t i = 0;
    while (buffer[i] != 0)
    {
        while (!(UCSR0A & (1 << UDRE0)))
            ;
        UDR0 = buffer[i];
        i++;
    }
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = ')';
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = '\n';
}

void debug_p()
{
    DDRA &= ~(1 << PA0) & ~(1 << PA2);
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = 'P';
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = '(';
    char buffer[5];
    can converter;
    uint8_t canValue;
    canValue = converter.lecture(PA0) >> 2;
    //canValue -= 20;
    itoa(canValue, buffer, 10);
    uint8_t i = 0;
    while (buffer[i] != 0)
    {
        while (!(UCSR0A & (1 << UDRE0)))
            ;
        UDR0 = buffer[i];
        i++;
    }
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = ',';
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = ' ';
    canValue = converter.lecture(PA2) >> 2;
    itoa(canValue, buffer, 10);
    i = 0;
    while (buffer[i] != 0)
    {
        while (!(UCSR0A & (1 << UDRE0)))
            ;
        UDR0 = buffer[i];
        i++;
    }
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = ')';
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = '\n';
}