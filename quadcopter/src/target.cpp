#include "target.h"

Target::Target()
{
    aX = aY = aZ = 0;
    gX = gY = gZ = 0;
}

Target::Target(LSM6DS3& imu)
{
    aX = imu.readFloatAccelX();
    aY = imu.readFloatAccelY();
    aZ = imu.readFloatAccelZ();

    gX = imu.readFloatGyroX();
    gY = imu.readFloatGyroY();
    gZ = imu.readFloatGyroZ();
    
    Serial.print("a.X: ");
    Serial.println(round(aX));
    Serial.print("a.Y: ");
    Serial.println(round(aY));
    Serial.print("a.Z: ");
    Serial.println(round(aZ));
    Serial.println();

    
}

bool Target::operator==(const Target& rhs)
{
    return ((aX == rhs.aX && aY == rhs.aY && rhs.aZ) &&
        (gX == rhs.gX && gY == rhs.gY && gZ == rhs.gZ));
}
