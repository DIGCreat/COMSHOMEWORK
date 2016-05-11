#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<sys/msg.h>
//#include<fcntl.h>
//#include<sys/types.h>
//#include<sys/stat.h>

#define MAX_TEXT 512

typedef struct my_msg_st {
	long int my_msg_type;
	char some_text[MAX_TEXT];
} myMsgSt;

int main(){
	FILE *fp;
	myMsgSt some_data;
	int msgid;
	char buffer[BUFSIZ], fpath[512];

	msgid = msgget((key_t)1234, 0666|IPC_CREAT);
	if(msgid == -1){
		fprintf(stderr, "msgget failed with error: %d\n", errno);
		exit(EXIT_FAILURE);
	}

	printf("reading text.txt\n");
	fp = fopen("text.txt", "r");

	while(fgets(buffer, BUFSIZ, fp) != NULL){
		some_data.my_msg_type = 1;
		strcpy(some_data.some_text, buffer);

		if(msgsnd(msgid, (void *)&some_data, MAX_TEXT, 0) == -1){
			fprintf(stderr, "msgsnd failed\n");
			exit(EXIT_FAILURE);
		}
	}

	strcpy(some_data.some_text, "end");
	if(msgsnd(msgid, (void *)&some_data, MAX_TEXT, 0) == -1){
		fprintf(stderr, "msgsnd failed\n");
		exit(EXIT_FAILURE);
	}
	printf("Done.\n");

	exit(EXIT_SUCCESS);
}
