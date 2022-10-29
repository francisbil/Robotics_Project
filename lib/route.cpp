#include "route.h"

Route::Route() : leftPhotoresistor_(0), rightPhotoresistor_(0), lightDifference_(0), leftAmbientLight_(160), rightAmbientLight_(147)
{
    /*led_ = Led();
    converter_ = can();
    move_ = Move(2);
    button_ = Button(true);
    timer_ = Timer(1);
    memoire24_ = Memoire24CXXX();*/
}

Route::~Route() {}

uint8_t Route::chooseMode()
{
    DDRD &= ~(1 << PD2) & ~(1 << PD3);
    while ( ((PIND & (1 << PD2)) == 0) && ((PIND & (1 << PD3)) != 0) )
        ;
    _delay_ms(30);
    uint8_t choice = 0;
    if ( ((PIND & (1 << PD2)) != 0) )
    {
        led_.blinkGreen();
        choice = 1;
    }
    else if ( ((PIND & (1 << PD3)) == 0) )
    {
        led_.blinkRed();
        choice = 2;
    }
    return choice;
}

void Route::enableBreadboardButton()
{
    cli();
    DDRD &= ~(1 << PD3);
    EIMSK |= (1 << INT1);
    EICRA |= (1 << ISC11);
    EICRA &= ~(1 << ISC10);
    sei();
}

void Route::followWall()
{
    while (distanceSensor_ > 35)
    {
        if (distanceSensor_ > 90)
        {
            // virage a gauche
            move_.forwards(40, 61);
        }
        else if (distanceSensor_ <= 90 && distanceSensor_ > 74)
        {
            // a gauche aussi
            move_.forwards(40, 56);
        }
        else if (distanceSensor_ <= 74 && distanceSensor_ > 70)
        {
            // tout droit
            move_.forwards(45, 40);
        }
        else if (distanceSensor_ <= 70 && distanceSensor_ > 35)
        {
            // virage a droite
            move_.forwards(68, 40);
            
        }
        _delay_ms(10);
        updateCanValue(PA4);
    }
}

void Route::followLight()
{
    while (leftPhotoresistor_ > leftAmbientLight_ || rightPhotoresistor_ > rightAmbientLight_)
    {
        updateCanValue(PA4);
        if (distanceSensor_ > 40)
        {
            break;
        }
        lightDifference_ = leftPhotoresistor_ - rightPhotoresistor_;
        if (lightDifference_ > 0 && lightDifference_ < 30)
        {
            // tout droit, vitesse variable
            if (leftPhotoresistor_ < 210)
            {
                move_.forwards(45, 40);
            }
            else if (leftPhotoresistor_ >= 210 && leftPhotoresistor_ < 215)
            {
                move_.forwards(58, 53);
            }
            else if (leftPhotoresistor_ >= 215 && leftPhotoresistor_ < 220)
            {
                move_.forwards(80, 74);
            }
            else if (leftPhotoresistor_ >= 220)
            {
                move_.forwards(100, 90);
            }
        }
        else if (lightDifference_ >= 30 && lightDifference_ < 40)
        {
            // virage leger gauche
            move_.forwards(40, 56);
        }
        else if (lightDifference_ >= 40 && lightDifference_ < 42)
        {
            // virage leger gauche
            move_.forwards(40, 59);
        }
        else if (lightDifference_ >= 42 && lightDifference_ < 44)
        {
            // virage leger gauche
            move_.forwards(40, 62);
        }
        else if (lightDifference_ >= 44)
        {
            // rotation gauche
            move_.turnLeft();
        }
        else if (lightDifference_ <= 0 && lightDifference_ > -16)
        {
            // virage leger droit
            move_.forwards(58, 40);
        }
        else if (lightDifference_ <= -16 && lightDifference_ > -25)
        {
            // virage leger droit
            move_.forwards(61, 40);
        }
        else if (lightDifference_ <= -25 && lightDifference_ > -30)
        {
            // virage leger droit
            move_.forwards(64, 40);
        }
        else if (lightDifference_ <= -30)
        {
            // rotation droit
            move_.turnRight();
            
        }
        _delay_ms(10);
        updateCanValue(PA0);
        updateCanValue(PA2);
    }
}

void Route::doUturn(uint16_t memoryAddress)
{
    TIMSK1 = 0;
    memoire24_.ecriture(memoryAddress, 0xFF);
    _delay_ms(1000);
    move_.forwards(100, 59);
    led_.blinkAmber();
    move_.forwards(0, 0);
}

void Route::finish(uint16_t memoryAddress)
{
    TIMSK1 = 0;
    move_.forwards(0, 0);
    memoire24_.ecriture(memoryAddress, 0xFF);
    led_.setRed();
    _delay_ms(2000);
    led_.setGreen();
}

void Route::replay()
{
    uint16_t memoryAddress = 0;
    uint8_t donneeLue[1];
    move_.forwards(0, 0);
    uint8_t leftWheelSpeed;
    uint8_t rightWheelSpeed;
    memoire24_.lecture(memoryAddress, donneeLue);
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
        memoryAddress++;
        memoire24_.lecture(memoryAddress, donneeLue);
        leftWheelSpeed = donneeLue[0];
        memoryAddress++;
        memoire24_.lecture(memoryAddress, donneeLue);
        if (donneeLue[0] == 1)
        {
            PORTD |= (1 << PD5);
        }
        else
        {
            PORTD &= ~(1 << PD5);
        }
        memoryAddress++;
        memoire24_.lecture(memoryAddress, donneeLue);
        rightWheelSpeed = donneeLue[0];
        memoryAddress++;
        memoire24_.lecture(memoryAddress, donneeLue);
        OCR2B = leftWheelSpeed;
        OCR2A = rightWheelSpeed;
        _delay_ms(50);
    }
    move_.forwards(0, 0);
    led_.setGreen();
}

void Route::enableInterruptButton()
{
    button_.enable();
}

void Route::startCtcTimer(uint32_t delay)
{
    timer_.enableCtc(delay);
}

void Route::stopRobot()
{
    move_.forwards(0, 0);
}

void Route::updateCanValue(uint8_t pin)
{
    uint8_t canValue = converter_.lecture(pin) >> 2;
    switch (pin)
    {
        case 0 :
            leftPhotoresistor_ = canValue;
            break;
        case 2 :
            rightPhotoresistor_ = canValue;
            break;
        case 4 :
            distanceSensor_ = canValue;
            break;
    }
}

void Route::setAmbientLight(uint8_t leftAmbientLight, uint8_t rightAmbientLight)
{
    leftAmbientLight_ = leftAmbientLight;
    rightAmbientLight_ = rightAmbientLight;
}