#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

void sigHandler(int sig)
{
	static int cnt=1;
	printf("killtest : i got signal %d\n",sig);
	if(cnt==5)
	exit(0);
	cnt++;
	//(void)signal(SIGINT,SIG_DFL);
}

int main(void)
{
	signal(SIGINT,sigHandler);
	while(1)
	{
		printf("Hello World\n");
		sleep(1);
	}
}
