#include "controller.h"

#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

#define BYTE 0xff

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
    address.sin_port = htons(port);

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

int controllerGet(controller c, char input_resource_id)
{
    char fetch[2];
    int value;

    fetch[0] = CRES_GET;
    fetch[1] = input_resource_id;

    write(c.socket, fetch, 2);
    read(c.socket, &value, 4);

    return value;
}

void controllerSet(controller c, char output_resource_id, int value)
{
    char fetch[2];

    fetch[0] = CRES_SET;
    fetch[1] = output_resource_id;

    write(c.socket, fetch, 2);
    write(c.socket, &value, 4);
}

void controllerDisconnect(controller c)
{
	close(c.socket);
	close(c.client);
}
