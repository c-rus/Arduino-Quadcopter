#include "motor.h"

bool Motor::running = false;
int Motor::standby = STBY;

Motor::Motor(int In2pin, int In1pin, int PWMpin)
{
   in1 = In1pin;
   in2 = In2pin;
   pwm = PWMpin;

   pinMode(in1, OUTPUT);
   pinMode(in2, OUTPUT);
   
   analogWrite(pwm, MINSPEED);

   //all will have correct rotations (cw and ccw) with this setup
   digitalWrite(in1, HIGH);
   digitalWrite(in2, LOW);
}

void Motor::RunMotors(bool swap)
{
   Motor::running = swap;

   pinMode(Motor::standby, OUTPUT);

   if (Motor::running)
      digitalWrite(Motor::standby, HIGH);
   else
      digitalWrite(Motor::standby, LOW);
}

bool Motor::IsRunning()
{
   return running;
}

int Motor::GetSpeed()
{
   return speed;
}

void Motor::SetSpeed(int speed)
{
   this->speed = speed;
   analogWrite(pwm, this->speed);
}

void Motor::AdjustSpeed(int speed)
{
   this->speed += speed;

   //limit the speed between 0 and 255
   if (this->speed > MAXSPEED)
      this->speed = MAXSPEED;
   else if (this->speed < MINSPEED)
      this->speed = MINSPEED;

   analogWrite(pwm, this->speed);
}