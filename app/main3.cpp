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

// Bouton interrupt
volatile uint8_t gFini = 0;
// Bouton blanc
volatile uint8_t gDemiTour = 0;
// Adresse memoire externe
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
    DDRD |= (1 << PD4) | (1 << PD5);
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

void modeParcours();
void modeReprise();

int main()
{
    DDRD &= ~(1 << PD2) & ~(1 << PD3);
    while ( ((PIND & (1 << PD2)) == 0) && ((PIND & (1 << PD3)) != 0) )
        ;

    _delay_ms(30);
    Led led('B', 0, 1);
    if ( ((PIND & (1 << PD2)) != 0) )
    {
        led.blinkGreen();
        modeParcours();
    }
    else if ( ((PIND & (1 << PD3)) == 0) )
    {
        led.blinkRed();
        modeReprise();
    }

    

    return 0;
}

void modeParcours()
{
    can converter;
    Uart uart;
    Move move(2);
    Led led('B', 0, 1);
    uint8_t canValue;
    uint8_t canValueLeft;
    uint8_t canValueRight;
    int16_t canDifference;
    uint8_t valeurAmbianteLeft = 160;
    uint8_t valeurAmbianteRight = 147;
    Button button(true);
    button.enable();
    cli();
    DDRD &= ~(1 << PD3);
    EIMSK |= (1 << INT1);
    EICRA |= (1 << ISC11);
    EICRA &= ~(1 << ISC10);
    sei();

    // On part le timer pour enregistrer les deplacements
    Timer timer(1);
    timer.enableCtc(50);

    while (true)
    {
        canValue = converter.lecture(PA4) >> 2;
        canValueLeft = converter.lecture(PA0) >> 2;
        canValueRight = converter.lecture(PA2) >> 2;
        while (canValue > 40)
        {
            if (canValue > 90)
            {
                // virage a gauche
                move.forwards(40, 61);
                led.setRed();
            }
            else if (canValue <= 90 && canValue > 74)
            {
                // a gauche aussi
                move.forwards(40, 56);
            }
            else if (canValue <= 74 && canValue > 70)
            {
                // tout droit
                move.forwards(45, 40);
                led.setOff();
            }
            else if (canValue <= 70 && canValue > 45) // 68 60
            {
                // a droite
                led.setGreen();
                move.forwards(68, 40);
                
            }
            else if (canValue <= 45 && canValue > 40)
            {
                // beaucoup a droite
                /*move.turnRight(100);
                _delay_ms(500);
                move.forwards(45, 40);
                _delay_ms(2500);
                move.turnLeft(100);
                _delay_ms(520);
                move.forwards(0, 0);
                _delay_ms(1000);
                move.forwards(65, 33);*/
                move.forwards(68, 40);
            }
            /*else if (canValue <= -9 && canValue > -16)
            {
                // virage prononce droit
                move.forwards(100, 63);
            }
            else if (canValue <= -16)
            {
                // rotation droit
                move.turnRight();
                
            }*/
            DEBUG_PRINTV();
            _delay_ms(10);
            canValue = converter.lecture(PA4) >> 2;
        }

        // flashlight
        while (canValueLeft > valeurAmbianteLeft || canValueRight > valeurAmbianteRight)
        {
            canValue = converter.lecture(PA4) >> 2;
            if (canValue > 40)
            {
                break;
            }
            canDifference = canValueLeft - canValueRight;
            if (canDifference > 0 && canDifference < 30)
            {
                /*tout droit
                //move.forwards(45, 40);*/
                if (canValueLeft < 170)
                {
                    move.forwards(45, 40);
                }
                else if (canValueLeft >= 170 && canValueLeft < 180)
                {
                    move.forwards(58, 53);
                }
                else if (canValueLeft >= 180 && canValueLeft < 190)
                {
                    move.forwards(80, 74);
                }
                else if (canValueLeft >= 190)
                {
                    move.forwards(100, 90);
                }

            }
            else if (canDifference >= 30 && canDifference < 40)
            {
                // virage leger gauche
                move.forwards(40, 56);
            }
            else if (canDifference >= 40 && canDifference < 50)
            {
                // virage leger gauche
                move.forwards(40, 59);
            }
            else if (canDifference >= 50 && canDifference < 60)
            {
                // virage leger gauche
                move.forwards(40, 62);
            }
            else if (canDifference >= 60)
            {
                // virage prononce gauche
                move.turnLeft();
            }
            else if (canDifference <= 0 && canDifference > -16)
            {
                // virage leger droit
                move.forwards(58, 40);
            }
            else if (canDifference <= -16 && canDifference > -32)
            {
                // virage leger droit
                move.forwards(61, 40);
            }
            else if (canDifference <= -32 && canDifference > -50)
            {
                // virage leger droit
                move.forwards(64, 40);
            }
            else if (canDifference <= -50)
            {
                // rotation droit
                move.turnRight();
                
            }
            //DEBUG_PRINTV();
            DEBUG_PRINTP();
            //DEBUG_PRINT();
            _delay_ms(10);
            canValueLeft = converter.lecture(PA0) >> 2;
            canValueRight = converter.lecture(PA2) >> 2;
        }

        if (gFini == 1)
        {
            break;
        }

        if (gDemiTour == 1)
        {
            TIMSK1 = 0;
            Memoire24CXXX memoire24;
            memoire24.ecriture(gAdresse, 0xFF);
            _delay_ms(1000);
            move.forwards(100, 60);
            led.blinkAmber();
            move.forwards(0, 0);
            gDemiTour = 0;
        }
        move.forwards(0, 0);
        _delay_ms(10);
    }

    if (gFini == 1)
    {
        TIMSK1 = 0;
        gFini = 0;
        move.forwards(0, 0);
        Memoire24CXXX memoire242;
        memoire242.ecriture(gAdresse, 0xFF);
        led.setRed();
        _delay_ms(2000);
        led.setGreen();
    }
}

