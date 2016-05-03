#include "client.h"
#include<ctype.h>
#include<signal.h>

void closefifo(int sig);

int main(){
	int server_fifo_fd, client_fifo_fd;
	struct data_to_pass_st my_data;
	int read_res;
	char client_fifo[256];
	char *tmp_char_ptr;

	mkfifo(SERVER_FIFO_NAME, 0777);
	server_fifo_fd = open(SERVER_FIFO_NAME, O_RDONLY|O_NONBLOCK);
	if(server_fifo_fd == -1){
		fprintf(stderr, "Server fifo failure\n");
		exit(EXIT_FAILURE);
	}

//    if((signal(SIGINT, closefifo)) == 0){
//		close(server_fifo_fd);
//		unlink(SERVER_FIFO_NAME);
//	}

	do{
		read_res = read(server_fifo_fd, &my_data, sizeof(my_data));

		if(read_res > 0){
			if(strcmp(my_data.some_data, "quit") == 0){
				printf("%d client exit.", my_data.client_pid);
				client_fifo_fd = open(client_fifo, O_WRONLY);
				if(client_fifo_fd != -1){
					sprintf(my_data.some_data, "ok");
					write(client_fifo_fd, &my_data, sizeof(my_data));
					sleep(5);
					close(client_fifo_fd);
					printf("Done\n");
					break;
				}
				else{
					printf("closing client occur error.\n");
				}
			}
			printf("%d client say:%s\n", my_data.client_pid, my_data.some_data);
			tmp_char_ptr = my_data.some_data;
			while(*tmp_char_ptr){
				*tmp_char_ptr = toupper(*tmp_char_ptr);
				tmp_char_ptr++;
			}
			sprintf(client_fifo, CLIENT_FIFO_NAME, my_data.client_pid);

			client_fifo_fd = open(client_fifo, O_WRONLY);
			if(client_fifo_fd != -1){
				printf("say something:");
				scanf("%s", my_data.some_data);
				write(client_fifo_fd, &my_data, sizeof(my_data));
				close(client_fifo_fd);
			}
		}
	}while(1);
	close(server_fifo_fd);
	unlink(SERVER_FIFO_NAME);
	exit(EXIT_SUCCESS);
}

void closefifo(int sig){
	printf("QUIT SERVER\n");
}
