#include <stdio.h>
#include <stdlib.h>
#include "motor.h"
#include "sensor.h"

int main(int argc, char *argv[])
{
    sensor s;
    s = sensorNew('1');
    
    if (!s.exists) return 1;

    printf("%f\n", sensorReadDecimal(s, '0'));

    sensorSetMode(s, "GYRO-RATE");
    sensorSetMode(s, "GYRO-ANG");
    sensorReset(&s);

    printf("%f\n", sensorReadDecimal(s, '0'));

    return 0;
}
