#ifndef CONTROLLER_H
#define CONTROLLER_H

#define CDEF_PORT    8989
#define CDEF_ADDRESS "127.0.0.7"

#define CSTAT_OK                0b000
#define CSTAT_CREATION_ERROR    0b001
#define CSTAT_INVALID_ADDRESS   0b010
#define CSTAT_CONNECTION_ERROR  0b100

#define CRES_GET 0
#define CRES_SET 1

typedef struct Controller
{
        int socket, client, status;
}
controller;

controller controllerConnect(char *addr, int port);
int controllerGet(controller c, char input_resource_id);
void controllerSet(controller c, char output_resource_id, int value);
void controllerDisconnect(controller c);

#endif
