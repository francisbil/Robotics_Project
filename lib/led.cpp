#include "led.h"

Led::Led() : port_('B'), pin1_(0), pin2_(1) {}

Led::Led(char port, uint8_t pin1, uint8_t pin2) : port_(port), pin1_(pin1), pin2_(pin2) {}

void Led::setRed()
{
    switch (port_)
    {
        case 'A' :
            DDRA |= (1 << pin1_) | (1 << pin2_);
            PORTA |= (1 << pin1_);
            PORTA &= ~(1 << pin2_);
            break;
        case 'B' :
            DDRB |= (1 << pin1_) | (1 << pin2_);
            PORTB |= (1 << pin1_);
            PORTB &= ~(1 << pin2_);
            break;
        case 'C' :
            DDRC |= (1 << pin1_) | (1 << pin2_);
            PORTC |= (1 << pin1_);
            PORTC &= ~(1 << pin2_);
            break;
        case 'D' :
            DDRD |= (1 << pin1_) | (1 << pin2_);
            PORTD |= (1 << pin1_);
            PORTD &= ~(1 << pin2_);
            break;
    }
}

void Led::setGreen()
{
    switch (port_)
    {
        case 'A' :
            DDRA |= (1 << pin1_) | (1 << pin2_);
            PORTA |= (1 << pin2_);
            PORTA &= ~(1 << pin1_);
            break;
        case 'B' :
            DDRB |= (1 << pin1_) | (1 << pin2_);
            PORTB |= (1 << pin2_);
            PORTB &= ~(1 << pin1_);
            break;
        case 'C' :
            DDRC |= (1 << pin1_) | (1 << pin2_);
            PORTC |= (1 << pin2_);
            PORTC &= ~(1 << pin1_);
            break;
        case 'D' :
            DDRD |= (1 << pin1_) | (1 << pin2_);
            PORTD |= (1 << pin2_);
            PORTD &= ~(1 << pin1_);
            break;
    }
}

void Led::setOff()
{
    switch (port_)
    {
        case 'A' :
            PORTA &= ~(1 << pin1_) & ~(1 << pin2_);
            break;
        case 'B' :
            PORTB &= ~(1 << pin1_) & ~(1 << pin2_);
            break;
        case 'C' :
            PORTC &= ~(1 << pin1_) & ~(1 << pin2_);
            break;
        case 'D' :
            PORTD &= ~(1 << pin1_) & ~(1 << pin2_);
            break;
    }
}

void Led::blinkRed()
{
    switch (port_)
    {
        case 'A' :
            DDRA |= (1 << pin1_) | (1 << pin2_);
            for (uint8_t i = 0; i < 15; i++)
            {
                PORTA |= (1 << pin1_);
                PORTA &= ~(1 << pin2_);
                _delay_ms(100);
                PORTA &= ~(1 << pin1_);
                _delay_ms(100);
            }
            break;
        case 'B' :
            DDRB |= (1 << pin1_) | (1 << pin2_);
            for (uint8_t i = 0; i < 15; i++)
            {
                PORTB |= (1 << pin1_);
                PORTB &= ~(1 << pin2_);
                _delay_ms(100);
                PORTB &= ~(1 << pin1_);
                _delay_ms(100);
            }
            break;
        case 'C' :
            DDRC |= (1 << pin1_) | (1 << pin2_);
            for (uint8_t i = 0; i < 15; i++)
            {
                PORTC |= (1 << pin1_);
                PORTC &= ~(1 << pin2_);
                _delay_ms(100);
                PORTC &= ~(1 << pin1_);
                _delay_ms(100);
            }
            break;
        case 'D' :
            DDRD |= (1 << pin1_) | (1 << pin2_);
            for (uint8_t i = 0; i < 15; i++)
            {
                PORTD |= (1 << pin1_);
                PORTD &= ~(1 << pin2_);
                _delay_ms(100);
                PORTD &= ~(1 << pin1_);
                _delay_ms(100);
            }
            break;
    }
}

void Led::blinkGreen()
{
    switch (port_)
    {
        case 'A' :
            DDRA |= (1 << pin1_) | (1 << pin2_);
            for (uint8_t i = 0; i < 15; i++)
            {
                PORTA |= (1 << pin2_);
                PORTA &= ~(1 << pin1_);
                _delay_ms(100);
                PORTA &= ~(1 << pin2_);
                _delay_ms(100);
            }
            break;
        case 'B' :
            DDRB |= (1 << pin1_) | (1 << pin2_);
            for (uint8_t i = 0; i < 15; i++)
            {
                PORTB |= (1 << pin2_);
                PORTB &= ~(1 << pin1_);
                _delay_ms(100);
                PORTB &= ~(1 << pin2_);
                _delay_ms(100);
            }
            break;
        case 'C' :
            DDRC |= (1 << pin1_) | (1 << pin2_);
            for (uint8_t i = 0; i < 15; i++)
            {
                PORTC |= (1 << pin2_);
                PORTC &= ~(1 << pin1_);
                _delay_ms(100);
                PORTC &= ~(1 << pin2_);
                _delay_ms(100);
            }
            break;
        case 'D' :
            DDRD |= (1 << pin1_) | (1 << pin2_);
            for (uint8_t i = 0; i < 15; i++)
            {
                PORTD |= (1 << pin2_);
                PORTD &= ~(1 << pin1_);
                _delay_ms(100);
                PORTD &= ~(1 << pin2_);
                _delay_ms(100);
            }
            break;
    }
}

void Led::blinkAmber()
{
    switch (port_)
    {
        case 'A' :
            DDRA |= (1 << pin1_) | (1 << pin2_);
            for (uint16_t i = 0; i < 252; i++)
            {
                PORTA |= (1 << pin1_);
                PORTA &= ~(1 << pin2_);
                _delay_ms(5);
                PORTA &= ~(1 << pin1_);
                PORTA |= (1 << pin2_);
                _delay_ms(15);
            }
            PORTA &= ~(1 << pin2_) & ~(1 << pin1_);
            break;
        case 'B' :
            DDRB |= (1 << pin1_) | (1 << pin2_);
            for (uint16_t i = 0; i < 252; i++)
            {
                PORTB |= (1 << pin1_);
                PORTB &= ~(1 << pin2_);
                _delay_ms(5);
                PORTB &= ~(1 << pin1_);
                PORTB |= (1 << pin2_);
                _delay_ms(15);
            }
            PORTB &= ~(1 << pin2_) & ~(1 << pin1_);
            break;
        case 'C' :
            DDRC |= (1 << pin1_) | (1 << pin2_);
            for (uint16_t i = 0; i < 252; i++)
            {
                PORTC |= (1 << pin1_);
                PORTC &= ~(1 << pin2_);
                _delay_ms(5);
                PORTC &= ~(1 << pin1_);
                PORTC |= (1 << pin2_);
                _delay_ms(15);
            }
            PORTC &= ~(1 << pin2_) & ~(1 << pin1_);
            break;
        case 'D' :
            DDRD |= (1 << pin1_) | (1 << pin2_);
            for (uint16_t i = 0; i < 252; i++)
            {
                PORTD |= (1 << pin1_);
                PORTD &= ~(1 << pin2_);
                _delay_ms(5);
                PORTD &= ~(1 << pin1_);
                PORTD |= (1 << pin2_);
                _delay_ms(15);
            }
            PORTD &= ~(1 << pin2_) & ~(1 << pin1_);
            break;
    }
}