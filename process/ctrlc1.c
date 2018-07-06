#include<signal.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

//SIGINT에 대응하는 핸들러

void sigHandler(int sig)
{
	static int count=0;

	switch(sig)
	{
	case SIGINT:
	printf("OUCH! - i got signal %d\n",sig);
	//(void) signal(SIGINT, SIG_DFL);
	count++;
	if(count==5)
	exit(0);
	break;
	case SIGQUIT:
	printf("OUCH! - i got signal SIGQUIT %d\n",sig);
	(void) signal(SIGQUIT, SIG_DFL);
	break;
	}
}

int main()
{
	signal(SIGINT,sigHandler);
	signal(SIGQUIT,sigHandler);

	while(1)
	{
		printf("Hello World!\n");//fflush(stdout); 버퍼에 있는 것들을 우선적으로 내보낸다.//write(1,"Hello world\n");
		sleep(1);
	}
}
