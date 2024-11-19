#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<arpa/inet.h>

#define SERV_ADDR "127.0.0.1"
#define SERV_PORT 2809

int main()
{
    int ret, serv_fd, cli_fd,num1,num2,result;
    struct sockaddr_in serv_addr,cli_addr;
    socklen_t socklen = sizeof(cli_addr);
    
    //1.create server socket
    serv_fd = socket(AF_INET,SOCK_STREAM,0);
    //2.bind the address
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    inet_aton(SERV_ADDR, &serv_addr.sin_addr);
    ret = bind(serv_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    //3. listen to server socket
    listen(serv_fd, 5);
    //6. accept client connection
    cli_fd = accept(serv_fd, (struct sockaddr*)&cli_addr, &socklen);
    
        //8. read data from client
        read(cli_fd, &num1, sizeof(num1));
        read(cli_fd, &num2, sizeof(num2));
        printf("data received from client: %d and %d\n",num1,num2);
        //9. send data to client
        result=num1+num2;
        printf("server: data sent\n");
        write(cli_fd, &result, sizeof(result));
    
    //12. close client socket
    close(cli_fd);
    //13. shutdown server socket
    shutdown(serv_fd, SHUT_RDWR);
    return 0;
}
