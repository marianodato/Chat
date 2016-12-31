CC = gcc
CFLAGS  = -g -Wall
SERVER = src/Server
CLIENT = src/Client
CLIENT_MESSAGES = src/Client_Messages

all: $(SERVER) $(CLIENT) $(CLIENT_MESSAGES)

$(SERVER):	src/Socket.c src/Server_Socket.c $(SERVER).c
	$(CC) $(CFLAGS) -o $(SERVER) src/Socket.c src/Server_Socket.c $(SERVER).c

$(CLIENT):	src/Socket.c src/Client_Socket.c $(CLIENT).c
	$(CC) $(CFLAGS) -o $(CLIENT) -pthread src/Socket.c src/Client_Socket.c $(CLIENT).c

$(CLIENT_MESSAGES):	$(CLIENT_MESSAGES).c
	$(CC) $(CFLAGS) -o $(CLIENT_MESSAGES) $(CLIENT_MESSAGES).c

clean:
	$(RM) $(SERVER) $(CLIENT) $(CLIENT_MESSAGES)