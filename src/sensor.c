#include "sensor.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../shared.h"

const char *SENSOR_INIT_PATH[4] = {"/command", "/value", "/mode", "/decimals"};
const int  SENSOR_INIT_LEN[6]   = {8, 7, 5, 9};

sensor sensorNew(char port)
{
        sensor s;

        char *path;
        int path_len;
        path_len = devicePath(&path, port, SENSOR, SENSOR_PREFIX);

        if (!path_len)
        {
                s.exists = 0;
                fprintf(stderr, "Sensor not found on port %c\n", port);
                return s;
        }
        s.exists = 1;

        for (int i = 0; i < 4; i++)
        {
                s.paths[i] = malloc((path_len + SENSOR_INIT_LEN[i]) * sizeof(char));
                strcpy(s.paths[i], path);
                strcat(s.paths[i], SENSOR_INIT_PATH[i]);
        }

        // cache decimals
        sensorReset(&s);

        // `s.value` caching for future sensor readings
        s.value_len = path_len + SENSOR_INIT_LEN[S_Value] - 1;
        s.paths[S_Value][s.value_len] = '\0';

        return s;
}

void sensorSetMode(sensor s, char *mode)
{
        writeValue(s.paths[S_Mode], mode, "%s");
}

void sensorReset(sensor *s)
{
        int value;
        readValue(&value, s->paths[S_Decimals], "%d");

        s->decimal = 1;
        for (int i = 0; i < value; i++) s->decimal *= 0.1;
}

void sensorCommand(sensor s, char *command)
{
        writeValue(s.paths[S_Command], command, "%s");
}

int sensorRead(sensor s, char n)
{
        s.paths[S_Value][s.value_len - 1] = n;

        int value;
        readValue(&value, s.paths[S_Value], "%d");
        return value;
}

double sensorReadDecimal(sensor s, char n)
{
        return s.decimal * sensorRead(s, n);
}

void sensorFree(sensor *s)
{
        for (int i = 0; i < 4; i++) free(s->paths[i]);
}
