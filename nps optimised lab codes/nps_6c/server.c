#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

// void communicate(int sockfd, struct sockaddr *cli_addr, int cli_len)
// {
//     int n = 1;
//     char buff[1024];

//     while(1)
//     {
//         int addr_len = cli_len;

//         n = recvfrom(sockfd, buff, 1024, 0, cli_addr, &addr_len);

//         sendto(sockfd, buff, n, 0, cli_addr, addr_len);
//     }
// }

// int main()
// {
//     //--------------------------------------------------------------------------------------------------------------------
//     //  > Creating the socket:
//     //--------------------------------------------------------------------------------------------------------------------
//         int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

//         if(sockfd > 0)
//             printf("socket is created...\n");
//         else
//         {
//             printf("socket creation failed....\n");
//             exit(0);
//         }
//     //--------------------------------------------------------------------------------------------------------------------
//     //  > Fill the address structure:
//     //--------------------------------------------------------------------------------------------------------------------
//         struct sockaddr_in servaddr;

//         servaddr.sin_family = AF_INET;
//         servaddr.sin_port = htons(15001);
//         servaddr.sin_addr.s_addr = INADDR_ANY;
//     //--------------------------------------------------------------------------------------------------------------------
//     //  > Binding:
//     //--------------------------------------------------------------------------------------------------------------------
//         int bindfd = bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

//         if(bindfd == 0)
//             printf("binding successful....\n");
//         else 
//         {
//             printf("Binding failed...\n");
//             exit(0);
//         }
//     //--------------------------------------------------------------------------------------------------------------------
//     //  > Communicate:
//     //--------------------------------------------------------------------------------------------------------------------
//         struct sockaddr_in cli_addr;
        
//         communicate(sockfd, (struct sockaddr *)&cli_addr, sizeof(cli_addr));
//     //--------------------------------------------------------------------------------------------------------------------

// }

void communicate(int sockfd, struct sockaddr *cli, int len)
{
    char buffer[1024];

    while(1)
    {
        int len1 = len;

        recvfrom(sockfd, buffer, 1024, 0, cli, &len1);

        sendto(sockfd, buffer, sizeof(buffer), 0, cli, len1);
    }
}


int main()
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if(sockfd > 0)
        printf("socket is created...\n");
    else
    {
        printf("socket creation failed....\n");
        exit(0);
    }

    struct sockaddr_in servaddr;

    servaddr.sin_port = htons(15001);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;

    int bindfd = bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    if(bindfd == 0)
        printf("binding successful....\n");
    else 
    {
        printf("Binding failed...\n");
        exit(0);
    }

    struct sockaddr_in cli;

    communicate(sockfd, (struct sockaddr *)&cli, sizeof(cli));
}