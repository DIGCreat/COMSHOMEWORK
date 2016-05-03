#include "client.h"
#include<ctype.h>

int main(){
	int server_fifo_fd, client_fifo_fd;
	struct data_to_pass_st my_data;
	char client_fifo[256], send_msg[1000];

	memset(send_msg, '\0', sizeof(send_msg));
	server_fifo_fd = open(SERVER_FIFO_NAME, O_WRONLY);
	if(server_fifo_fd == -1){
		fprintf(stderr, "Sorry, no server\n");
		exit(EXIT_FAILURE);
	}

	my_data.client_pid = getpid();
	sprintf(client_fifo, CLIENT_FIFO_NAME, my_data.client_pid);
	if(mkfifo(client_fifo, 0777) == -1){
		fprintf(stderr, "Sorry, can't make %s\n", client_fifo);
		exit(EXIT_FAILURE);
	}


	while(1){
		printf("say:");
		scanf("%s", send_msg);
		sprintf(my_data.some_data, send_msg, my_data.client_pid);
		write(server_fifo_fd, &my_data, sizeof(my_data));

		if(strcmp(send_msg, "quit") == 0){
		    client_fifo_fd = open(client_fifo, O_RDONLY|O_NONBLOCK);
			sleep(5);
			read(client_fifo_fd, &my_data, sizeof(my_data));
			if(strcmp(my_data.some_data, "ok") == 0){
				close(client_fifo_fd);
				break;
			}
		}

		client_fifo_fd = open(client_fifo, O_RDONLY);

		if(client_fifo_fd != -1){
			if(read(client_fifo_fd, &my_data, sizeof(my_data)) > 0){
				printf("received:%s\n", my_data.some_data);
				close(client_fifo_fd);
			}
		}
		memset(send_msg, '\0', sizeof(send_msg));
	}
	close(server_fifo_fd);
	unlink(client_fifo);
	exit(EXIT_SUCCESS);
}
