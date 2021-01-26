#include <Arduino.h>
#include "flightcontrol.h"

FlightControl* fc = nullptr;

void setup()
{
    Serial.begin(19200);
    
    //create a new flightcontrol
    fc = new FlightControl();
}

void loop()
{
    Serial.println("looping...");
    fc->Input();
    fc->Action();
}