#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<arpa/inet.h>

// void communicate(FILE *fp, int sockfd, struct sockaddr *servaddr, int addrlen)
// {
//     char buff[1024];

//     while(fgets(buff, 1024, fp) != NULL)
//     {
//         sendto(sockfd, buff, sizeof(buff), 0, servaddr, addrlen);

//         if(recvfrom(sockfd, buff, sizeof(buff), 0, NULL, NULL) > 0)
//             fputs(buff, stdout);
//     }

//     printf("End of function\n");
// }

void communicate(FILE *fp, int sockfd, struct sockaddr *serv, int len)
{
    char buffer[1024];

    while(1)
    {
        printf("Enter a message to server : ");
        
        while(fgets(buffer, 1024, fp) > 0)
        {
            sendto(sockfd, buffer, sizeof(buffer), 0, serv, len);

            if(recvfrom(sockfd, buffer, 1024, 0, serv, &len) > 0)
                fputs(buffer, stdout);
        }
    }
}

int main()
{
    //---------------------------------------------------------------------------------------------------
    //  > Socket creation
    //---------------------------------------------------------------------------------------------------
        int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

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
    //  > communicate with server:
    //--------------------------------------------------------------------------------------------------------------------
        communicate(stdin, sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    //--------------------------------------------------------------------------------------------------------------------



}