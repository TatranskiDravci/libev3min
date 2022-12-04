#include "motor.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "shared.h"

motor motorNew(char port)
{
    motor m;
    m.exists = 0;

    DIR *d;
    struct dirent *dir;
    d = opendir(MOTOR_PREFIX);

    if (d) while ((dir = readdir(d)) != NULL) if (dir->d_name[0] == 'm')
    {
        char m_path_pure[256] = MOTOR_PREFIX;
        char m_address[256], address_buffer[15];

        strcat(m_path_pure, dir->d_name);
        strCopyConcat(m_address, m_path_pure, "/address");

        FILE *address_fp;
        address_fp = fopen(m_address, "r");
        fgets(address_buffer, 15, address_fp);
        fclose(address_fp);

        // check if found motor port matches given port
        if (port == address_buffer[13])
        {
            // copy address and concatenate appropriate file names
            strCopyConcat(m.speed_sp, m_path_pure, "/speed_sp");
            strCopyConcat(m.target_sp, m_path_pure, "/position_sp");
            strCopyConcat(m.command, m_path_pure, "/command");
            strCopyConcat(m.stop_action, m_path_pure, "/stop_action");
            strCopyConcat(m.position, m_path_pure, "/position");
            strCopyConcat(m.state, m_path_pure, "/state");

            m.exists = 1;
            break;
        }
    }

    closedir(d);
    if (!m.exists) printf("Motor not found on port %c\n", port);
    return m;
}

void motorSetPosition(motor m, int position)
{
    FILE *fp;
    fp= fopen(m.position, "w");
    fprintf(fp, "%d", position);
    fclose(fp);
}

int motorPosition(motor m)
{
    int position;

    FILE *fp;
    fp = fopen(m.position, "r");
    fscanf(fp, "%d", &position);
    fclose(fp);

    return position;
}

void motorSetTarget(motor m, int target)
{
    FILE *fp;
    fp = fopen(m.target_sp, "w");
    fprintf(fp, "%d", target);
    fclose(fp);
}

void motorSetSpeed(motor m, int speed)
{
    FILE *fp;
    fp = fopen(m.speed_sp, "w");
    fprintf(fp, "%d", speed);
    fclose(fp);
}

void motorCommand(motor m, char *command)
{
    FILE *fp;
    fp = fopen(m.command, "w");
    fprintf(fp, "%s", command);
    fclose(fp);
}

void motorSetStopAction(motor m, char *stop_action)
{
    FILE *fp;
    fp = fopen(m.stop_action, "w");
    fprintf(fp, "%s", stop_action);
    fclose(fp);
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

    // mask bits based on characters unique for each state
    while (*states != '\0') switch (*states)
    {
        case 'u':   state_mask |= RUNNING; states += 6; break;
        case 'm':   state_mask |= RAMPING; states += 5; break;
        case 'h':   state_mask |= HOLDING; states += 7; break;
        case 's':   state_mask |= STALLED; states += 7; break;
        default:    states++;
    }

    return state_mask;
}
