#include "controller.h"

int controllerConnect(char *addr, int port)
{
    int ctl_fd, client_fd;
    struct sockaddr_in serv_addr;

    if ((ctl_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) return -1;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = (uint32_t) port;

    inet_pton(AF_INET, addr, &serv_addr.sin_addr);

}