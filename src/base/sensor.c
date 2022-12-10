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
                char s_path[256] = SENSOR_PREFIX;
                char s_address[256], address;

                strcat(s_path, dir->d_name);
                strCopyConcat(s_address, s_path, "/address");

                FILE *address_fp;
                address_fp = fopen(s_address, "r");
                fseek(address_fp, 12, SEEK_SET);
                address = fgetc(address_fp);
                fclose(address_fp);

                // check if found sensor port matches given port
                if (port != address) continue;

                // copy address and concatenate appropriate file names
                strCopyConcat(s.command, s_path, "/command");
                strCopyConcat(s.value, s_path, "/value");
                strCopyConcat(s.mode, s_path, "/mode");
                strCopyConcat(s.decimals, s_path, "/decimals");

                // cache decimals
                sensorReset(&s);

                // cache length of `s.value` and shift null terminator
                s.value_len = strlen(s.value);
                s.value[s.value_len + 1] = '\0';

                s.exists = 1;
                break;
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
        int value;
        readValue(&value, s->decimals, "%d");

        s->decimal = 1;
        for (int i = 0; i < value; i++) s->decimal *= 0.1;
}

void sensorCommand(sensor s, char *command)
{
        writeValue(s.command, command, "%s");
}

int sensorRead(sensor s, char n)
{
        s.value[s.value_len] = n;

        int value;
        readValue(&value, s.value, "%d");
        return value;
}

double sensorReadDecimal(sensor s, char n)
{
        return s.decimal * sensorRead(s, n);
}
