// #include<stdio.h>
// #include<stdlib.h>
// #include<sys/socket.h>
// #include<sys/types.h>
// #include<unistd.h>
// #include<arpa/inet.h>

// int main()
// {
//     //---------------------------------------------------------------------------------------------------
//     //  > Socket creation
//     //---------------------------------------------------------------------------------------------------
//         int sockfd = socket(AF_INET, SOCK_STREAM, 0);

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
//     //  > call connect to server:
//     //--------------------------------------------------------------------------------------------------------------------

//         int connected = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

//         char buffer[1024];
//         int flag = 0;

//         while(1)
//         {
//             if(flag == 1)
//             {
//                 recv(sockfd, buffer, 1024, 0);
//                 printf("Client 2 : %s\n", buffer);

//                 flag = 0;
//             }
//             else 
//             {
//                 printf("Client 1 : ");
//                 gets(buffer);
//                 send(sockfd, buffer, sizeof(buffer), 0);

//                 flag = 1;
//             }
            
//         }
//     //--------------------------------------------------------------------------------------------------------------------



// }

#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>


int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(sockfd > 0)
        printf("Socket created...\n");
    else
    {
        printf("Socket creation failed...\n");
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
            if(flag == 0)
            {
                printf("Client 1 : ");
                gets(buffer);
                send(sockfd, buffer, sizeof(buffer), 0);

                flag = 1;
            }
            else
            {
                printf("Client 2 : ");
                recv(sockfd, buffer, 1024, 0);
                printf("%s\n", buffer);

                flag = 0;
            }
        }
    }
    else
        printf("Connection failed....\n");
}