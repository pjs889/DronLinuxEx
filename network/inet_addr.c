#include<stdio.h>
#include<arpa/inet.h>

int main(int argc,char *argv[])
{
	char *addr1="127.212.124.78";
	char *addr2="127.212.124.255";

	//127.212.124.78
	unsigned long conv_addr=inet_addr(addr1);
	if(conv_addr==INADDR_NONE)// 주소를 넣었는데도 주소가 입력되지 않은경우
		printf("Error occured!\n");
	else
		printf("IP ADDR : %#lx \n",conv_addr);

	
	//127.212.124.255
	 conv_addr=inet_addr(addr2);
	        if(conv_addr==INADDR_NONE)// 주소를 넣었는데도 주소가 입력되지 않은경우
		        printf("Error occured!\n");
	       else
			printf("IP ADDR : %#lx \n",conv_addr);


	return 0;
}
