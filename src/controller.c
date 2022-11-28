#include "controller.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>


controller controllerConnect(char *addr, int port)
{
    controller c;
    struct sockaddr_in address;

    c.status = CSTAT_OK;

    if ((c.socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        c.status |= CSTAT_CREATION_ERROR;
        return c;
    }

    address.sin_family = AF_INET;
    address.sin_port = (uint32_t) port;

    if (inet_pton(AF_INET, addr, &address.sin_addr) <= 0)
    {
        c.status |= CSTAT_INVALID_ADDRESS;
        return c;
    }

    if ((c.client = connect(c.socket, (struct sockaddr *) &address, sizeof(address))) < 0)
    {
        c.status |= CSTAT_CONNECTION_ERROR;
        return c;
    }

    return c;
}

int controllerGet(controller c, resource r)
{
    char fetch = (char) r;
    send(c.socket, &fetch, 1);

    if (r >= LeverLX)
    {
        char buffer[2];
        read(c.socket, buffer, 2);

        int value;
        value  = (int) buffer[1] + 127;
        value *= (!buffer[0] - buffer[0]);

        return value;
    }

    char value;
    read(c.socket, &value, 1);

    return (int) value;
}
