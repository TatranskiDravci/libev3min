/*
        devnote:
                shared.h defines macros (and functions) for frequently occurring expressions.
                Creating separate functions for some these commonly occurring expressions
                would sacrifice execution speed, as it would require new function calls.
                Thus, macros are used, sacrificing memory instead.
*/
#ifndef SHARED_H
#define SHARED_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define writeValue(target, value, format)               \
        ({                                              \
                FILE *fp;                               \
                fp = fopen(target, "w");                \
                fprintf(fp, format, value);             \
                fclose(fp);                             \
        })

#define readValue(target, source, format)               \
        ({                                              \
                FILE *fp;                               \
                fp = fopen(source, "r");                \
                fscanf(fp, format, target);             \
                fclose(fp);                             \
        })

#define SENSOR 's'
#define MOTOR  'm'

char devicePort(char *address, char type);
int devicePath(char **__path, char port, char type, char *prefix);

#endif
