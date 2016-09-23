#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#define USHORT unsigned short
#define ULONG unsigned long
#define UCHAR unsigned char
#define UINT unsigned int

struct IpHead
{
    unsigned char  ucVersionAndHeadLength;        // Version (4 bits) + Internet header length (4 bits)
    unsigned char  ucTos;            // Type of service 
    unsigned short usTotalLength;           // Total length 
    unsigned short usIdentification; // Identification
    unsigned short usFlagsAndFragmentOffset;       // Flags (3 bits) + Fragment offset (13 bits)
    unsigned char  ucTtl;            // Time to live
    unsigned char  ucProtocol;          // Protocol
    unsigned short usCrc;            // Header checksum
    unsigned long  dwSourceAddr;      // Source address
    unsigned long  dwDestAddr;      // Destination address
};
struct TcpHead            //¶¨ÒåTCP Ê×²¿
{
	USHORT usSourcePort; //16 Î»Ô´¶Ë¿Ú
	USHORT usDestPort; //16 Î»Ä¿µÄ¶Ë¿Ú
	ULONG dwSeq;
	ULONG dwAck;
	UCHAR ucLength;           //4 Î»Ê×²¿³¤¶È/4 Î»±£Áô×Ö
	UCHAR ucFlag;            //6 Î»±êÖ¾Î»
	USHORT usWindow; //16 Î»´°¿Ú´óÐ¡
	USHORT usCrc;//16 Î»Ð£ÑéºÍ
	USHORT usUrgent;//16 Î»½ô¼±Êý¾ÝÆ«ÒÆÁ¿
	UINT unMssOpt;
	USHORT usNopOpt;
	USHORT usSackOpt;
};
int main(){
	int sockfd;
	struct TcpHead theTcpHead;
	struct IpHead theIpHead;

	
	sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_TP);

    theTcpHead.usDestPort=htons(1000);
    theTcpHead.usSourcePort=htons(3000);
    theTcpHead.dwSeq=ntohl(198327);
    theTcpHead.dwAck=0;
    theTcpHead.ucLength=0x70;
    theTcpHead.ucFlag=4;
    theTcpHead.usWindow=0xFFFF;	 //16  
    theTcpHead.usCrc=0;//16 位校验和
    theTcpHead.usUrgent=0;//16 位紧急数
    theTcpHead.unMssOpt=htonl(0x020405B4);
    theTcpHead.usNopOpt= 0x0101;
    theTcpHead.usSackOpt= 0x0204;
    theTcpHead.usCrc=0;
}