void modeReprise()
{
    gAdresse = 0;
    Memoire24CXXX memoire24;
    Uart uart;
    uint8_t donneeLue[1];
    Move move(2);
    move.forwards(0, 0);
    memoire24.lecture(gAdresse, donneeLue);
    uint8_t leftWheelSpeed;
    uint8_t rightWheelSpeed;
    while (donneeLue[0] != 0xFF)
    {
        if (donneeLue[0] == 1)
        {
            PORTD |= (1 << PD4);
        }
        else
        {
            PORTD &= ~(1 << PD4);
        }
        gAdresse++;
        memoire24.lecture(gAdresse, donneeLue);
        leftWheelSpeed = donneeLue[0];
        /*leftWheelSpeed = donneeLue[0];
        if (leftWheelSpeed == 1)
        {
            leftWheelSpeed = 100;
        }
        else if (leftWheelSpeed == 254)
        {
            leftWheelSpeed = 0;
        }
        else
        {
            leftWheelSpeed = 100 - ((leftWheelSpeed + 1) * 100) / 256;
        }*/
        gAdresse++;
        memoire24.lecture(gAdresse, donneeLue);
        if (donneeLue[0] == 1)
        {
            PORTD |= (1 << PD5);
        }
        else
        {
            PORTD &= ~(1 << PD5);
        }
        gAdresse++;
        memoire24.lecture(gAdresse, donneeLue);
        rightWheelSpeed = donneeLue[0];
        /*rightWheelSpeed = donneeLue[0];
        if (rightWheelSpeed == 1)
        {
            rightWheelSpeed = 100;
        }
        else if (rightWheelSpeed == 254)
        {
            rightWheelSpeed = 0;
        }
        else
        {
            rightWheelSpeed = 100 - ((rightWheelSpeed + 1) * 100) / 256;
        }*/
        gAdresse++;
        DEBUG_PRINT(leftWheelSpeed);
        DEBUG_PRINT(rightWheelSpeed);
        memoire24.lecture(gAdresse, donneeLue);
        OCR2B = leftWheelSpeed;
        OCR2A = rightWheelSpeed;
        //move.forwards(leftWheelSpeed, rightWheelSpeed);
        //DEBUG_PRINTV();
        _delay_ms(50);
    }
    move.forwards(0, 0);
    Led led;
    led.setGreen();
}