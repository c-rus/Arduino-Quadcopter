#pragma once
#include <Arduino.h>
#include "radio.h"

struct Controller
{
private:
    const int LOW_DEFAULT_ANGLE = 10;
    const int HIGH_DEFAULT_ANGLE = 120;

    Radio* radio = nullptr;

    const int PIN_VERTICAL;
    const int PIN_HORIZONTAL;
    const int PIN_SELECT;

    int jsVertical;
    int jsHorizontal;
    int jsSelectState;
    int jsPrevSelectState;
    int jsPrevVertical;
    int jsPrevHorizontal;

public:
    Controller(int pinV, int pinH, int pinS);
    ~Controller();

    void Read();
};