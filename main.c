#include <stdio.h>
#include <stdlib.h>
#include "motor.h"
#include "sensor.h"

int main(int argc, char *argv[])
{
    motor m;
    m = motorNew('D');

    if (!m.exists) return 1;

    motorSetTarget(m, 360);
    motorSetSpeed(m, 100);
    motorSetStopAction(m, "brake");
    motorCommand(m, "run-to-rel-pos");

    while (motorState(m) & RUNNING);

    return 0;
}
