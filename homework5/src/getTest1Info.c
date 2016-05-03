#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<utime.h>

int main(void){
    int fp;
    struct stat buf;
    struct utimbuf timebuf;
    struct tm * timeinfo;
    char buffer [128];
    fp = open("test_file_1.txt", O_RDWR);
    fstat(fp, &buf);

    timeinfo = localtime (&(buf.st_atime));
    strftime (buffer,sizeof(buffer),"%Y/%m/%d %H:%M:%S",timeinfo);
    printf("上次被访问的时间为： %s\n", buffer);

    timeinfo = localtime (&(buf.st_ctime));
    strftime (buffer,sizeof(buffer),"%Y/%m/%d %H:%M:%S",timeinfo);
    printf("上次属性被修改的时间为： %s\n", buffer);

    timeinfo = localtime (&(buf.st_mtime));
    strftime (buffer,sizeof(buffer),"%Y/%m/%d %H:%M:%S",timeinfo);
    printf("上次内容被修改的时间为： %s\n", buffer);
    if(ftruncate(fp, 364) == -1){
        printf("failed\n");
    }
    timebuf.actime = buf.st_atime;
    timebuf.modtime = buf.st_mtime;
    utime("test_file_1.txt", &timebuf);
    close(fp);
    exit(0);
} 
