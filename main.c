#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "motor.h"
#include "sensor.h"

int main(int argc, char *argv[])
{
    motor m;
    m = motorNew('A');
    
    if (!m.exists) return 1;

    motorReset(m);
    motorSetSpeed(m, 200);
    motorSetTarget(m, 360);
    motorSetStopAction(m, "hold");
    motorCommand(m, "run-to-rel-pos");

    while (motorState(m) & RUNNING);

    return 0;
}
