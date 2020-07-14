#ifndef _SOCKET_H
#define _SOCKET_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h> 
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

int read_socket (int fd, char *data, int length);

int write_socket (int fd, char *data, int length);

#endif
