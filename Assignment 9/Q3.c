#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    int pipefd[2];
    int bufsize;

    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    bufsize = fcntl(pipefd[0], F_GETPIPE_SZ);
    if (bufsize == -1) {
        perror("fcntl failed");
        exit(EXIT_FAILURE);
    }

    printf("The size of the pipe buffer is: %d bytes\n", bufsize);

    close(pipefd[0]);
    close(pipefd[1]);

    return 0;
}

