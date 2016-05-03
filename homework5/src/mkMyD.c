#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<stdio.h>
#include<fcntl.h>
#include <time.h>


int main(){
    int oldfile, newfile;
    char block[1024];
    int nread;
    DIR *dir;
    struct dirent *ptr;
    struct stat buf;
    struct tm * timeinfo;
    char buffer [128];

    oldfile = open("/home/cdq-2013210364/Workspace/CProgram/homework5/test_file_1.txt", O_RDONLY);
    mkdir("2013210364", S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP|S_IROTH|S_IXOTH);
    chdir("2013210364");
    newfile = open("test_file_1.txt", O_CREAT|O_RDWR,S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
    while((nread = read(oldfile, block, sizeof(block))) > 0){
        write(newfile, block, nread);
    }
    oldfile = open("/home/cdq-2013210364/Workspace/CProgram/homework5/test_file_2.txt", O_RDONLY);
    newfile = open("test_file_2.txt", O_CREAT|O_RDWR,S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
    while((nread = read(oldfile, block, sizeof(block))) > 0){
        write(newfile, block, nread);
    }
    dir = opendir(".");
    while((ptr = readdir(dir)) != NULL)
    {
        stat(ptr->d_name, &buf);
	printf("--------------------\n");
	printf("文件名：%s\n", ptr->d_name);
	printf("文件大小：%d\n", buf.st_size);
        timeinfo = localtime (&(buf.st_atime));
        strftime (buffer,sizeof(buffer),"%Y/%m/%d %H:%M:%S",timeinfo);
	printf("上次被访问时间：%s\n", buffer);
        timeinfo = localtime (&(buf.st_mtime));
        strftime (buffer,sizeof(buffer),"%Y/%m/%d %H:%M:%S",timeinfo);
	printf("上次内容被修改时间：%s\n", buffer);
        timeinfo = localtime (&(buf.st_ctime));
        strftime (buffer,sizeof(buffer),"%Y/%m/%d %H:%M:%S",timeinfo);
	printf("上次属性被改变时间：%s\n", buffer);
    }
    closedir(dir);
    close(oldfile);
    close(newfile);
}


