CC = gcc
CFLAGS  = -g -Wall
SERVER = src/Server
CLIENT = src/Client
MESSAGE = src/Client_Messages

all: $(SERVER) $(CLIENT) $(MESSAGE)

$(SERVER):	src/Socket.c src/Server_Socket.c $(SERVER).c
	$(CC) $(CFLAGS) -o $(SERVER) src/Socket.c src/Server_Socket.c $(SERVER).c

$(CLIENT):	src/Socket.c src/Client_Socket.c $(CLIENT).c
	$(CC) $(CFLAGS) -o $(CLIENT) -pthread src/Socket.c src/Client_Socket.c $(CLIENT).c

$(MESSAGE):	$(MESSAGE).c
	$(CC) $(CFLAGS) -o $(MESSAGE) $(MESSAGE).c

clean:
	$(RM) $(SERVER) $(CLIENT) $(MESSAGE)