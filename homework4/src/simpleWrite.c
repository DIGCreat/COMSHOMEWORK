#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(void){
    int nfile;
 
    nfile = open("test", O_WRONLY);
    if(nfile == -1){
        write(2, "A open error has occurred\n", 26);
    }
    else{
        if(write(nfile, "Hello welcome to CQUPT!\n", 24) != 24){
            write(2, "A write error has occurred\n", 27);
        }
    }
    close(nfile);
    exit(0);
}
