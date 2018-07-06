#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<signal.h>

//이 함수는 프로세스상에서 delay를 한다.
//sleep은 main이  프로세스 되지 않고 delay한다.
//int delay_func(int delay)
//{
//	int i,result=0;
//	for(i=0;i<delay;i++)
//	{
//		result++;
//	}
//
//}

 void pr_exit(int status)
 {
            //자식프로세스가 정상적으로 종료됬다면  
        if(WIFEXITED(status))
                   printf("normal termination = %d\n",WEXITSTATUS(status));
            //자식프로세스가 시그널에 의해 종료됬다면
         else if (WIFSIGNALED(status))
		 printf("abnormal termination, signal number = %d%s\n",\
		 WTERMSIG(status), WCOREDUMP(status) ? "(core file generated)": "");
	 else if (WIFSTOPPED(status))
            printf("child stopped, signal number = %d\n", WSTOPSIG(status));
 }




int main(void)
{
	int status;
	pid_t pid;
	
	//자신의 PID값을 확인한다.
	printf("Process ID = %d\n",getpid());
	//부모의 PID값을 확인한다.
	printf("Parent Process ID = %d\n",getppid());
	
	pid = fork();
	
	//fork()를 실행했는데 정상적으로 자식프로세스가 생성되지 않은 경우
	if(pid<0)
	{
		printf("Error: fork()\n");
		return -1;
	}
	//자식 프로세스인 경우 실행
	else if(pid==0)
	{
		printf("Child: Hello!!\n");
		raise(SIGINT);
		//exit(11);
	}
	//부모 프로세스인 경우 실행
	else
	{
		printf("Parent: hi!!\n");
		printf("Child PID : %d\n",pid);
	}

	pid = wait(&status);
	printf("EXIT:Child pid=%d\n",pid);

	//sleep(10);
	//delay_func(10000);

	pr_exit(status);
	return 0;

}



