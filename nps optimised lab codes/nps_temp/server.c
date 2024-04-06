#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

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

    struct sockaddr_in addr;
    addr.sin_addr.s_addr = inet_addr(GROUP);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);

    char buff[1024];

    while(1)
    {
        printf("Enter the message to multicast: ");
        fgets(buff, 1024, stdin);

        sendto(sockfd, buff, 1024, 0, (struct sockaddr *)&addr, sizeof(addr));
    }
}