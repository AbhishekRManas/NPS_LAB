#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <sys/socket.h>

int main()
{

    //-----------------------------------------------------------------------------------------------------
    //  > socket creation
    //-----------------------------------------------------------------------------------------------------
        int sockfd = socket(AF_INET, SOCK_STREAM, 0);

        if(sockfd > 0)
            printf("The socket is created\n");
    //-----------------------------------------------------------------------------------------------------
    //  > address filling:
    //-----------------------------------------------------------------------------------------------------
        struct sockaddr_in servaddr;

        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(15001);
        servaddr.sin_addr.s_addr = INADDR_ANY;
    //-----------------------------------------------------------------------------------------------------
    //  > connect request:
    //-----------------------------------------------------------------------------------------------------
        int connected = connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

        if(connected == 0)
            printf("The connection was accepted\n");
    //-----------------------------------------------------------------------------------------------------
    //  > Read the file name:
    //-----------------------------------------------------------------------------------------------------
        char filename[1024];

        printf("Enter the file name:\n");
        scanf("%s", &filename);
        send(sockfd, filename, 1024, 0);
    //-----------------------------------------------------------------------------------------------------
    //  > Receive the file content:
    //-----------------------------------------------------------------------------------------------------
        char buffer[1024];

        if(recv(sockfd, buffer, 1024, 0) > 0){
            fputs(buffer, stdout);
        }
    //-----------------------------------------------------------------------------------------------------

	return close(sockfd);
}