#include "shared.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

int devicePath(char *__path, char __port, char initial, char *prefix)
{
        DIR *d;
        struct dirent *dir;
        d = opendir(prefix);

        if (d) while ((dir = readdir(d)) != NULL) if (dir->d_name[0] == initial)
        {
                char path[256];
                char address[256], port;

                strcpy(path, prefix);
                strcat(path, dir->d_name);
                strCopyConcat(address, path, "/address");


                FILE *address_fp;
                address_fp = fopen(address, "r");


                switch (initial)
                {
                        case 's': fseek(address_fp, 12, SEEK_SET); break;
                        case 'm': fseek(address_fp, 13, SEEK_SET); break;
                }

                port = fgetc(address_fp);
                fclose(address_fp);

                // check if found sensor port matches given port
                if (__port != port) continue;

                strcpy(__path, path);
                closedir(d);
                return 1;
        }

        closedir(d);
        return 0;
}
