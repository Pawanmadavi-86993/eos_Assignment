#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>

#define SERV_ADDR "127.0.0.1"
#define SERV_PORT 2809

int main() 
{
    int ret,cli_fd,num1,num2,result;
    struct sockaddr_in serv_addr;
    
    //4. create client socket
    cli_fd = socket(AF_INET, SOCK_STREAM, 0);
    //5. connect to server socket
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    inet_aton(SERV_ADDR, &serv_addr.sin_addr);
    ret = connect(cli_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    
        //7. send data to server
        printf("client:enter 2 numbers: ");
        scanf("%d%d",&num1,&num2);
        write(cli_fd, &num1, sizeof(num1));
        write(cli_fd, &num2, sizeof(num2));
        //10. read data from server
        read(cli_fd, &result, sizeof(result));
        printf("server: %d\n", result);
    
    //11. close client socket
    close(cli_fd);
    return 0;
}


