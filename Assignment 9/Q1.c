#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MSG_KEY 1234

struct msg_buffer {
    long msg_type;
    int num1; 
    int num2;         
    int sum;          
};

int main() {
    pid_t pid;
    int msgid;
    struct msg_buffer message;

    msgid = msgget(MSG_KEY, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        message.msg_type = 1;
        message.num1 = 10;
        message.num2 = 20;
        if (msgsnd(msgid, &message, sizeof(message) - sizeof(long), 0) == -1) {
            perror("msgsnd failed");
            exit(1);
        }

        if (msgrcv(msgid, &message, sizeof(message) - sizeof(long), 2, 0) == -1) {
            perror("msgrcv failed");
            exit(1);
        }


        printf("Child: The sum of %d and %d is %d\n", message.num1, message.num2, message.sum);


        exit(0);
    }
    else {
        if (msgrcv(msgid, &message, sizeof(message) - sizeof(long), 1, 0) == -1) {
            perror("msgrcv failed");
            exit(1);
        }

        message.sum = message.num1 + message.num2;

        message.msg_type = 2;

        if (msgsnd(msgid, &message, sizeof(message) - sizeof(long), 0) == -1) {
            perror("msgsnd failed");
            exit(1);
        }

        wait(NULL);

        msgctl(msgid, IPC_RMID, NULL);

        exit(0);
    }

    return 0;
}

