#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int glob=6; //external variable in initialized data
char buf[]="a write to stdout\n";

int main(void){
	int var; //automatic variable on the stack
	pid_t pid;
	var=88;

	if(write(STDOUT_FILENO,buf,sizeof(buf)-1) !=sizeof(buf-1))
		perror("write error");//STDOUT_FILENO=1이므로 1로 적어도 됨.
	
	printf("before fork\n");  //we don't flush stdout

	if((pid=fork())==0)
	{
		//child
		glob++;    //modify variables
		var++;
	}
	else 
	{	//parent
		sleep(2);
	}

	printf("pid=%d,glob=%d,var=%d\n",getpid(),glob,var);
	exit(0);
//부모에게서 복사된 변수들은 자식 프로세서에서는 전혀 다른 변수로 인식해야한다.
}
