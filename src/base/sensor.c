#include "sensor.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "../shared.h"

sensor sensorNew(char port)
{
    sensor s;
    s.exists = 0;

    DIR *d;
    struct dirent *dir;
    d = opendir(SENSOR_PREFIX);

    if (d) while ((dir = readdir(d)) != NULL) if (dir->d_name[0] == 's')
    {
        char s_path_pure[256] = SENSOR_PREFIX;
        char s_address[256], address_buffer[14];

        strcat(s_path_pure, dir->d_name);
        strCopyConcat(s_address, s_path_pure, "/address");

        FILE *address_fp;
        address_fp = fopen(s_address, "r");
        fgets(address_buffer, 14, address_fp);
        fclose(address_fp);

        // check if found sensor port matches given port
        if (port == address_buffer[12])
        {
            // copy address and concatenate appropriate file names
            strCopyConcat(s.command, s_path_pure, "/command");
            strCopyConcat(s.value, s_path_pure, "/value");
            strCopyConcat(s.mode, s_path_pure, "/mode");
            strCopyConcat(s.decimals, s_path_pure, "/decimals");

            // cache decimals
            FILE *fp;
            char val[4];
            fp = fopen(s.decimals, "r");
            fgets(val, 4, fp);
            fclose(fp);

            s.decimal = 1;
            for (int i = 0; i < atoi(val); i++) s.decimal *= 0.1;

            // cache length of `s.value` and shift null terminator
            s.value_len = strlen(s.value);
            s.value[s.value_len + 1] = '\0';
            s.exists = 1;
            break;
        }
    }

    closedir(d);
    if (!s.exists) printf("Sensor not found on port %c\n", port);
    return s;
}

void sensorSetMode(sensor s, char *mode)
{
    FILE *fp;
    fp = fopen(s.mode, "w");
    fprintf(fp, "%s", mode);
    fclose(fp);
}

void sensorReset(sensor *s)
{
    // update decimals
    FILE *fp;
    char value[4];
    fp = fopen(s->decimals, "r");
    fgets(value, 4, fp);
    fclose(fp);

    s->decimal = 1;
    for (int i = 0; i < atoi(value); i++) s->decimal *= 0.1;
}

void sensorCommand(sensor s, char *command)
{
    FILE *fp;
    fp = fopen(s.command, "w");
    fprintf(fp, "%s", command);
    fclose(fp);
}

int sensorRead(sensor s, char n)
{
    s.value[s.value_len] = n;
    char value[10];

    FILE *fp;
    fp = fopen(s.value, "r");
    fgets(value, 10, fp);
    fclose(fp);

    return atoi(value);
}

double sensorReadDecimal(sensor s, char n)
{
    return s.decimal * sensorRead(s, n);
}
