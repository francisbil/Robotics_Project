#ifndef BUTTON_H
#define BUTTON_H

#include <avr/io.h>
#define F_CPU 8000000UL
#include <avr/interrupt.h>

class Button
{
public:
    Button(bool risingEdge = true);
    void enable();
    void disable();
private:
    bool risingEdge_;
};

#endif