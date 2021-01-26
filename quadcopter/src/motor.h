#pragma once
#include <Arduino.h>

const int MAXSPEED = 255; 
const int MINSPEED = 0;
const int SPEED_BOOST = 5;

// Pins for inputs
const int CW_IN1 = A0;
const int CW_IN2 = 8;

const int CCW_IN1 = 7;
const int CCW_IN2 = 4;

const int PWMA = 3;
const int PWMB = 5;
const int PWMC = 6;
const int PWMD = 9;

const int STBY = A1;

struct Motor
{
private:
    //variables for the 2 inputs, PWM input
	int in1, in2, pwm, speed;
    static int standby;
    static bool running;

public:
    // Constructor. Mainly sets up pins.
    Motor(int In1pin, int In2pin, int PWMpin);       

    int GetSpeed();

    void SetSpeed(int speed);
    void AdjustSpeed(int speed);

    //set the chip to standby mode.  The drive function takes it out of standby 
    static void RunMotors(bool swap);
    static bool IsRunning();
};
