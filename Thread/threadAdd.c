#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

struct Num{
	int start;
	int end;
};

void*t_function(void*data)
{
	int i;
	struct Num num;
	num=*((struct Num*)data);
	int sum=0;
			
	for(i=num.start;i<=num.end;i++)
	{
		sum=sum+i;
	}

	sleep(2);
	return (void*)(sum);
}

int main()
{
	pthread_t p_thread[2];
	int err;
	int sum1,sum2;
	struct Num num[2];
	num[0].start=1;
	num[0].end=5000;
	num[1].start=5001;
	num[1].end=10000;

	if((err=pthread_create(&p_thread[0],NULL,t_function,(void*)&num[0]))<0)	
	{
		perror("thread create error:");
		exit(1);
	}

	if((err=pthread_create(&p_thread[1],NULL,t_function,(void*)&num[1]))<0)
	{
		perror("thread create error:");
		exit(2);
	}

	pthread_join(p_thread[0],(void**)&sum1);
	printf("sum1:%d\n",sum1);
	pthread_join(p_thread[1],(void**)&sum2);
	printf("sum2:%d\n",sum2);

	//printf("after pthread_create()glob_var=%d\n",glob_var);
	return 0;
}
