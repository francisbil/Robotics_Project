#include "move.h"

Move::Move(uint8_t timerNumber)
{
    timer_ = Timer(timerNumber);
}

void Move::forwards(uint8_t percentageLeft, uint8_t percentageRight)
{
    cli();
    switch (timer_.getTimerNumber())
    {
        case 0 :
            DDRB |= (1 << PB5) | (1 << PB6);
            PORTB &= ~(1 << PB5) & ~(1 << PB6);
            break;
        case 1 :
            DDRD |= (1 << PD6) | (1 << PD7);
            PORTD &= ~(1 << PD6) & ~(1 << PD7);
            break;
        case 2 :
            DDRD |= (1 << PD4) | (1 << PD5);
            PORTD &= ~(1 << PD4) & ~(1 << PD5);
            break;
    }
    timer_.enablePwm(percentageLeft, percentageRight);
    sei();
}

void Move::backwards(uint8_t percentageLeft, uint8_t percentageRight)
{
    cli();
    switch (timer_.getTimerNumber())
    {
        case 0 :
            DDRB |= (1 << PB5) | (1 << PB6);
            PORTB |= (1 << PB5) | (1 << PB6);
            break;
        case 1 :
            DDRD |= (1 << PD6) | (1 << PD7);
            PORTD |= (1 << PD6) | (1 << PD7);
            break;
        case 2 :
            DDRD |= (1 << PD4) | (1 << PD5);
            PORTD |= (1 << PD4) | (1 << PD5);
            break;
    }
    timer_.enablePwm(percentageLeft, percentageRight);
    sei();
}

void Move::turnRight(uint8_t percentage)
{
    forwards(percentage, percentage);
    cli();
    switch (timer_.getTimerNumber())
    {
        case 0 :
            PORTB |= (1 << PB5);
            break;
        case 1 :
            PORTD |= (1 << PD7);
            break;
        case 2 :
            PORTD |= (1 << PD5);
            break;
    }
    sei();
}

void Move::turnLeft(uint8_t percentage)
{
    forwards(percentage, percentage);
    cli();
    switch (timer_.getTimerNumber())
    {
        case 0 :
            PORTB |= (1 << PB6);
            break;
        case 1 :
            PORTD |= (1 << PD6);
            break;
        case 2 :
            PORTD |= (1 << PD4);
            break;
    }
    sei();
}