#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int i, ret, s,count=0;
    printf("program starts!\n");
	for(i=0;i<5;i++)
	{
    ret = fork();
    if(ret == 0) {
		
        for(int j=1; j<=5; j++) {
            printf("child - %d count %d\n", i,j);
            sleep(1);
        }
		_exit(0);
    }
	}
    for(i=1; i<=5; i++) {        
        waitpid(ret,&s,0); 
        printf("exit status: %d\n",WEXITSTATUS(s));
        }
    
    return 0;
}
