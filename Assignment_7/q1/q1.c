#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<signal.h>
#include<string.h>

int main()
{
	pid_t pid;
	int sig,ret;
	printf("Enter the Signal number and process id: \n");
	scanf("%d%d",&pid,&sig);
	ret = kill(pid,sig);
	if(ret == -1)
	{
		printf("kill failed\n");
		exit(1);
	}

	return 0;
}

