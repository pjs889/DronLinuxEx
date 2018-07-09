#include<stdio.h>
#include<signal.h>
#include<stdlib.h>

volatile sig_atomic_t quitflag; //set nonzero by signal handler

//one signal handler for SIGINT and SIGQUIT
static void sig_int(int signo)
{
	if(signo==SIGINT)
		printf("\ninterrupt\n");
		//추가한 SIGINT와 함께 quitflag=1을 넣어주면 SIGINT로 서스펜드 해제가능
	else if(signo==SIGQUIT)
		quitflag=1;//set flag for main loop
}

int main(void)
{
	sigset_t newmask,oldmask,zeromask;

	if(signal(SIGINT,sig_int)==SIG_ERR)
		perror("signal(SIGINT) error");
	if(signal(SIGQUIT,sig_int)==SIG_ERR)
		perror("signal(SIGQUIT) error");

	sigemptyset(&zeromask);
	sigemptyset(&newmask);
	sigaddset(&newmask,SIGQUIT);//SIGINT로 지정,추가하하면 SIGINT로 suspend풀기가능

	//block SIGQUIT and save current signal mask.
	if(sigprocmask(SIG_BLOCK,&newmask,&oldmask)<0)
		perror("SIG_BLOCK error");

	while(quitflag==0)
		sigsuspend(&zeromask);//sigsuspend는 반대로 생각

	//SIGQUIT has been caught and is now blcoked ; do whatever
	quitflag=0;

	//reset signal mask which unblocks SIGQUIT.
	if(sigprocmask(SIG_SETMASK,&oldmask,NULL)<0)
		perror("SIG_SETMASK error");
	//abort();//비정상적인 종료
	exit(0);
}
