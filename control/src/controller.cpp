#include "controller.h"

Controller::Controller(int pinV, int pinH, int pinS) : PIN_VERTICAL(pinV), PIN_HORIZONTAL(pinH), PIN_SELECT(pinS)
{
    pinMode(PIN_VERTICAL, INPUT);
    pinMode(PIN_HORIZONTAL, INPUT);
    pinMode(PIN_SELECT, INPUT_PULLUP);
    radio = new Radio();
}

Controller::~Controller()
{
    delete radio;
}

void Controller::Read()
{
    int temp = analogRead(PIN_VERTICAL);
    jsVertical = map(temp, 0, 1023, 0, 180);
    //Serial.println(jsVertical);
    temp = analogRead(PIN_HORIZONTAL);
    jsHorizontal = map(temp, 0, 1023, 0, 180);
    //Serial.println(jsHorizontal);
    jsSelectState = digitalRead(PIN_SELECT);

    //vertical
    if (jsVertical < LOW_DEFAULT_ANGLE && jsPrevVertical >= LOW_DEFAULT_ANGLE)
        radio->Send("down", 4);
    else if (jsVertical > HIGH_DEFAULT_ANGLE && jsPrevVertical <= HIGH_DEFAULT_ANGLE)
        radio->Send("up", 2);
    
    //horizontal
    else if (jsHorizontal < LOW_DEFAULT_ANGLE && jsPrevHorizontal >= LOW_DEFAULT_ANGLE)
        radio->Send("right", 5);
    else if (jsHorizontal > HIGH_DEFAULT_ANGLE && jsPrevHorizontal <= HIGH_DEFAULT_ANGLE)
        radio->Send("left", 4);
  
    //button
    else if (jsSelectState == LOW && jsPrevSelectState == HIGH) {
        jsPrevSelectState = LOW;
        radio->Send("select", 6);
    }

    jsPrevSelectState = jsSelectState;
    jsPrevHorizontal = jsHorizontal;
    jsPrevVertical = jsVertical;
}