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

volatile uint8_t gAdresse = 0;

int main()
{
    Uart uart;
    Memoire24CXXX memoire24;
    uint8_t donneeLue[1];
    Move move(2);
    Led led;
    memoire24.lecture(gAdresse, donneeLue);
    while (donneeLue[0] != 0xFF)
    {
        DEBUG_PRINT(donneeLue[0]);
        //uart.transmission(donneeLue[0]);
        gAdresse++;
        memoire24.lecture(gAdresse, donneeLue);
        DEBUG_PRINT(donneeLue[0]);
        //uart.transmission(donneeLue[0]);
        gAdresse++;
        memoire24.lecture(gAdresse, donneeLue);
        DEBUG_PRINT(donneeLue[0]);
        //uart.transmission(donneeLue[0]);
        gAdresse++;
        memoire24.lecture(gAdresse, donneeLue);
        DEBUG_PRINT(donneeLue[0]);
        //uart.transmission(donneeLue[0]);
        gAdresse++;
        memoire24.lecture(gAdresse, donneeLue);
        _delay_ms(50);
    }
    move.forwards(0, 0);
    led.setRed();

    /*DDRD |= (1 << PD4);
    PORTD |= (1 << PD4);
    DDRD &= ~(1 << PD4);

    if (PIND & (1 << PD4))
    {
        Led led;
        led.setGreen();
    }
    */

    return 0;
}

