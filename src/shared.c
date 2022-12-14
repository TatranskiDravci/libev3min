#include "shared.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../config.h"

char devicePort(char *address, char type)
{
        char port;
        FILE *address_fp;
        address_fp = fopen(address, "r");

        // the position of port char depends on device type
        switch (type)
        {
                case SENSOR: fseek(address_fp, 12, SEEK_SET); break;
                case MOTOR:  fseek(address_fp, 13, SEEK_SET); break;
        }

        port = fgetc(address_fp);
        fclose(address_fp);

        return port;
}

const char *pathPrefix(devtype type)
{
        switch (type)
        {
                case DEVT_Sensor: return SENSOR_PREFIX;
                case DEVT_Motor:  return MOTOR_PREFIX;
        }
        return '\0';
}

int devicePath(char **__path, int *__path_len, char port, devtype type)
{
        const char *prefix = pathPrefix(type);

        DIR *d;
        struct dirent *dir;
        d = opendir(prefix);

        if (!d) return 0;

        int status;

        while ((dir = readdir(d)) != NULL) if (dir->d_name[0] == type)
        {
                *__path_len = strlen(dir->d_name) + PATH_LEN + 1;
                *__path = calloc(*__path_len, sizeof(char));

                char address[*__path_len + 8];          // address file path buffer

                strcpy(*__path, prefix);
                strcat(*__path, dir->d_name);
                strcpy(address, *__path);
                strcat(address, "/address");

                if ((status = (port == devicePort(address, type)))) break;

                free(*__path);
        }

        closedir(d);
        return status;
}
