#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/types.h>

#define BUFSIZE 1024

//int main(int argc,char **argv)
int main(int argc,char *argv[])
{
          int count,fdIn,fdOut;
	  char buf[BUFSIZE];
         //인자값이 3개가 아닌 경우
	  if(argc<3)
	  {
              // printf("usage : copy file1 file2\n");
	      //fflush(stdout); 버퍼에 있는 문자들을 출력하고 넘어가라
	      write(1,"Usage : copy file1 file2\n",26);
	      return -1;
	  
	  }
        //원본파일이 정상적으로 열리지 않은 경우
	if((fdIn=open(argv[1],O_RDONLY)) <0) 
           {
                 perror(argv[1]);
		 return -1;
	   }
         
	 if((fdOut=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR))<0)
	 {
               perror(argv[2]);
	       return -1;
	 }

         while((count = read(fdIn,buf,sizeof(buf))) > 0)
	 write(fdOut,buf,count);

         close(fdIn);
	 close(fdOut);

	 return 0;
	  }
