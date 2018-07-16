#include<stdio.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/select.h>

#define BUFSIZE 30

int main(int argc, char *argv[])
{
	fd_set reads,temps;
	int result,str_len;
	char buf[BUFSIZE];
	struct timeval timeout;

	// reads값 설정
	FD_ZERO(&reads);//파일디스크립터를 감시하는 fd_set값을 0으로 설정
	FD_SET(0,&reads); // stdin : monitoring
			  // 멀티프로세서에서는 소켓파일 디스크립터 3번이므로
			  // 0대신 3을 넣어주면 됨.

	while(1)
	{
		temps=reads;//원본은 보존된다. event가 발생하지 않으면 원본이 변하기 때문에
			    //temps를 이용하고 reads는 보존	
		// select()함수의 timeout값을 5초로 설정
		timeout.tv_sec=5;
		timeout.tv_usec=0;
		result = select(1,&temps,0,0,&timeout);
		if(result==-1)
		{
			write(1,"select() error!\n",16);//fflush 필요없다.printf는 필요함
			break;
		}
		// timeout에 의한 반환 시
		else if(result==0)
		{
			write(1,"timeout!\n",9);
		}
		// 정상적으로 select함수가 수행된 경우 (변화 발생시)
		else
		{
			if(FD_ISSET(0,&temps))//0번 디스크립터의 fd_set값 확인
				 	      //변화가 발생하면 1이므로 if문에 들어감.
			{
				str_len=read(0,buf,BUFSIZE);
				buf[str_len]=0; //문자열에 NULL추가
				printf("message from console:%s",buf);
				fflush(stdout);
			}
		}

	}



	return 0;
}
