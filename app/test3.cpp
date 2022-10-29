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
    Move move(2);
    Led led;

    // tout droit
    //move.forwards(45, 40);

    // a gauche
    //move.forwards(40, 46);

    // bcp a gauche
    //move.forwards(40, 51);

    // a droite
    //move.forwards(58, 40);

    move.forwards(99, 90);
    

    return 0;
}