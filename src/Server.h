#ifndef _SERVER_H
#define _SERVER_H

#include "Socket.h"
#include "Server_Socket.h"
#include "Utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_CLIENTS 5

void new_client (int server, int *clients, int *clients_number);

int give_maximum (int *table, int n);

void compact_keys (int *table, int *n);

#endif
