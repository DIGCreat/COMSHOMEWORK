/* ex7-1.c 
编译时在最后加上这个动态库 -pthread
gcc -o ex7-1 ex7-1.c -pthread
编译ex7-2.c同理
*/
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void print_msg(char *ptr);

int main()
{
	pthread_t thread1, thread2;
	int i,j;
	char *msg1="Hello\n";
	char *msg2="World\n";
	pthread_create(&thread1,NULL, (void *)(&print_msg), (void *)msg1);
	pthread_create(&thread2,NULL, (void *)(&print_msg), (void *)msg2);
	sleep(1);
	return 0;
}

void  print_msg(char *ptr)
{
	int retval;
	int id=pthread_self();
	printf("Thread ID: %lx\n",id);
  	printf("%s",ptr);
	pthread_exit(&retval);
}

