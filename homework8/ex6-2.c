/*ex6-2.c*/
#include <stdio.h>
#include <signal.h>

void intfunc(int signum);
void continuefunc(int signum);
void exitfunc(int signum);

int main()
{
	char buffer1[100],buffer2[100];
	int i;
	if(signal(SIGINT, &intfunc)==-1)
	{
		printf("Couldn't register signal hanlder for SIGINT!\n");
		exit(1);
	}
	if(signal(SIGTSTP, &intfunc)==-1)
	{
		printf("Couldn't register signal hanlder for SIGTSTP!\n");
		exit(1);
	}
	if(signal(SIGCONT, &continuefunc)==-1)
	{
		printf("Couldn't register signal hanlder for SIGCONT!\n");
		exit(1);
	}
	if(signal(SIGTERM, &exitfunc)==-1)
	{
		printf("Couldn't register signal hanlder for SIGTERM!\n");
		exit(1);
	}
	printf("Pid of This Process : %d \n",getpid());

	for(;;)
	{
		printf("Please input:\n");
		fgets(buffer1, sizeof(buffer1),stdin);
		for(i=0;i<100;i++)
		{
			if(buffer1[i]>=97&&buffer1[i]<=122)
				buffer2[i]=buffer1[i]-32;
			else
				buffer2[i]=buffer1[i];
		}
		printf("Your input is: %s \n",buffer2);
	}
	exit(0);
}

void intfunc(int signum)
{
	printf("catch signal %d \n",signum);
}

void continuefunc(int signum)
{
	printf("Continue.\n");
}

void exitfunc(int signum)
{
	printf("signal SIGTERM \n");
	exit(0);
}

