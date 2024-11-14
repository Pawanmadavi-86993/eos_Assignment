#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

// Signal handler for SIGCHLD to prevent zombie processes
void handle_sigchld(int sig) {
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

// Signal handler for SIGINT (Ctrl+C)
void handle_sigint(int sig) {
    printf("\nCaught signal %d (SIGINT). Press 'exit' to terminate the shell.\ncmd> ");
    fflush(stdout); // Ensure the prompt is printed immediately
}

int main() {
    char cmd[512], *ptr, *args[32];
    int i, ret, err, s;

    // Setup signal handlers
    signal(SIGCHLD, handle_sigchld);
    signal(SIGINT, handle_sigint);

    while (1) {
        // Input a command string from user, split it into multiple tokens using strtok() and
        // store their addresses into array of char*.
        printf("cmd> ");
        fgets(cmd, sizeof(cmd), stdin); // Use fgets instead of gets for safety
        cmd[strcspn(cmd, "\n")] = '\0'; // Remove newline character from fgets

        i = 0;
        ptr = strtok(cmd, " ");
        args[i] = ptr;  i++;
        do {
            ptr = strtok(NULL, " ");
            args[i] = ptr;  i++;
        } while (ptr != NULL);

        // Check for asynchronous execution
        int async = 0;
        if (i > 1 && strcmp(args[i - 2], "&") == 0) {
            async = 1;
            args[i - 2] = NULL; // Remove '&' from arguments
        }

        // Implement logic for internal commands
        if (strcmp(args[0], "exit") == 0)
            _exit(0);
        else if (strcmp(args[0], "cd") == 0)
            chdir(args[1]);
        else {
            // fork() + execvp() to execute the external command with args and call wait() to avoid zombie
            ret = fork();
            if (ret == 0) {
                err = execvp(args[0], args);
                if (err < 0) {
                    perror("exec() failed");
                    _exit(1);
                }
            }
            else {
                if (!async) { // Only wait for the child if not asynchronous
                    waitpid(ret, &s, 0);
                }
            }
        }
    }
    return 0;
}
