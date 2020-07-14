#include "Client.h"

int main()
{
	int error;
	int len;
	pthread_t id_thread;
	int num;
	key_t key1;
	key_t key2;
	int id_msg_queue1;
	int id_msg_queue2;
	my_msg msg1;
	my_msg msg2;
	int first = 1;
	char name[200];
	char message[200];

	printf ("%s", KWHT);
	system("clear");

	sock = open_inet_connection ();

	error = read_socket (sock, (char *)&num, sizeof(int));

	if (error < 1)
	{
		printf ("Connection has been closed\n");
		exit(-1);
	}

	key1 = ftok ("/bin/ls",23);
	if (key1 == (key_t)-1)
	{
		printf("Error getting key for the messages queue\n");
		exit(-1);
	}

	id_msg_queue1 = msgget (key1, 0777 | IPC_CREAT);
	if (id_msg_queue1 == -1)
	{
		printf("Error getting identifier for the message queue\n");
		exit (-1);
	}

	printf("Client started\n");

	srand(time(NULL));
	num = rand();

	msg1.id_msg = 1;

	memset(msg1.msg, '\0', sizeof(msg1.msg));
	sprintf(msg1.msg,"%d",num);

	msgsnd (id_msg_queue1, (struct msgbuf *)&msg1, sizeof(msg1.msg), 0);

	key2 = ftok ("/bin/ls",num);
	if (key2 == (key_t)-1)
	{
		printf("Error getting key for the messages queue\n");
		exit(-1);
	}

	id_msg_queue2 = msgget (key2, 0777 | IPC_CREAT);
	if (id_msg_queue2 == -1)
	{
		printf("Error getting identifier for the message queue\n");
		exit (-1);
	}

	printf("Client ready\n");

	error = pthread_create (&id_thread, NULL, read_from_socket, NULL);

	while(1)
	{
			memset(msg2.msg, '\0', sizeof(msg2.msg));

			msgrcv (id_msg_queue2, (struct msgbuf *)&msg2,
				sizeof(msg2.msg), 1, 0);

			if (first == 1)
			{
				memset(name, '\0', sizeof(name));
				strcpy(name, msg2.msg);
				name[strlen(name)-1]='\0';
				printf ("%sYour name: %s\n", KWHT, name);
				first = 0;
			}else
			{
				printf("%sYou: %s", KGRN,msg2.msg);
				memset(message,'\0', sizeof(message));
				strcat(message,name);
				strcat(message,": ");
				strcat(message,msg2.msg);
				len = strlen(message);
				write_socket(sock, (char *)&len, sizeof(int)); 
				write_socket(sock, (char *)message, len);
			}
	}

	close(sock);

	return 0;
}

void *read_from_socket (void *param)
{
	int len =0;
	char buffer[200];

	while(1)
	{
			len = 0;

			if (read_socket (sock, (char *)&len, sizeof(int))>0)
			{
				memset(buffer, '\0', sizeof(buffer));

				if (read_socket (sock, (char *)buffer, len)>0)
				{
					printf ("%s",buffer);
				}else
				{
					printf ("Connection has been closed\n");
					exit(-1);
				}
			}else
			{
				printf ("Connection has been closed\n");
				exit(-1);
			}
	}
}
