#pragma once
#include "SparkFunLSM6DS3.h"
#include <math.h>

//an accel+gyro reading to strive for when we are flying in the air
struct Target
{
private:
    float aX, aY, aZ;
    float gX, gY, gZ;
    int s1, s2, s3, s4;

public:
    Target();
    Target(LSM6DS3& imu);

    bool operator==(const Target& rhs);
};