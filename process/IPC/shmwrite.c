#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>

#include "shm.h"

int main(void)
{
	void *shared_mem=(void*)0; //NULL 포인터로 초기화
	int shmid;
	int *shmaddr;//실제 데이터 영역(공유메모리)을 접근하기 위한 포인터
	int i;

	// step1. shmget
	shmid=shmget(KEY_VALUE,SHMSIZE,0666|IPC_CREAT);
	if(shmid==-1)
	{
		fprintf(stderr,"shmget failed\n");
		exit(EXIT_FAILURE);
	}

	// step2. shmat
	shared_mem=shmat(shmid,(void*)0,0);//공유메모리 접근하는 주소값 알아냄
	if(shared_mem==(void*)-1)
	{
		fprintf(stderr,"shmat failed\n");
		exit(EXIT_FAILURE);
	}
	
	// step3. shared memory access
	shmaddr=(int*)shared_mem;//void타입 주소를 int형으로 바꿔준다

	for(i=0;i<dataCount;i++)
	{
		*(shmaddr+i)=i+1;
		printf("shmaddr:%p, data:%d\n",shmaddr+i,*(shmaddr+i));
		
	}

	// step4. shmdt
	if(shmdt(shared_mem)==-1)
	{
		fprintf(stderr,"shmdt failed\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);

}

