#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include "cal.h"

#define BUFSIZE 50

void error_handling(char *message);

int main(int argc,char *argv[])
{
	int sock;
	struct sockaddr_in serv_addr;
	char message[BUFSIZE];
	int str_len;
	struct Cal cal;
	int operand,i,cnt;
	char operation;

	if(argc!=3)
	{
		printf("Usage : %s [IP] [PORT]\n",argv[0]);
		exit(1);
	}

	// 1.socket()
	sock = socket(PF_INET,SOCK_STREAM,0);
	if(sock==-1)
	{
		error_handling("socket() error");
	}
	
	// 2.서버의 주소(ip,port)값을 설정
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	// 3. connect()
	if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
	{
		error_handling("connet() error");
	}
	
	// 4. Data transfer
	//str_len = read(sock,message,sizeof(message)-1);//메세지가 수신 안되면 여기서 blocking 되어있다.


	printf("operation Count: ");
	scanf("%d",&cnt);
	cal.cnt=cnt;
	for(i=0;i<cnt;i++)
	{
		printf("operand%d:",i+1);
		scanf("%d",&cal.operand[i]);
		//cal.operand[i]=operand;
		
		if(i==cnt-1)
		{
			printf("operation:");
			scanf("%c",&cal.operation);
			scanf("%c",&cal.operation);
			//cal.operation=operation;
		}
	}

	str_len=write(sock,&cal,sizeof(cal));
	        if(str_len==-1)
		{
	              error_handling("read() error");
		}

	
	
	
	//printf("Message from server : %s\n", message);

	// 5.close()
	close(sock);

	return 0;



}

void error_handling(char *message)
{
        fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}
