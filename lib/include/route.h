#ifndef ROUTE_H
#define ROUTE_H

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "button.h"
#include "can.h"
#include "debug.h"
#include "led.h"
#include "memoire_24.h"
#include "move.h"
#include "timer.h"
#include "uart.h"

class Route
{
public:
    Route();
    ~Route();
    uint8_t chooseMode();
    void enableBreadboardButton();
    void followWall();
    void followLight();
    void doUturn(uint16_t memoryAddress);
    void finish(uint16_t memoryAddress);
    void replay();
    void enableInterruptButton();
    void startCtcTimer(uint32_t delay);
    void stopRobot();
    void updateCanValue(uint8_t pin);
    void setAmbientLight(uint8_t leftAmbientLight, uint8_t rightAmbientLight);
private:
    Led led_;
    can converter_;
    Move move_ = Move(2);
    Button button_ = Button(true);
    Timer timer_ = Timer(1);
    Memoire24CXXX memoire24_;
    uint8_t distanceSensor_;
    uint8_t leftPhotoresistor_;
    uint8_t rightPhotoresistor_;
    int16_t lightDifference_;
    uint8_t leftAmbientLight_;
    uint8_t rightAmbientLight_;
};

#endif