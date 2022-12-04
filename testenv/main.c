#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../src/motor.h"
#include "../src/sensor.h"

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

    int state;
    state = motorState(m);

    printf("state[%d]: ", state);
    if (state & RAMPING) printf("ramping ");
    if (state & HOLDING) printf("holding ");
    if (state & STALLED) printf("stalled ");
    if (state & RUNNING) printf("running");
    printf("\n");

    sensor s;
    s = sensorNew('1');
    printf("value: %f\n", sensorReadDecimal(s, '0'));

    return 0;
}
