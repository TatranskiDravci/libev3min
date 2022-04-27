#include <stdio.h>
#include <stdlib.h>
#include "motor.h"
#include "sensor.h"

int main(int argc, char *argv[])
{
    sensor s;
    s = sensorNew('1');
    
    if (!s.exists) return 1;

    double value0, value1;
    value0 = sensorReadDecimal(s, '0');
    printf("%f\n", value0);

    sensorReset(&s);
    value0 = sensorReadDecimal(s, '0');
    value1 = sensorReadDecimal(s, '1');

    printf("%f %f\n", value0, value1);

    return 0;
}
