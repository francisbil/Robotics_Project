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
#include "route.h"

volatile uint8_t gFini = 0;
volatile uint8_t gDemiTour = 0;
volatile uint16_t gAdresse = 0;

ISR(INT0_vect)
{
    _delay_ms(30);
    if (PIND & (1 << PD2))
    {
        gFini = 1;
    }
    EIFR |= (1 << INTF0);
}

ISR(INT1_vect)
{
    _delay_ms(30);
    if (!(PIND & (1 << PD3)))
    {
        gDemiTour = 1;
    }
    EIFR |= (1 << INTF1);
}

ISR(TIMER1_COMPA_vect)
{
    Memoire24CXXX memoire24;
    uint8_t leftWheelSpeed = OCR2B;
    uint8_t rightWheelSpeed = OCR2A;
    uint8_t leftWheelDirection;
    uint8_t rightWheelDirection;
    DDRD &= ~(1 << PD4) & ~(1 << PD5);
    if (PIND & (1 << PD4))
    {
        leftWheelDirection = 1;
    }
    else
    {
        leftWheelDirection = 0;
    }
    if (PIND & (1 << PD5))
    {
        rightWheelDirection = 1;
    }
    else
    {
        rightWheelDirection = 0;
    }
    memoire24.ecriture(gAdresse, leftWheelDirection);
    gAdresse++;
    _delay_ms(5);
    memoire24.ecriture(gAdresse, leftWheelSpeed);
    gAdresse++;
    _delay_ms(5);
    memoire24.ecriture(gAdresse, rightWheelDirection);
    gAdresse++;
    _delay_ms(5);
    memoire24.ecriture(gAdresse, rightWheelSpeed);
    gAdresse++;
}

int main()
{
    Route route;
    //route.setAmbientLight(160, 147);
    route.setAmbientLight(205, 195);
    uint8_t mode = route.chooseMode();

    if (mode == 1)
    {
        route.enableInterruptButton();
        route.enableBreadboardButton();
        route.startCtcTimer(50);

        while (true)
        {
            route.updateCanValue(PA4);
            route.updateCanValue(PA0);
            route.updateCanValue(PA2);

            route.followWall();
            route.followLight();
            if (gFini == 1)
            {
                gFini = 0;
                break;
            }
            if (gDemiTour == 1)
            {
                gDemiTour = 0;
                route.doUturn(gAdresse);
            }
            route.stopRobot();
            _delay_ms(10);
        }

        route.finish(gAdresse);

    }
    else if (mode == 2)
    {
        route.replay();
    }

    return 0;
}