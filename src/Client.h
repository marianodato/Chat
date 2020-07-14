#ifndef _CLIENT_H
#define _CLIENT_H

#include "Socket.h"
#include "Client_Socket.h"
#include "Utils.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>

void *read_from_socket (void *param);

int sock;

#endif

