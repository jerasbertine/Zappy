/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-vincent.shao
** File description:
** init
*/

#include "server.h"
#include "macro.h"

static int create_server(sock_addrs_t *addrs, int port)
{
    addrs->server.sin_family = AF_INET;
    addrs->server.sin_port = htons(port);
    addrs->server.sin_addr.s_addr = INADDR_ANY;
    addrs->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (addrs->socket_fd < 0)
        return FAILURE;
    addrs->name = bind(addrs->socket_fd,
    (const struct sockaddr *) &addrs->server, sizeof(addrs->server));
    if (addrs->name < 0)
        return FAILURE;
    addrs->status = listen(addrs->socket_fd, MAX_CONNECTIONS);
    if (addrs->status < 0)
        return FAILURE;
    FD_ZERO(&addrs->rfds);
    return SUCCESS;
}

static int init_clients(server_t *server)
{
    for (int i = 0; i < MAX_CONNECTIONS; i++) {
        server->clients[i].fd = -1;
    }
    return SUCCESS;
}

int init_server(server_t *server, int port)
{
    if (create_server(&server->addrs, port) == FAILURE)
        return FAILURE;
    if (init_clients(server) == FAILURE)
        return FAILURE;
    server->clients[0].fd = server->addrs.socket_fd;
    return SUCCESS;
}
