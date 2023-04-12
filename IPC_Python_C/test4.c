#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define  BUFF_SIZE  16
#define  C_TO_PY    2
#define  KEY        1234

typedef struct {
	long  data_type;
	char  data_buff[BUFF_SIZE];
} t_data;

int main(void)
{
	int      msqid;
	t_data   data;

	if (-1 == (msqid = msgget((key_t)KEY, IPC_CREAT | 0666)))
	{
		perror("msgget() failed");
		exit(1);
	}

    data.data_type = C_TO_PY;
    sprintf(data.data_buff, "Siu!");
    if (-1 == msgsnd(msqid, &data, sizeof(t_data) - sizeof(long), 0))
	{
		perror("msgsnd() failed");
		exit(1);
	}
}