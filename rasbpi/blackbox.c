#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <sys/vfs.h>


#define BUFSIZE 100
#define DIRPATH "/home/pi/user/blackbox/"


void delDir(void);


int main(int argc,char **argv)
{
        time_t UTCtime;
	struct tm *tm;
	char buf[BUFSIZ];
	char temp[BUFSIZE];
	char dirName[BUFSIZE];
	struct timeval UTCtime_u;
	int result;
	char cmd[BUFSIZE];

	int ret;
       struct statfs s;
       long used_blocks;
       long used_percent;
       long crtMemory;
       long CUT = 1024*1024*7;
	
	while(1)
	{
		// 1.time()
		time(&UTCtime);
		printf("time : %u\n",(unsigned)UTCtime);    //UTC현재시간 출력

		tm=localtime(&UTCtime);
	
		// blackbox /   hour create
		strftime(temp,sizeof(temp),"%Y%m%e%H",tm);
		sprintf(dirName,DIRPATH);
        	strcat(dirName,temp);
		printf("dirName : %s\n",dirName);
		   if((result=mkdir(dirName,0777))==-1)
			{
				if (errno!=EEXIST)
				{	
		  			perror("mkdir error");
	  				return  1;
				}
#ifdef DEBUG
	printf("%s is exist\n",dirName);
#endif
    			}	
		//blackbox /  hour / sec create
		strftime(buf,sizeof(buf),"%Y%m%e_%H%M%S",tm);
		printf("strtftime: %s\n",buf);
	
		strcat(buf,".h264 -vf -hf");
		sprintf(cmd,"raspivid -p 100,100,300,480 -w 640 -h 480 -t 60000 ");
		strcat(cmd," -o ");
		strcat(cmd,dirName);
		strcat(cmd,"/");
		strcat(cmd,buf);
		printf("cmd = %s",cmd);
		system(cmd);	
		

	////////////////////////////////////
	if (argc<2) {
        printf("Too few arguments\nUsage: ./finfo mount_point\n");
        return 1;
    }
    /*인자로 주어진 파일/디렉토리의 마운트된 곳의 정보를 가져옵니다.*/
    if ( statfs((const char*)argv[1], &s) !=0) {
        perror("statfs");
        return 1;
    }

    if (s.f_blocks >0) {
        long free_percent;
        used_blocks = s.f_blocks - s.f_bfree;
        if (used_blocks ==0)
            used_percent = 0;
        else {
            used_percent = (long)
                (used_blocks * 100.0 / (used_blocks + s.f_bavail) + 0.5);
        }
        if (s.f_bfree ==0)
            free_percent = 0;
        else {
            free_percent = (long)
                (s.f_bavail * 100.0 / (s.f_blocks) + 0.5);
        }
 
        printf("blocks %ld%% remain(%ld bytes %ldK\n",
                free_percent,
                s.f_bavail * s.f_bsize,
                (long) (s.f_bavail * (s.f_bsize/(double)1024))
                );
    }
	crtMemory=(long) (s.f_bavail * (s.f_bsize/(double)1024));
	printf("current memory = %ld\n",crtMemory);
	
  if(crtMemory<CUT)
	{
	  delDir();
	}
   }


	return 0;
}



void delDir(void)
{
  struct dirent **namelist;
  int count;
  int idx;
  int min_num;
  char delCmd[BUFSIZE];

  if((count=scandir(DIRPATH,&namelist,NULL,alphasort))==-1){
	fprintf(stderr,"%s Directory Scan error:%s\n",DIRPATH,strerror(errno));
	return ;
  }

  for(idx=0;idx<count;idx++){
	printf("%s\n",namelist[idx]->d_name);
  }
  
  //min_num=atoi(namelist[2]->d_name);
  //printf("min_num: %d\n",min_num);
    
  sprintf(delCmd,"rm -rf ");
  strcat(delCmd,DIRPATH);
  strcat(delCmd,namelist[2]->d_name);
  system(delCmd);

  for(idx=0;idx<count;idx++){
	free(namelist[idx]);
  }

  free(namelist);
}

