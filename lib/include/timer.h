#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>
#define F_CPU 8000000UL
#include <avr/interrupt.h>

class Timer
{
public:
    Timer(uint8_t number = 1);
    void enableCtc(uint32_t duration);
    void disableCtc();
    void enablePwm(uint8_t percentageLeft = 100, uint8_t percentageRight = 100);
    void disablePwm();
    uint8_t getTimerNumber();
private:
    uint8_t number_;
};

#endif