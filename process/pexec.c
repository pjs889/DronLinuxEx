#include<stdio.h>
#include<unistd.h>
#include <sys/types.h> 
#include <sys/wait.h> 
#include <stdlib.h> 
#include <signal.h> 

void pr_exit(int status);

int main()
{
	pid_t pid;
	int status;
	pid=fork();

	if(pid<0)
	{
		printf("Error:fork()\n");
		return -1;
	}

	else if( pid==0)
	{
		printf("Child\n");
		execlp( "./pexec1", "pexec1",(char*)0);
		//execl("/home/park/DronLinuxEx/process/pexec1",\
		"/home/park/DronLinuxEx/process/pexec1",NULL);
		return -1;
	}
         // 부모 프로세스인 경우 실행 
 	else 
 	{ 
 		printf("Parent: Hi!!!\n"); 
 		printf("Child PID : %d\n",pid); 
 	} 
 
 
  	pid = wait(&status); 
  	printf("EXIT:Child pid=%d\n",pid); 
   
    	pr_exit(status); 
    	return 0; 


}


void pr_exit(int status) 
{   
 	// 자식 프로세스가 정상적으로 종료했다면   
 	if (WIFEXITED(status)) 
 	        printf("normal termination, exit status = %d\n",   WEXITSTATUS(status)); 
 	// 자식 프로세스가 시그널에 의해 종료했다면 
 	else if (WIFSIGNALED(status)) 
 	        printf("abnormal termination, signal number = %d%s\n",\
		WTERMSIG(status),   WCOREDUMP(status) ? "(core file generated)" : "");     
 	// 자식 프로세스가 정지된 상태라면 
 	else if (WIFSTOPPED(status))         
 		printf("child stopped, signal number = %d\n",   WSTOPSIG(status));  
 }  

