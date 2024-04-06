#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<arpa/inet.h>

// void communicate(FILE *fp, int sockfd)
// {
//     char buff[1024];

//     while(fgets(buff, 1024, fp) != NULL)
//     {
//         send(sockfd, buff, sizeof(buff), 0);

//         if(recv(sockfd, buff, sizeof(buff), 0) > 0)
//             fputs(buff, stdout);
//     }

//     printf("End of function\n");
// }




void communicate(FILE *fp, int sockfd)
{
    char buffer[1024];

    while(fgets(buffer, 1024, fp) != NULL)
    {
        send(sockfd, buffer, sizeof(buffer), 0);

        if(recv(sockfd, buffer, 1024, 0) > 0)
            fputs(buffer, stdout);
    }
}

int main()
{
    //---------------------------------------------------------------------------------------------------
    //  > Socket creation
    //---------------------------------------------------------------------------------------------------
        int sockfd = socket(AF_INET, SOCK_STREAM, 0);

        if(sockfd > 0)
            printf("socket is created...\n");
        else
        {
            printf("socket creation failed....\n");
            exit(0);
        }
    //--------------------------------------------------------------------------------------------------------------------
    //  > Fill the address structure:
    //--------------------------------------------------------------------------------------------------------------------
        struct sockaddr_in servaddr;

        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(15001);
        servaddr.sin_addr.s_addr = INADDR_ANY;
    //--------------------------------------------------------------------------------------------------------------------
    //  > call connect to server:
    //--------------------------------------------------------------------------------------------------------------------

        // int connected = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

        // if(connected == 0)
        // {
        //     printf("Connection was accepted by server %s\n", inet_ntoa(servaddr.sin_addr));

        //     communicate(stdin, sockfd);
        //     return close(sockfd);
        // }
        // else
        //     "Connection failed....\n";

        int connected = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

        if(connected == 0)
        {
            communicate(stdin, sockfd);
            close(sockfd);
        }
    //--------------------------------------------------------------------------------------------------------------------
}