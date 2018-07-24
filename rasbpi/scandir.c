#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define BUFSIZE 100
#define DIRPATH "/home/pi/user/blackbox/"
const char *path="/home/pi/user/blackbox";

int main(void)
{
  struct dirent **namelist;
  int count;
  int idx;
  int min_num;
  char delCmd[BUFSIZE];

  if((count=scandir(path,&namelist,NULL,alphasort))==-1){
	fprintf(stderr,"%s Directory Scan error:%s\n",path,strerror(errno));
	return 1;
  }

  for(idx=0;idx<count;idx++){
	printf("%s\n",namelist[idx]->d_name);
  }
  
  min_num=atoi(namelist[2]->d_name);
  printf("min_num: %d\n",min_num);
    
  sprintf(delCmd,"rm -rf ");
  strcat(delCmd,DIRPATH);
  strcat(delCmd,namelist[2]->d_name);
  printf("delCmd :%s\n",delCmd);
  system(delCmd);

  for(idx=0;idx<count;idx++){
	free(namelist[idx]);
  }

 
  free(namelist);

  return 0;

}
