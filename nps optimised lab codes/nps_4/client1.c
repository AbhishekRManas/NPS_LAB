#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include<stdlib.h>

#define HELLO_PORT 12345
#define HELLO_GROUP "225.0.0.37"
#define MSGBUFSIZE 25

int main()
{
    //--------------------------------------------------------------------------------------
    //  > Socket creation
    //--------------------------------------------------------------------------------------
        int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

        if(sockfd > 0)
            printf("Socket created..\n");
        else
        {
            printf("Socket creation failed...\n");
            exit(0);
        }
    //--------------------------------------------------------------------------------------
    //  > Socket modification for reusing the address
    //--------------------------------------------------------------------------------------
        int yes = 1;

        int fd1 = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

        if(fd1 < 0)
        {
            printf("Error in set sock opt reuser addr\n");
            exit(0);
        }
        else
            printf("Socket updated (reuse)\n");
    //--------------------------------------------------------------------------------------
    //  > Binding:
    //--------------------------------------------------------------------------------------
        struct sockaddr_in servaddr;

        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(HELLO_PORT);
        servaddr.sin_addr.s_addr = INADDR_ANY;

        int bindfd = bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

        if(bindfd == 0)
            printf("Binding successful...\n");
        else
        {
            printf("Binding failed\n");
            exit(0);
        }
    //--------------------------------------------------------------------------------------
    //  > ADD membership:
    //--------------------------------------------------------------------------------------
        struct ip_mreq mreq;

        mreq.imr_multiaddr.s_addr = inet_addr(HELLO_GROUP);
        mreq.imr_interface.s_addr = INADDR_ANY;

        int fd2 = setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));

        if(fd2 < 0)
        {
            printf("Error in add membership..\n");
            exit(0);
        }
        else
            printf("Add membership successful..\n");
    //--------------------------------------------------------------------------------------
    //  > Receive msg from server
    //--------------------------------------------------------------------------------------
        char buffer[1024];

        while(1)
        {
            int len = sizeof(servaddr);

            if(recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)&servaddr, &len) > 0)
                fputs(buffer, stdout);
        }
    //--------------------------------------------------------------------------------------
}