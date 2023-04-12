#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define BUF_SIZE 1024
#define MAX 10
#define MESG_KEY 1234
#define PY_TO_C 2
#define False 0
#define True 1

// structure for message queue
struct mesg_buffer
{
    long mesg_type;
    char mesg_text[100];
} message;

char* recv_from_python()
{

    int msgid;

    // ftok to generate unique key

    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(MESG_KEY, 0666 | IPC_CREAT);
    message.mesg_type = PY_TO_C;

    int length;
    // msgsnd to send message
    if (msgrcv(msgid, &message, sizeof(message), message.mesg_type, 0) == -1)
    {
        perror("Msgrcv failed");
    }
    // display the message
    char *buffer = (char *)calloc(BUF_SIZE, sizeof(char));
    bzero(buffer, BUF_SIZE);
    strncpy(buffer, message.mesg_text, sizeof(message.mesg_text));

    return buffer;
}

int main()
{
    char *buffer = (char *)calloc(BUF_SIZE, sizeof(char));
    bzero(buffer, BUF_SIZE);
    while (True)
    {
        buffer = recv_from_python();
        printf("Data send is : %s \n", message.mesg_text);
    }
}
