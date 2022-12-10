#include "motor.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../shared.h"

motor motorNew(char port)
{
        motor m;

        char m_path[256];
        m.exists = devicePath(m_path, port, MOTOR, MOTOR_PREFIX);

        if (!m.exists)
        {
                printf("Motor not found on port %c\n", port);
                return m;
        }

        strCopyConcat(m.speed_sp, m_path, "/speed_sp");
        strCopyConcat(m.target_sp, m_path, "/position_sp");
        strCopyConcat(m.command, m_path, "/command");
        strCopyConcat(m.stop_action, m_path, "/stop_action");
        strCopyConcat(m.position, m_path, "/position");
        strCopyConcat(m.state, m_path, "/state");

        return m;
}

void motorSetPosition(motor m, int position)
{
        writeValue(m.position, position, "%d");
}

int motorGetPosition(motor m)
{
        int position;
        readValue(&position, m.position, "%d");
        return position;
}

void motorSetTarget(motor m, int target)
{
        writeValue(m.target_sp, target, "%d");
}

void motorSetSpeed(motor m, int speed)
{
        writeValue(m.speed_sp, speed, "%d");
}

void motorCommand(motor m, char *command)
{
        writeValue(m.command, command, "%s");
}

void motorSetStopAction(motor m, char *stop_action)
{
        writeValue(m.stop_action, stop_action, "%s");
}

int motorState(motor m)
{
        int state_mask;
        state_mask = 0;

        FILE *fp;
        fp = fopen(m.state, "r");

        char states[32];
        fgets(states, 32, fp);
        fclose(fp);

        char *c;
        c = states;

        // mask bits based on characters unique for each state
        while (*c != '\0') switch (*c)
        {
                case 'u':   state_mask |= RUNNING; c += 6; break;
                case 'm':   state_mask |= RAMPING; c += 5; break;
                case 'h':   state_mask |= HOLDING; c += 7; break;
                case 's':   state_mask |= STALLED; c += 7; break;
                default:    c++;
        }

        return state_mask;
}
