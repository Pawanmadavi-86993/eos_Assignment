#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int fd,ret1,ret2,ret3,num1,num2,result;
    
    fd = open("/tmp/myfifo", O_WRONLY);
    if(fd < 0) {
        perror("open() failed");
        _exit(1);
    }
    printf("p1: enter a message: ");
    scanf("%d%d",&num1,&num2);
    ret1 = write(fd, &num1, sizeof(num1));
    ret2 = write(fd, &num2, sizeof(num2));
    printf("p1: message sent: %d and %d\n",num1,num2);
    printf("waiting for result\n");
    fd = open("/tmp/myfifo", O_RDONLY);
    if(fd < 0) {
        perror("open() failed");
        _exit(1);
    }
    ret3 = read(fd,&result, sizeof(result));
    printf("Result : %d\n",result);
    close(fd);
    return 0;
}
