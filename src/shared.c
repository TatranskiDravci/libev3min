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

int devicePath(char **__path, char port, char type, char *prefix)
{
        DIR *d;
        struct dirent *dir;
        d = opendir(prefix);

        if (d) while ((dir = readdir(d)) != NULL) if (dir->d_name[0] == type)
        {
                int dir_len;
                dir_len = strlen(dir->d_name) + PATH_LEN + 1;

                char path[dir_len];
                char address[dir_len + 8];

                strcpy(path, prefix);
                strcat(path, dir->d_name);
                strcpy(address, path);
                strcat(address, "/address");

                if (port != devicePort(address, type)) continue;

                *__path = malloc(dir_len * sizeof(char));
                strcpy(*__path, path);

                closedir(d);
                return dir_len;
        }

        closedir(d);
        return 0;
}
