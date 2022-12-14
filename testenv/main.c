#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../src/base/motor.h"
#include "../src/base/sensor.h"

int main(int argc, char *argv[])
{
        motor m;
        sensor s;

        m = motorNew('A');
        s = sensorNew('1');

        if (!m.exists) return 1;
        if (!s.exists) return 1;

        for (int i = 0; i < 10000; i++) motorState(m);
        for (int i = 0; i < 10000; i++) sensorReadDecimal(s, '0');

        motorFree(&m);
        sensorFree(&s);

        return 0;
}
