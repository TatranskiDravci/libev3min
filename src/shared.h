/*
        devnote:
                shared.h defines macros for frequently occurring expressions.
                Creating separate functions for these commonly occurring expressions
                would sacrifice execution speed, as it would require new function calls.
                Thus, macros are used, sacrificing memory instead.
*/
#ifndef SHARED_H
#define SHARED_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define strCopyConcat(target, source, concat)           \
        ({                                              \
                strcpy(target, source);                 \
                strcat(target, concat);                 \
        })

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

#endif
