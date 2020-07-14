#ifndef _SERVER_SOCKET_H
#define _SERVER_SOCKET_H

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

int open_inet_socket (char *service);

int accept_client_connection (int descriptor);

#endif
