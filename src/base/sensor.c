#include "sensor.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../shared.h"

sensor sensorNew(char port)
{
        sensor s;

        char s_path[256];
        s.exists = devicePath(s_path, port, SENSOR, SENSOR_PREFIX);

        if (!s.exists)
        {
                printf("Sensor not found on port %c\n", port);
                return s;
        }

        strCopyConcat(s.command, s_path, "/command");
        strCopyConcat(s.value, s_path, "/value");
        strCopyConcat(s.mode, s_path, "/mode");
        strCopyConcat(s.decimals, s_path, "/decimals");

        // cache decimals
        sensorReset(&s);

        // `s.value` caching for future sensor readings
        s.value_len = strlen(s.value);
        s.value[s.value_len + 1] = '\0';

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
