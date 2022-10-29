#ifndef MOVE_H
#define MOVE_H

#include <avr/io.h>
#define F_CPU 8000000UL
#include <avr/interrupt.h>
#include "timer.h"
#include "memoire_24.h"

class Move
{
public:
    Move(uint8_t timerNumber);
    void forwards(uint8_t percentageLeft = 100, uint8_t percentageRight = 100);
    void backwards(uint8_t percentageLeft = 100, uint8_t percentageRight = 100);
    void turnRight(uint8_t percentage = 100);
    void turnLeft(uint8_t percentage = 100);
private:
    Timer timer_;
};

#endif