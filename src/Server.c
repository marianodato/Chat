#include "Server.h"

int main()
{
	int server_socket;
	int client_socket[MAX_CLIENTS];
	int clients_number = 0;
	fd_set read_descriptors;
	int len;
	int max;
	int i;
	char buffer[200];
	char msg[200];
	int j = 0;

	printf ("%s", KWHT);
	system("clear");

	server_socket = open_inet_socket ("test-sockets");
	if (server_socket == -1)
	{
		perror ("Error starting server\n");
		exit (-1);
	}

	printf ("Server started\n");

	while (1)
	{
		compact_keys (client_socket, &clients_number);
		
		FD_ZERO (&read_descriptors);

		FD_SET (server_socket, &read_descriptors);

		for (i=0; i<clients_number; i++)
			FD_SET (client_socket[i], &read_descriptors);

		max = give_maximum (client_socket, clients_number);
		
		if (max < server_socket)
			max = server_socket;

		select (max + 1, &read_descriptors, NULL, NULL, NULL);

		for (i=0; i<clients_number; i++)
		{
			if (FD_ISSET (client_socket[i], &read_descriptors))
			{
				if ((read_socket (client_socket[i], (char *)&len, sizeof(int)) > 0))
				{
					memset(buffer, '\0', sizeof(buffer));
					if ((read_socket (client_socket[i], (char *) buffer, len) > 0))
					{

						memset(msg,'\0',sizeof(msg));

						if(i==0)
							strcat(msg,KRED);
						else if (i==1)
							strcat(msg,KYEL);
						else if (i==2)
							strcat(msg,KBLU);
						else if (i==3)
							strcat(msg,KMAG);
						else if (i==4)
							strcat(msg,KCYN);
						else
							strcat(msg,KRED);
						
						strcat(msg,buffer);
						len = strlen(msg);

						for (j=0;j<clients_number;j++)
						{
							if (i!=j)
							{
								write_socket(client_socket[j], (char *)&len, sizeof(int)); 
								write_socket(client_socket[j], (char *)msg, len);
							}
						}

					}else
					{
						printf ("User %d has closed connection\n", i+1);
						client_socket[i] = -1;
					}
				}else
				{
					printf ("User %d has closed connection\n", i+1);
					client_socket[i] = -1;
				}
			}
		}

		if (FD_ISSET (server_socket, &read_descriptors))
			new_client (server_socket, client_socket, &clients_number);
	}

	return 0;
}

void new_client (int server, int *clients, int *clients_number)
{
	clients[*clients_number] = accept_client_connection (server);
	(*clients_number)++;

	if ((*clients_number) > MAX_CLIENTS)
	{
		close (clients[(*clients_number) -1]);
		(*clients_number)--;
		return;
	}
		
	write_socket (clients[(*clients_number)-1], (char *)clients_number, sizeof(int));

	printf ("User %d has entered\n", *clients_number);

	return;
}

int give_maximum (int *table, int n)
{
	int i;
	int max;

	if ((table == NULL) || (n<1))
		return 0;
		
	max = table[0];
	for (i=0; i<n; i++)
		if (table[i] > max)
			max = table[i];

	return max;
}

void compact_keys (int *table, int *n)
{
	int i,j;

	if ((table == NULL) || ((*n) == 0))
		return;

	j=0;
	for (i=0; i<(*n); i++)
	{
		if (table[i] != -1)
		{
			table[j] = table[i];
			j++;
		}
	}
	
	*n = j;
}
