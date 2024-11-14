#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>

int main()
{
	int ret,err,s;
	printf("parent\n");
	ret = fork();
	if(ret == 0)
	{
		char *args[] = {"gcc circle.c"}
	}

	return 0;
}
