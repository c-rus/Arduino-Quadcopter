#pragma once
//imu library
#include "SparkFunLSM6DS3.h"
#include "motor.h"
#include "radio.h"
#include "target.h"
#include <Arduino.h>

enum Code
{
    UP = 229,
    DOWN = 440,
    SELECT = 640,
    RIGHT = 542,
    LEFT = 427,
    STANDBY = 757
};


struct FlightControl
{
    private:
        //has-a accelerometer
        LSM6DS3* imu = nullptr;

        //has-a 4 motors: m1, m2, m3, m4
        Motor* m1 = nullptr;
        Motor* m2 = nullptr;
        Motor* m3 = nullptr;
        Motor* m4 = nullptr;

        // motor layout
        //
        //  m1 --- m2
        //  |       |
        //  |       |
        //  m4 --- m3
        //    front

        //has-a RC transciever
        Radio* radio = nullptr;

        //has-a current target objective
        Target objective;

    public:
        FlightControl();
        ~FlightControl();

        //recieve any input from RC controller
        void Input();

        //perform actions based on input and state of accelerometer
        void Action();

    //list of actions the LightningBug can perform
    private:

        void MotorTest();
};