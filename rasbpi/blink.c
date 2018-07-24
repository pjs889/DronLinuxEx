//For wiringPi
#include<wiringPi.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

int bright=100;
int dim=100;

void* key_func(void* data)
{
	int id=0;
	char insert;
	for(;;)
	{
		printf("insert key(a or d):");
		scanf("%s",&insert);

		if(insert=='a')
		{
			bright=bright+5;
		}
		else if(insert=='d')
		{
			dim=dim-5;	
		}
		
	}
	return (void*)id;
}



int main(void)
{

	pthread_t pid;
	int status;
	int err;
	char insert;
	//WiringPi Initalize function
	wiringPiSetup();	
	pinMode(0,OUTPUT);
	if((err=pthread_create(&pid,NULL,key_func,(void*)NULL))<0)
	{
		perror("thread create error:");
		exit(1);
	}
	
	
	for(;;)
	{	

	digitalWrite(0,HIGH);
	delay(bright);
	//usleep(bright);
	digitalWrite(0,LOW);
	//usleep(dim);
	delay(dim);

	}
	
	pthread_detach(pid);

	return 0;

}
