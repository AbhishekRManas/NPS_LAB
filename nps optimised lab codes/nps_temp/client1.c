#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<netinet/in.h>

#define GROUP "225.0.0.37"
#define PORT 12345

int main()
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if(sockfd > 0)
        printf("Socket created\n");
    else
    {
        printf("Socket creation failed\n");
        exit(0);
    }

    int yes = 1;

    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) < 0)
    {
        printf("Error in reuse....\n");
        exit(0);
    }

    struct sockaddr_in addr;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);

    int bindfd = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));

    if(bindfd != 0)
    {
        printf("Socket binding failed\n");
        exit(0);
    }

    struct ip_mreq mreq;

    mreq.imr_multiaddr.s_addr = inet_addr(GROUP);
    mreq.imr_interface.s_addr = INADDR_ANY;

    if(setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0)
    {
        printf("add membership failed\n");
        exit(0);
    }


    char buff[1024];

    while(1)
    {
        int len = sizeof(addr);

        if(recvfrom(sockfd, buff, 1024, 0, (struct sockaddr*)&addr, &len) > 0)
            puts(buff);
    }
}