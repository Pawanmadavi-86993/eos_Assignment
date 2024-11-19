#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int fd, ret1,ret2,ret3,num3,num4,result;
    
    fd = open("/tmp/myfifo", O_RDONLY);
    if(fd < 0) {
        perror("open() failed");
        _exit(1);
    }
    printf("p2: waiting for message...\n");
    ret1 = read(fd,&num3, sizeof(num3));
    ret2 = read(fd,&num4, sizeof(num4));
    printf("p2: message recvd: %d and %d\n",num3, num4);
    fd = open("/tmp/myfifo", O_WRONLY);
    if(fd < 0) {
        perror("open() failed");
        _exit(1);
    }
    result=num3+num4;
    ret3 = write(fd, &result, sizeof(result));
    printf("p2: message sent\n");
    close(fd);
    return 0;
}
