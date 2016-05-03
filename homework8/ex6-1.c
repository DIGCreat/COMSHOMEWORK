/*ex6-1.c*/
#include <stdio.h>
#include <signal.h>

void sigcatcher(int signum);

int main()
{
	char buffer1[100], buffer2[100];
	int i;
	if(signal(SIGTERM, &sigcatcher)==-1)
	{
		printf("Couldn't register signal hanlder!\n");
		exit(1);
	}
	printf("Pid of This Process : %d \n",getpid());
	printf("Please input:\n");
	for(;;)
	{
		fgets(buffer1, sizeof(buffer1),stdin);
		for(i=0;i<100;i++)
		{
			if(buffer1[i]>=97&&buffer1[i]<=122)
				buffer2[i]=buffer1[i]-32;
			else
				buffer2[i]=buffer1[i];
		}
		printf("Your input is: %s \n\n",buffer2);
	}
	exit(0);
}

void sigcatcher(int signum)
{
	printf("catch signal SIGTERM.\n");
	exit(0);
}

