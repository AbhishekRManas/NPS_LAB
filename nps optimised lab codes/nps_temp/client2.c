#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(sockfd > 0)
        printf("Socket created..\n");
    else
    {
        printf("Socket creation error...\n");
        exit(0);
    }

    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(15001);
    servaddr.sin_addr.s_addr = INADDR_ANY;



    int connected = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    if(connected == 0)
    {
        char buffer[1024];

        int flag = 0;

        while(1)
        {
            if(flag == 1)
            {
                printf("Client 2 : ");
                fgets(buffer, 1024, stdin);
                send(sockfd, buffer, 1024, 0);

                flag = 0;
            }
            else
            {
                recv(sockfd, buffer, 1024, 0);
                printf("Client 1 : ");
                fputs(buffer, stdout);

                flag = 1;
            }
        }
    }
    else
    {
        printf("connection failed..\n");
        exit(0);
    }
}
