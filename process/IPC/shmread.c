#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
#include "shm.h"

int main(void)
{
	void *shared_mem=(void*)0;
	int shmid;
	int *shmaddr;
	int i;

	// step1. shmget
	shmid=shmget(KEY_VALUE,SHMSIZE,0666|IPC_CREAT);
	if(shmid==-1)
	{
		fprintf(stderr,"shmget failed\n");
		exit(EXIT_FAILURE);
	}

	// step2.shmat
	shared_mem=shmat(shmid,(void*)0,0);
	if(shared_mem==(void*)-1)
	{
		fprintf(stderr,"shmat failed\n");
		exit(EXIT_FAILURE);
	}

	//step3. shared memory access
	shmaddr=(int*)shared_mem;
	for(i=0;i<dataCount;i++)
	{
		printf("shmaddr:%p, data:%d\n",(void*)(shmaddr+i),*(shmaddr+i));

	}
	//step4.shmdt
	if(shmdt(shared_mem)==-1)
	{
		fprintf(stderr,"shmdt failed\n");
		exit(EXIT_FAILURE);
	}
	//step5.shmclt
	if(shmctl(shmid,IPC_RMID,0)==-1)
	{
		fprintf(stderr,"shmctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
