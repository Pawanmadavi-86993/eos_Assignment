#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipe1[2], pipe2[2];
    pid_t pid;
    int num1, num2, sum;

    if (pipe(pipe1) == -1) {
        perror("pipe1 creation failed");
        exit(1);
    }
    if (pipe(pipe2) == -1) {
        perror("pipe2 creation failed");
        exit(1);
    }

    pid = fork();
    
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        close(pipe1[0]);
        close(pipe2[1]);
        num1 = 10;
        num2 = 20;
        write(pipe1[1], &num1, sizeof(num1));
        write(pipe1[1], &num2, sizeof(num2));

        close(pipe1[1]);

        read(pipe2[0], &sum, sizeof(sum));
        
        printf("Child: The sum of %d and %d is %d\n", num1, num2, sum);

        close(pipe2[0]);

        exit(0);
    } else {
        close(pipe1[1]);
        close(pipe2[0]);

        read(pipe1[0], &num1, sizeof(num1));
        read(pipe1[0], &num2, sizeof(num2));

        sum = num1 + num2;

        write(pipe2[1], &sum, sizeof(sum));
        close(pipe1[0]);
        close(pipe2[1]);

        wait(NULL);

        exit(0);
    }

    return 0;
}


