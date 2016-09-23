/**
 *  * @file ip_tcp_recv.c
 *   */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>

/* ip首部长度 */
#define IP_HEADER_LEN sizeof(struct ip)
/* tcp首部长度 */
#define TCP_HEADER_LEN sizeof(struct tcphdr)
/* udp首部长度 */
#define UDP_HEADER_LEN sizeof(struct udphdr)
/* ip首部 + tcp首部长度 */
#define IP_TCP_HEADER_LEN IP_HEADER_LEN + TCP_HEADER_LEN
/* ip首部 + udp首部长度 */
#define IP_UDP_HEADER_LEN IP_HEADER_LEN + UDP_HEADER_LEN
/* 接收数据缓冲大小 */
#define BUFFER_SIZE 1024
/* ip首部 + tcp首部 + 数据缓冲区大小 */
#define IP_TCP_BUFF_SIZE IP_TCP_HEADER_LEN + BUFFER_SIZE
/* ip首部 + tcp首部 + 数据缓冲区大小 */
#define IP_UDP_BUFF_SIZE IP_UDP_HEADER_LEN + BUFFER_SIZE

void err_exit(const char *err_msg)
{
	perror(err_msg);
	exit(1);
}

/* 原始套接字接收 */
void raw_socket_recv()
{
	struct ip *ip_header;
	struct tcphdr *tcp_header;
	struct udphdr *udp_header;
	struct sockaddr_in addr;
	int sock_raw_fd, ret_len, pid = -1;
	int addr_len = sizeof(struct sockaddr_in);
	char buf[IP_TCP_BUFF_SIZE], udpbuf[IP_UDP_BUFF_SIZE];

	if((pid = fork()) == 0){
		if((sock_raw_fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP)) == -1)
			err_exit("socket()");
		bzero(&addr, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_port = htons(2000);
		addr.sin_addr.s_addr = inet_addr("127.0.0.1");
		if(bind(sock_raw_fd, (struct sockaddr *)&addr, addr_len) == -1){
			err_exit("bind()");
		}
		while(1){
			bzero(udpbuf, IP_UDP_BUFF_SIZE);
			ret_len = recvfrom(sock_raw_fd, udpbuf, IP_UDP_BUFF_SIZE, 0, &addr, &addr_len);
			if(ret_len > 0){
				ip_header = (struct ip *)udpbuf;
				udp_header = (struct udphdr *)(udpbuf + IP_HEADER_LEN);
				printf("=================================\n");
				printf("from ip: \t\t%s\n", inet_ntoa(ip_header->ip_src));
				printf("from port:\t\t%d\n", ntohs(udp_header->source));
				printf("get protocol:\t\t%d\n", ip_header->ip_p);
				printf("get data:\t\t%s\n", udpbuf+IP_UDP_HEADER_LEN);
			}
		}
		close(sock_raw_fd);
	}
	else{
		if((sock_raw_fd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP)) == -1)
			err_exit("socket()");
		bzero(&addr, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_port = htons(1500);
		addr.sin_addr.s_addr = inet_addr("127.0.0.1");

		if(bind(sock_raw_fd, (struct sockaddr *)&addr, addr_len) == -1){
			err_exit("bind()");
		}
		while(1){
			bzero(buf, IP_TCP_BUFF_SIZE);
			ret_len = recvfrom(sock_raw_fd, buf, IP_TCP_BUFF_SIZE, 0, &addr, &addr_len);
			if(ret_len > 0){
				ip_header = (struct ip *)buf;
				tcp_header = (struct tcphdr *)(buf + IP_HEADER_LEN);
				printf("=================================\n");
				printf("from ip: \t\t%s\n", inet_ntoa(ip_header->ip_src));
				printf("from port:\t\t%d\n", ntohs(tcp_header->source));
				printf("get protocol:\t\t%d\n", ip_header->ip_p);
				printf("get data:\t\t%s\n", buf+IP_TCP_HEADER_LEN);
			}
		}
		close(sock_raw_fd);
	}
}

int main(void)
{
	/* 原始套接字接收 */
	raw_socket_recv();

	return 0;
}
