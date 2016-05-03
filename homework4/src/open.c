#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>

int main(void){
    char buffer[100];
    int nread;
    int nfile;
    nfile = open("/etc/apt/sources.list", O_RDONLY);
    nread = read(nfile, buffer, 100);
    if(nread == -1){
	write(2, "A read error has occurred\n", 26);
    }
    if(write(1, buffer, nread) != nread){
	write(2, "A write error has occurred\n", 27);
    }
    close(nfile);
    exit(0);
}
