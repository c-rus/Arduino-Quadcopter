#include "flightcontrol.h"

FlightControl::FlightControl()
{
    Serial.println("Initializing FlightControl System...");
    Motor::RunMotors(false);

    //6-degrees-of-freedom!
    imu = new LSM6DS3();   

    if (imu->begin() == 0)
        Serial.println("IMU successfully initialized!");
    else
        Serial.println("IMU failed to initialize.");

    //main-wave communicator!
    radio = new Radio();

    m1 = new Motor(CW_IN1, CW_IN2, PWMA);
    m4= new Motor(CCW_IN1, CCW_IN2, PWMB);
    m3 = new Motor(CW_IN1, CW_IN2, PWMC);
    m2 = new Motor(CCW_IN1, CCW_IN2, PWMD);


    //let's get the motors running!
    Motor::RunMotors(true);
    
    if (Motor::IsRunning())
        Serial.println("Motors are up and running!");
}

FlightControl::~FlightControl()
{
    delete radio;
    delete m1;
    delete m2;
    delete m3;
    delete m4;
    delete imu;
}

void FlightControl::Input()
{
    //check for any incoming signals
    const char* message = radio->Receive();

    if (message != nullptr) {
        //match with the correct action
        //set a target accelerometer reading that drone will strive for
        
        int cmd = 0;
        //lets convert the message into a numerical value
        int size = 0;
        while (message[size] != '\0') 
            size++;

        for (int i = 0; i < size; i++)
            cmd += (int)message[i];

        switch (cmd)
        {
            case Code::SELECT: //[select]
                //MOTOR SWITCH
                //target: level plane but increase speed of propellers so force is > gravity
                objective = Target();
                //MOTOR SWITCH
                Motor::RunMotors(!Motor::IsRunning());
                break;
            case Code::DOWN: //[down]
                //LIFT DOWN 
                //target: level plane but decrease speed of propellers so force is < gravity
                objective = Target();
                m1->AdjustSpeed(-SPEED_BOOST);
                m2->AdjustSpeed(-SPEED_BOOST);
                m3->AdjustSpeed(-SPEED_BOOST);
                m4->AdjustSpeed(-SPEED_BOOST);
                break;
            case Code::UP: //[up]
                //LIFT OFF
                //target: slanted plane with front propellors lower
                objective = Target();
                m1->AdjustSpeed(SPEED_BOOST);
                m2->AdjustSpeed(SPEED_BOOST);
                m3->AdjustSpeed(SPEED_BOOST);
                m4->AdjustSpeed(SPEED_BOOST);
                break;
            case Code::RIGHT: //[right]
                //ROTATE RIGHT 
                //target: level plane but ang. momentum twist right
                objective = Target();
                m1->SetSpeed(MINSPEED);
                m2->SetSpeed(MAXSPEED/2);
                m3->SetSpeed(MINSPEED);
                m4->SetSpeed(MAXSPEED/2);
                
                break;
            case Code::LEFT: //[left]
                //ROTATE LEFT
                //target: level plane but ang. momentum twist left
                objective = Target();
                m1->SetSpeed(MAXSPEED/2);
                m2->SetSpeed(MINSPEED);
                m3->SetSpeed(MAXSPEED/2);
                m4->SetSpeed(MINSPEED);
                
                break;
            case Code::STANDBY: //[standby]
                //STANDBY
                //not yet implementing for decoding
                break;

            default:
                Serial.println("ERROR: Code not found.");
        }
    }
    //have no commands, so let's just suspend ourself in the air
    else {
        Serial.println("No message detected...");
        //BALANCE
        objective = Target();
    }
}

void FlightControl::Action()
{
    //read in all values for the current status of the drone
    Target currentStatus = Target(*imu);

    
    //check if we need to make adjustments to our propellors' speeds
    if (!(currentStatus == objective) && Motor::IsRunning()) {
        Serial.println("flight adjusting!");
    }

}




//*=====Command Center=====*//

void FlightControl::MotorTest()
{
    m1->SetSpeed(MAXSPEED/3);
    m2->SetSpeed(MAXSPEED/3);
    m3->SetSpeed(MAXSPEED/3);
    m4->SetSpeed(MAXSPEED/3);

    delay(1000);

    m1->SetSpeed(MINSPEED);
    m2->SetSpeed(MINSPEED);
    m3->SetSpeed(MINSPEED);
    m4->SetSpeed(MINSPEED);

    delay(500);

    m1->SetSpeed(MAXSPEED/3);
    delay(1000);
    m1->SetSpeed(MINSPEED);
    m2->SetSpeed(MAXSPEED/3);
    delay(1000);
    m2->SetSpeed(MINSPEED);
    m3->SetSpeed(MAXSPEED/3);
    delay(1000);
    m3->SetSpeed(MINSPEED);
    m4->SetSpeed(MAXSPEED/3);
    delay(1000);
    m4->SetSpeed(MINSPEED);

    delay(1000);
}


//increase speed uniformly across all motors until the upward force is greater than gravity


//decrease speed uniformly across all motors until the upward force is less than gravity


//set the speed uniformly across all motors until the upward force is equal to gravity 