#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUFSIZE 30
#define TRUE 1
#define FALSE 0


// ./hello_server [PORT]
void error_handling(char *message);


int main(int argc,char *argv[])
{
	int serv_sock;
	int str_len;
	int option;
	char buf[BUFSIZE];

	struct sockaddr_in addr;
	socklen_t clnt_addr_size;
	socklen_t optlen;
	struct ip_mreq join_adr;
	char *ipaddr;

	if(argc!=2)
	{
		printf("Usage : %s [port]\n",argv[0]);
		exit(1);
	}

	// 1.socket() 소켓을 생성한다.
	serv_sock=socket(PF_INET,SOCK_DGRAM,0);
	if(serv_sock==-1)
		error_handling("socket() error");
	
	// 2.서버의 주소값(ip,port)을 설정한다.
	memset(&addr,0,sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=htonl(INADDR_ANY);  //IP 설정
	addr.sin_port=htons(atoi(argv[1]));      //PORT 설정
	
	// bind() error방지
	optlen=sizeof(option);
	option=TRUE;
	setsockopt(serv_sock,SOL_SOCKET,SO_REUSEADDR,&option,optlen);

	// 3.서버의 주소값을 bind한다.
	if(bind(serv_sock, (struct sockaddr*) &addr,sizeof(addr))==-1)
		error_handling("bind() error");

	while(1)
	{
		str_len=recvfrom(serv_sock,buf,BUFSIZE-1,0,NULL,0);//udp이기 때문에 recvfrom으로
								   //데이터를 읽는다.
		if(str_len<0)
		    break;
		buf[str_len]=0;
		printf("%s\n",buf);
	}

	close(serv_sock);
	return 0;

}

void error_handling(char *message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}
