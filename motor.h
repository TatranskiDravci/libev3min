/*
    devnote:
        Drivers should be kept in a bare-minimum state to ensure
        flexibility and efficiency. Avoid providing higher level
        functionality than necessary.

        All code here is ev3 specific.

        p.v. - possible values
*/
#ifndef MOTOR_H
#define MOTOR_H

#include "config.h"

// motor state bit-masks - to check if motor matches the state, use `state & BITMASK` (p.v. 0, 1...)
#define RUNNING 0b1000
#define RAMPING 0b0100
#define HOLDING 0b0010
#define STALLED 0b0001
#define motorReset(m) motorSetPosition(m, 0)            // motorReset macro

typedef struct Motor
{
    char speed_sp[PATH_LEN];                            // speed setpoint file path
    char target_sp[PATH_LEN];                           // target setpoint file path
    char command[PATH_LEN];                             // command file path
    char stop_action[PATH_LEN];                         // stop action file path
    char position[PATH_LEN];                            // position file path
    char state[PATH_LEN];                               // state file path
    int exists;                                         // motor existence (p.v. 1 - exists, 0 - does not exist)
}
motor;

motor motorNew(char port);                              // `motor` constructor, initializes `motor` type
void motorSetPosition(motor m, int position);           // sets motor position variable to `position`
int motorPosition(motor m);                             // returns motor position
void motorSetSpeed(motor m, int speed);                 // sets motor speed
void motorSetTarget(motor m, int target);               // sets target angle on motor
void motorCommand(motor m, char *command);              // sends command to a motor (e.g. "run-forever", "stop")
void motorSetStopAction(motor m, char *stop_action);    // sets stop action of a motor (p.v. "coast", "brake", "hold")
int motorState(motor m);                                // returns motor state bitmask

#endif
