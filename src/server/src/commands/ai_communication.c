/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-vincent.shao
** File description:
** ai_communication
*/

#include "server.h"
#include "macro.h"
#include "game_macro.h"

int do_ai_communication(char *buffer, node_t *client, server_t *server)
{
    if (!client->client.is_conn)
        if (do_ai_first_connect(buffer, client, &server->data) == SUCCESS)
            return SUCCESS;
    printf("From team\n");
    return FAILURE;
}