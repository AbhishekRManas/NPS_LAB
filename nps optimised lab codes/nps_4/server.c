/*-------------------------------------------------------------------------------------------------------
    steps mulitirouting:

        CLIENT :

            1. socket
            2. socket manipulation to reuse addr
            3. bind
            4. mreq + IPPROTO_IP manipulation to add member
            5. communicate

        SERVER :

            1. socket
            2. addr
            3. no bind
            4. sendto

-------------------------------------------------------------------------------------------------------*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>

#define HELLO_GROUP "225.0.0.37"
#define HELLO_PORT 12345

int main()
{
    //-----------------------------------------------------------------------------------------------------
    //  > Socket creation:
    //-----------------------------------------------------------------------------------------------------
        int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

        if(sockfd > 0)
            printf("Socket created.....\n");
        else
        {
            printf("Socket creation failed...\n");
            exit(0);
        }
    //-----------------------------------------------------------------------------------------------------
    //  > addr structure filling:
    //-----------------------------------------------------------------------------------------------------
        struct sockaddr_in addr;
        
        addr.sin_addr.s_addr = inet_addr(HELLO_GROUP);
        addr.sin_family = AF_INET;
        addr.sin_port = htons(HELLO_PORT);
    //-----------------------------------------------------------------------------------------------------
    //  > send messages to group:
    //-----------------------------------------------------------------------------------------------------
        char buff[1024];

        while(1)
        {
            printf("Enter a message to mulicast : ");
            fgets(buff, 1024, stdin);

            sendto(sockfd, buff, 1024, 0, (struct sockaddr *)&addr, sizeof(addr));
        }
    //-----------------------------------------------------------------------------------------------------
}