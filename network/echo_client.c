#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUFSIZE 50

void error_handling(char *message);

int main(int argc,char *argv[])
{
	int sock;
	struct sockaddr_in serv_addr;
	char message[BUFSIZE];
	int str_len;

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
	else
		printf("Connected....\n");
	while(1)
	{
		printf("Input message(Q to quit):");
		fgets(message,sizeof(message),stdin);

		if(!strcmp(message,"q\n") || !strcmp(message,"Q\n"))
			break; //"q\n"한 이유는 fgets가 엔터키까지 먹기때문

		write(sock,message,strlen(message));//sizeof로 하면 엔터키가 들어가 문자가 깨짐
		str_len=read(sock,message,sizeof(message)-1);
		message[str_len]=0;	//NULL문자 삽입
		if(str_len==-1)
		{
			error_handling("read() error");
		}	
	
		printf("Message from server : %s\n", message);
	}
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
