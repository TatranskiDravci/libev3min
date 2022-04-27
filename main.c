#include <stdio.h>
#include <stdlib.h>
#include "motor.h"

int main(int argc, char *argv[])
{
    motor m;
    m = motorNew('C');

    if (!m.exists) return 1;

    motorSetTarget(m, 100);
    motorSetSpeed(m, 300);
    motorSetStopAction(m, "brake");
    motorCommand(m, "run-to-abs-pos");

    while (motorState(m) & RUNNING);

    return 0;
}
