#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    int newfile, openfile;
    char buffer[1000];
    int nread;
   
    newfile = open("2013210364.txt", O_CREAT|O_WRONLY, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    openfile = open("test_file_1.txt", O_RDONLY);
    lseek(openfile, 200, SEEK_SET);
    nread = read(openfile, buffer, 100);
    if(nread == -1){
        write(2, "read error\n", 11);
    }
    buffer[100] = '\0';
    printf("200--300的字符为：\n%s\n开始写入到文件中\n", buffer); 
    if((write(newfile, buffer, 100)) != 100){
        write(2, "write error\n", 12);
    }
    printf("写入200--300个字符结束\n");

    lseek(openfile, -100, SEEK_END);
    nread = read(openfile, buffer, 100);
    if(nread == -1){
        write(2, "read error\n", 11);
    }
    buffer[100] = '\0';
    printf("倒数100个字符为：\n%s\n开始写入到文件中\n", buffer);
    if((write(newfile, buffer, 100)) != 100){
        write(2, "write error\n", 12);
    }
    printf("写入后100个字符结束\n");
    write(1, "program end\n", 12);
    close(openfile);
    close(newfile);
    exit(0);
}
