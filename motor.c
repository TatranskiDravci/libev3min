#include "motor.h"

#include <stdio.h>
#include <string.h>
#include <dirent.h>

motor motorNew(char port)
{
    motor m;
    m.exists = 0;

    DIR *d;
    struct dirent *dir;
    d = opendir(PREFIX);

    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            // match 'm' (from "motor") in dir->d_name to locate motor directories
            if (dir->d_name[0] == 'm') {
                char mdname[256] = PREFIX;
                char mdnamec[256], addr_raw[5];
                strcat(mdname, dir->d_name);
                strcpy(mdnamec, mdname);            // copy mdname to mdnamec
                strcat(mdname, "/address");         // get mdname'/address' file path

                FILE *addr_fp;
                addr_fp = fopen(mdname, "r");
                fgets(addr_raw, 5, addr_fp);        // read address

                // check if found motor port matches given port
                if (port == addr_raw[3])
                {
                    // copy addr. and concat. aprrop. file names
                    strcpy(m.speed_sp, mdnamec);
                    strcpy(m.target_sp, mdnamec);
                    strcpy(m.command, mdnamec);
                    strcpy(m.stop_action, mdnamec);
                    strcpy(m.position, mdnamec);
                    strcpy(m.state, mdnamec);
                    strcat(m.speed_sp, "/speed_sp");
                    strcat(m.target_sp, "/position_sp");
                    strcat(m.command, "/command");
                    strcat(m.stop_action, "/stop_action");
                    strcat(m.position, "/position");
                    strcat(m.state, "/state");
                    m.exists = 1;
                    break;
                }
                fclose(addr_fp);
            }
        }
        closedir(d);
    }
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
    FILE *fp;
    int position;
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

    char c;
    while ((c = fgetc(fp)) != EOF)
    {
        // "mask" bits based on characters unique for each state
        switch (c)
        {
            case 'u':
                state_mask |= RUNNING;
                break;
            case 'm':
                state_mask |= RAMPING;
                break;
            case 'h':
                state_mask |= HOLDING;
                break;
            case 's':
                state_mask |= STALLED;
                break;
        }
    }
    fclose(fp);
    return state_mask;
}
