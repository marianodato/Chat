#include "Client_Socket.h"

int open_inet_connection ()
{
	struct sockaddr_in address;
	int descriptor;

	address.sin_family = AF_INET;
	address.sin_port = htons(15556);
	inet_pton(AF_INET, "192.168.1.249", &address.sin_addr);
	
	descriptor = socket (AF_INET, SOCK_STREAM, 0);
	if (descriptor == -1)
		return -1;

	if (connect (
			descriptor, 
			(struct sockaddr *)&address, 
			sizeof (address)) == -1)
	{
		return -1;
	}

	return descriptor;
}
