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


int main()
{
    Uart uart;
    while (true)
    {
        DEBUG_PRINTV();
        DEBUG_PRINTP();
        DEBUG_PRINTD();
        _delay_ms(2000);
    }
    return 0;
}