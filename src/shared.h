#ifndef SHARED_H
#define SHARED_H

#include <string.h>

#define strCopyConcat(target, source , concat)  \
    ({                                          \
        strcpy(target, source);                 \
        strcat(target, concat);                 \
    })

#endif
