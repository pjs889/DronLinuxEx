#include <stdio.h>
#include <sys/vfs.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    int ret;
    struct statfs s;
    long used_blocks;
    long used_percent;
    long crtMemory;

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
	printf("%ld\n",crtMemory);
    return 0;
}
