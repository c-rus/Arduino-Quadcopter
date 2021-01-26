#include <Arduino.h>
#include "controller.h"

Controller* c = nullptr;

void setup()
{
    Serial.begin(9600);
    Serial.println("booting up!");
    c = new Controller(A4, A5, 4);
}

void loop()
{
    c->Read();
}