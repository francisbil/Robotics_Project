#include "timer.h"

Timer::Timer(uint8_t number) : number_(number) {}

uint8_t Timer::getTimerNumber()
{
    return this->number_;
}

void Timer::enableCtc(uint32_t duration)
{
    cli();
    // Max duration is 32 ms for 8 bit timers
    // and 8388 ms for 16 bit timers
    switch (number_)
    {
        case 0 :
            TCCR0A |= (1 << WGM01);
            TCCR0A &= ~(1 << COM0A1) & ~(1 << COM0A0) & ~(1 << COM0B1) & ~(1 << COM0B0) & ~(1 << WGM00);
            TCCR0B |= (1 << CS02) | (1 << CS00);
            TCCR0B &= ~(1 << WGM02) & ~(1 << CS01);
            TIMSK0 |= (1 << OCIE0A);
            TIMSK0 &= ~(1 << OCIE0B);
            OCR0A = duration*8000/1024;
            TCNT0 = 0;
            break;
        case 1 :
            TCCR1A = 0;
            TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);
            TCCR1B &= ~(1 << WGM13) & ~(1 << CS11);
            TCCR1C = 0;
            TIMSK1 |= (1 << OCIE1A);
            TIMSK1 &= ~(1 << OCIE1B);
            OCR1A = duration*8000/1024;
            TCNT1 = 0;
            break;
        case 2 :
            TCCR2A |= (1 << WGM21);
            TCCR2A &= ~(1 << COM2A1) & ~(1 << COM2A0) & ~(1 << COM2B1) & ~(1 << COM2B0) & ~(1 << WGM20);
            TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);
            TCCR2B &= ~(1 << WGM22);
            TIMSK2 |= (1 << OCIE2A);
            TIMSK2 &= ~(1 << OCIE2B);
            OCR2A = duration*8000/1024;
            TCNT2 = 0;
            break;
    }
    sei();
}

void Timer::disableCtc()
{
    cli();
    switch (number_)
    {
        case 0 :
            TIMSK0 = 0;
            break;
        case 1 :
            TIMSK1 = 0;
            break;
        case 2 :
            TIMSK2 = 0;
            break;
    }
    sei();
}

void Timer::enablePwm(uint8_t percentageLeft, uint8_t percentageRight)
{
    cli();
    uint16_t clockCount1 = 254;
    uint16_t clockCount2 = 254;
    if (percentageLeft != 0 && percentageLeft != 100)
    {
        clockCount1 = (256 * (100 - percentageLeft)) / 100 - 1;
    }
    else if (percentageLeft == 0)
    {
        clockCount1 = 254;
    }
    else if (percentageLeft == 100)
    {
        clockCount1 = 1;
    }
    if (percentageRight != 0 && percentageRight != 100)
    {
        clockCount2 = (256 * (100 - percentageRight)) / 100 - 1;
    }
    else if (percentageRight == 0)
    {
        clockCount2 = 254;
    }
    else if (percentageRight == 100)
    {
        clockCount2 = 1;
    }

    switch (number_)
    {
        case 0 :
            DDRB |= (1 << PB4) | (1 << PB3);
            TCCR0A |= (1 << COM0A1) | (1 << COM0A0) | (1 << COM0B1) | (1 << COM0B0) | (1 << WGM00);
            TCCR0A &= ~(1 << WGM01);
            TCCR0B |= (1 << CS01) | (1 << CS00);
            TCCR0B &= ~(1 << WGM02) & ~(1 << CS02);
            TIMSK0 = 0;
            OCR0A = clockCount2;
            OCR0B = clockCount1;
            break;
        case 1 :
            DDRD |= (1 << PD5) | (1 << PD4);
            TCCR1A |= (1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (1 << COM1B0) | (1 << WGM10);
            TCCR1A &= ~(1 << WGM11);
            TCCR1B |= (1 << CS12);
            TCCR1B &= ~(1 << WGM13) & ~(1 << WGM12) & ~(1 << CS11) & ~(1 << CS10);
            TCCR1C = 0;
            TIMSK1 = 0;
            OCR1A = clockCount2;
            OCR1B = clockCount1;
            break;
        case 2 :
            DDRD |= (1 << PD7) | (1 << PD6);
            TCCR2A |= (1 << COM2A1) | (1 << COM2A0) | (1 << COM2B1) | (1 << COM2B0) | (1 << WGM20);
            TCCR2A &= ~(1 << WGM21);
            TCCR2B |= (1 << CS22) | (1 << CS21);
            TCCR2B &= ~(1 << WGM22) & ~(1 << CS20);
            TIMSK2 = 0;
            OCR2A = clockCount2;
            OCR2B = clockCount1;
            break;
    }
    sei();
}

void Timer::disablePwm()
{
    cli();
    switch (number_)
    {
        case 0 :
            TCCR0A &= ~(1 << COM0A1) & ~(1 << COM0A0) & ~(1 << COM0B1) & ~(1 << COM0B0);
            PORTB &= ~(1 << PB3) & ~(1 << PB4);
            break;
        case 1 :
            TCCR1A &= ~(1 << COM1A1) & ~(1 << COM1A0) & ~(1 << COM1B1) & ~(1 << COM1B0);
            PORTD &= ~(1 << PD4) & ~(1 << PD5);
            break;
        case 2 :
            TCCR2A &= ~(1 << COM2A1) & ~(1 << COM2A0) & ~(1 << COM2B1) & ~(1 << COM2B0);
            PORTD &= ~(1 << PD6) & ~(1 << PD7);
            break;
    }
    sei();
}