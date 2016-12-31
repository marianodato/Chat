# Chat 
A simple TCP based console chat server written in C.

## Project Structure

The make command generates 3 executable files:

- Server: Starts the chat server. In this terminal you can see when new clients connect/disconnect to the server.
- Client: Starts a new client. In this terminal you can see messages sent by other clients.
- Client_Messages: In this terminal you can write and send messages to other clients.

## Considerations

- You should run the Server program first and only once.
- You can run the Client program as many times as clients you want to have.
- For each Client program you run you should also run one Client_Messages program in the same computer.
- You can run the all the executables in the same computer, or run the Server program in one computer and the Client programs in another one. You can also run all the Client programs in different computers.
- All computers must be inside the same LAN.

## Build and Run Instructions

1. Open a terminal.
2. In your server PC open /etc/services: `sudo nano /etc/services` 
3. Add a new TCP network service. Create a row indicating service name, port, type of protocol, a brief description and save changes. For example: `test-sockets  15556/tcp  #Test for TCP chat application`
4. Clone repository: `git clone https://github.com/marianodato/Chat.git`
5. Change to project directory: `cd Chat`
6. Change the ip address and port in Client_Socket.c with your server pc ip and the port number you added in /etc/services. 
7. Change the service name in Server.c with the service name you added in /etc/services.
8. Change MAX_CLIENTS variable in Server.h with the maximum amount of clients you want the server to support.
9. Run makefile: `make`
10. Run the Server program: `./Server`
11. In the same or in other computers run the clients programs: Both `./Client` and `./Client_Messages` in the same PC.
