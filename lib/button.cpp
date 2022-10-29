#include "button.h"

Button::Button(bool risingEdge) : risingEdge_(risingEdge) {}

void Button::enable()
{
    cli();
    DDRD &= ~(1 << PD2);
    EIMSK |= (1 << INT0);
    if (risingEdge_)
    {
        EICRA |= (1 << ISC01) | (1 << ISC00);
    }
    else
    {
        EICRA |= (1 << ISC01);
        EICRA &= ~(1 << ISC00);
    }
    sei();
}

void Button::disable()
{
    cli();
    EIMSK &= ~(1 << INT0);
    sei();
}