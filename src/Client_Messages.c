#include "Client_Messages.h"

int main()
{
	key_t key1;
	key_t key2;
	int id_msg_queue1;
	int id_msg_queue2;
	my_msg msg1;
	my_msg msg2;
	int num = 23;
	int first = 1;
	int ret = 0;

	printf ("%s", KWHT);
	system("clear");

	key1 = ftok ("/bin/ls", num);
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

	printf("Message started\n");

	memset(msg1.msg, '\0', sizeof(msg1.msg));

	msgrcv (id_msg_queue1, (struct msgbuf *)&msg1, sizeof(msg1.msg), 1, 0);

	ret = atoi(msg1.msg);

	key2 = ftok ("/bin/ls", ret);
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

	printf("Message ready\n");

	msg2.id_msg = 1;

	while(1)
	{
		memset(msg2.msg, '\0', sizeof(msg2.msg));
		system("clear");

		if (first == 1)
		{
			
			printf("Type your name: ");
			fgets(msg2.msg, sizeof(msg2.msg), stdin);
			first = 0;

		}else
		{
			printf("Type your message: ");
			fgets(msg2.msg, sizeof(msg2.msg), stdin);
		}

		msgsnd (id_msg_queue2, (struct msgbuf *)&msg2, 
				sizeof(msg2.msg), 0);
	}

	return 0;
}

