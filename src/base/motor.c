#include "motor.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../shared.h"

const char *MOTOR_INIT_PATH[6] = {"/speed", "/position_sp", "/command", "/stop_action", "/position", "/state"};
const int  MOTOR_INIT_LEN[6]   = {6, 12, 8, 12, 9, 6};

motor motorNew(char port)
{
        motor m;

        char *path;
        int path_len;
        path_len = devicePath(&path, port, MOTOR, MOTOR_PREFIX);

        if (!path_len)
        {
                m.exists = 0;
                fprintf(stderr, "Motor not found on port %c\n", port);
                return m;
        }
        m.exists = 1;

        for (int i = 0; i < 6; i++)
        {
                m.paths[i] = malloc((path_len + MOTOR_INIT_LEN[i]) * sizeof(char));
                strcpy(m.paths[i], path);
                strcat(m.paths[i], MOTOR_INIT_PATH[i]);
        }

        return m;
}

void motorSetPosition(motor m, int position)
{
        writeValue(m.paths[M_Position], position, "%d");
}

int motorGetPosition(motor m)
{
        int position;
        readValue(&position, m.paths[M_Position], "%d");
        return position;
}

void motorSetTarget(motor m, int target)
{
        writeValue(m.paths[M_Target], target, "%d");
}

void motorSetSpeed(motor m, int speed)
{
        writeValue(m.paths[M_Speed], speed, "%d");
}

void motorCommand(motor m, char *command)
{
        writeValue(m.paths[M_Command], command, "%s");
}

void motorSetStopAction(motor m, char *stop_action)
{
        writeValue(m.paths[M_StopAction], stop_action, "%s");
}

int motorState(motor m)
{
        int state_mask;
        state_mask = 0;

        FILE *fp;
        fp = fopen(m.paths[M_State], "r");

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
