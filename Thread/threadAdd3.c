#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include<time.h>
#include<sys/time.h>  //gettimeofday()함수에서 사용
#include<stdlib.h>


struct Num
{
	int start;
	int end;
};

void* add_func(void* data)
{
	struct Num num1;
	int i;
	long result=0;

	num1 = *((struct Num*)data);

	printf("num1.start=%d\n", num1.start);
	printf("num1.end=%d\n", num1.end);

	for(i=num1.start;i<=num1.end;i++)
	{
		result += i;
	}
												
													return (void*)(result);
}

int main(int argc, char *argv[])
{
	pthread_t p_thread;
	struct Num num1;
	long sum1;
	long result;
	struct timeval starttime,endtime;
	int i;

	num1.start = 1;
	num1.end = (atoi(argv[1]));
	
	gettimeofday(&starttime,NULL);
	if(pthread_create(&p_thread, NULL, add_func, (void*)&num1)<0)
	{
		perror("thread1 create error:");
		exit(1);
	}

 	pthread_join(p_thread,(void**)&sum1);

	printf("sum1: %ld\n", sum1);
	gettimeofday(&endtime,NULL);
	
	printf("before :%ld/%ld\n",starttime.tv_sec,starttime.tv_usec);
	printf("after :%ld/%ld\n",endtime.tv_sec,endtime.tv_usec);
	printf("running time: %ld\n",endtime.tv_usec-starttime.tv_usec);
	return 0;
}
