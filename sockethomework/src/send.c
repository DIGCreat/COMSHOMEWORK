/**
 *  * @file ip_tcp_send.c
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

void err_exit(const char *err_msg)
{
	perror(err_msg);
	exit(1);
}

/* 填充ip首部 */
struct ip *fill_ip_header(const char *src_ip, const char *dst_ip, int ip_packet_len, int pro)
{
	struct ip *ip_header;

	ip_header = (struct ip *)malloc(IP_HEADER_LEN);
	ip_header->ip_v = IPVERSION;
	ip_header->ip_hl = sizeof(struct ip) / 4;        /* 这里注意，ip首部长度是指占多个32位的数量，4字节=32位，所以除以4 */
	ip_header->ip_tos = 0;
	ip_header->ip_len = htons(ip_packet_len);        /* 整个IP数据报长度，包括普通数据 */
	ip_header->ip_id = 0;                            /* 让内核自己填充标识位 */
	ip_header->ip_off = 0;
	ip_header->ip_ttl = MAXTTL;
	ip_header->ip_p = pro;                   /* ip包封装的协议类型 */
	ip_header->ip_sum = 0;                           /* 让内核自己计算校验和 */
	ip_header->ip_src.s_addr = inet_addr(src_ip);    /* 源IP地址 */
	ip_header->ip_dst.s_addr = inet_addr(dst_ip);    /* 目标IP地址 */

	return ip_header;
}

/* 填充tcp首部 */
struct tcphdr *fill_tcp_header(int src_port, int dst_port)
{
	struct tcphdr *tcp_header;

	tcp_header = (struct tcphdr *)malloc(TCP_HEADER_LEN);
	tcp_header->source = htons(src_port); 
	tcp_header->dest = htons(dst_port);
	/* 同IP首部一样，这里是占32位的字节多少个 */
	tcp_header->doff = sizeof(struct tcphdr) / 4;
	/* 发起连接 */
	tcp_header->syn = 1;
	tcp_header->window = 4096;
	tcp_header->check = 0;

	return tcp_header;
}

/* 填充udp首部 */
struct udphdr *fill_udp_header(int src_port, int dst_port, int dataLen)
{
	struct udphdr *udp_header;

	udp_header = (struct udphdr *)malloc(UDP_HEADER_LEN);
	udp_header->source = htons(src_port); 
	udp_header->dest = htons(dst_port);
	udp_header->len = ntohs(8+dataLen);
	udp_header->check = 0;

	return udp_header;
}
/* 发送ip_tcp报文 */
void ip_tcp_send(const char *src_ip, int src_port, const char *dst_ip, int dst_port, const char *data)
{
	struct ip *ip_header;
	struct tcphdr *tcp_header;
	struct sockaddr_in dst_addr;
	socklen_t sock_addrlen = sizeof(struct sockaddr_in);

	int data_len = strlen(data);
	int ip_packet_len = IP_TCP_HEADER_LEN + data_len;
	char buf[ip_packet_len];
	int sockfd, ret_len, on = 1;

	bzero(&dst_addr, sock_addrlen);
	dst_addr.sin_family = PF_INET;
	dst_addr.sin_addr.s_addr = inet_addr(dst_ip);
	dst_addr.sin_port = htons(dst_port);

	/* 创建tcp原始套接字 */
	if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP)) == -1)
		err_exit("socket()");

	/* 开启IP_HDRINCL，自定义IP首部 */
	if (setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on)) == -1)
		err_exit("setsockopt()");

	/* ip首部 */
	ip_header = fill_ip_header(src_ip, dst_ip, ip_packet_len, IPPROTO_TCP);
	/* tcp首部 */
	tcp_header = fill_tcp_header(src_port, dst_port);

	bzero(buf, ip_packet_len);
	memcpy(buf, ip_header, IP_HEADER_LEN);
	memcpy(buf + IP_HEADER_LEN, tcp_header, TCP_HEADER_LEN);
	memcpy(buf + IP_TCP_HEADER_LEN, data, data_len);

	/* 发送报文 */
	ret_len = sendto(sockfd, buf, ip_packet_len, 0, (struct sockaddr *)&dst_addr, sock_addrlen);
	if (ret_len > 0)
		printf("send TCP ok!!!\n");
	else printf("send TCP failed\n");

	close(sockfd);
	free(ip_header);
	free(tcp_header);
}

/* 发送ip_udp报文 */
void ip_udp_send(const char *src_ip, int src_port, const char *dst_ip, int dst_port, const char *data)
{
	struct ip *ip_header;
	struct udphdr *udp_header;
	struct sockaddr_in dst_addr;
	socklen_t sock_addrlen = sizeof(struct sockaddr_in);

	int data_len = strlen(data);
	int ip_packet_len = IP_UDP_HEADER_LEN + data_len;
	char buf[ip_packet_len];
	int sockfd, ret_len, on = 1;

	bzero(&dst_addr, sock_addrlen);
	dst_addr.sin_family = PF_INET;
	dst_addr.sin_addr.s_addr = inet_addr(dst_ip);
	dst_addr.sin_port = htons(dst_port);

	/* 创建udp原始套接字 */
	if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP)) == -1)
		err_exit("socket()");

	/* 开启IP_HDRINCL，自定义IP首部 */
	if (setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on)) == -1)
		err_exit("setsockopt()");

	/* ip首部 */
	ip_header = fill_ip_header(src_ip, dst_ip, ip_packet_len, IPPROTO_UDP);
	/* udp首部 */
	udp_header = fill_udp_header(src_port, dst_port, data_len);

	bzero(buf, ip_packet_len);
	memcpy(buf, ip_header, IP_HEADER_LEN);
	memcpy(buf + IP_HEADER_LEN, udp_header, UDP_HEADER_LEN);
	memcpy(buf + IP_UDP_HEADER_LEN, data, data_len);

	/* 发送报文 */
	ret_len = sendto(sockfd, buf, ip_packet_len, 0, (struct sockaddr *)&dst_addr, sock_addrlen);
	if (ret_len > 0)
		printf("send UDP ok!!!\n");
	else printf("send UDP failed\n");

	close(sockfd);
	free(ip_header);
	free(udp_header);
}

int main(int argc, const char *argv[])
{
	const char *sender = "127.0.0.1";
	const char *sender_port = "3000";
	const char *recver = "127.0.0.1";
	const char *tcp_recver_port = "1500";
	const char *udp_recver_port = "2000";
	int choice;
	if (argc != 2)
	{
		printf("usage:%s data\n", argv[0]);
		exit(1);
	}

	printf("选择发送哪种数据报：1、TCP 2、UDP：");
	scanf("%d", &choice);
	switch(choice){
	/* 发送ip_tcp报文 */
	case 1:ip_tcp_send(sender, atoi(sender_port), recver, atoi(tcp_recver_port), argv[1]);break;
	/* 发送ip_udp报文 */
	case 2:ip_udp_send(sender, atoi(sender_port), recver, atoi(udp_recver_port), argv[1]);break;
	}
	return 0;
}
