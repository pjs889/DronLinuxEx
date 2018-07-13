#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>

void error_handling(char *message)
{
        fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}

int main(int argc,char *argv[])
{
	int tcp_sock,udp_sock;
	int snd_buf,rcv_buf;
	socklen_t optlen;
	int state;

	optlen = sizeof(snd_buf);
	// TCP socket 생성
	tcp_sock = socket(PF_INET,SOCK_STREAM,0);
	
	// TCP Read: snd_buf
	state = getsockopt(tcp_sock, SOL_SOCKET,SO_SNDBUF,(void*)&snd_buf,&optlen);
	
	if(state)
                 error_handling("tcp getsockopt() error");
        printf("Socket output buffer size : %d\n",snd_buf);

	// setsockopt()수행 snf_buf를 2배로정
	//snd_buf=(snd_buf<<1);
	state=setsockopt(tcp_sock,SOL_SOCKET,SO_SNDBUF,(void*)&snd_buf,optlen);
	if(state)
		error_handling("setsockopt() snd_buf error");

	//setsockopt가 정상적으로 수행되었는지 확인하기 위해
	state = getsockopt(tcp_sock, SOL_SOCKET,SO_SNDBUF,(void*)&snd_buf,&optlen);
    
            if(state)
	            error_handling("tcp getsockopt() error");
	    printf("Socket output buffer size : %d\n",snd_buf);


	optlen=sizeof(rcv_buf);
	// TCP Read: rcv_buf
	state = getsockopt(tcp_sock, SOL_SOCKET,SO_RCVBUF,(void*)&rcv_buf,&optlen);

	if(state)
		error_handling("tcp getsockopt() error");
	printf("Socket input buffer size : %d\n",rcv_buf);

	return 0;
}
