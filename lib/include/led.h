#ifndef LED_H
#define LED_H

#include <avr/io.h>
#define F_CPU 8000000UL
#include <avr/interrupt.h>
#include <util/delay.h>

class Led
{
public:
    Led();
    Led(char port, uint8_t pin1, uint8_t pin2);
    void setGreen();
    void setRed();
    void setOff();
    void blinkRed();
    void blinkGreen();
    void blinkAmber();
private:
    char port_;
    uint8_t pin1_;
    uint8_t pin2_;
};

#endif