#ifndef CONTROLLER_H
#define CONTROLLER_H

#define CDEF_PORT 8989
#define CDEF_ADDRESS NULL

#define CSTAT_OK                0b000
#define CSTAT_CREATION_ERROR    0b001
#define CSTAT_INVALID_ADDRESS   0b010
#define CSTAT_CONNECTION_ERROR  0b100

typedef struct Controller
{
    int socket, client, status;
}
controller;

typedef enum Resource
{
    A, B, X, Y,
    PadUP, PadDOWN, PadLEFT, PadRIGHT,
    ButtonL1, ButtonL2, ButtonR1, ButtonR2,
    LeverLX, LeverLY, LeverRX, LeverRY
}
resource;

controller controllerConnect(char *addr, int port);
int controllerGet(controller c, resource r);

#endif
