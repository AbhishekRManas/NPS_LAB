// #include<stdio.h>
// #include<stdlib.h>
// #include<unistd.h>
// #include<sys/socket.h>
// #include<arpa/inet.h>

// void communicate(int conn_fd)
// {
//     int n = 1;
//     char buff[1024];

//     do 
//     {
//         while(n = recv(conn_fd, buff, 1024, 0) > 0)
//         {
//             send(conn_fd, buff, n, 0);
//         }
//     } while(n > 0);
// }

// int main()
// {
//     //--------------------------------------------------------------------------------------------------------------------
//     //  > Creating the socket:
//     //--------------------------------------------------------------------------------------------------------------------
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
//     //  > Listening:
//     //--------------------------------------------------------------------------------------------------------------------
//         int listenfd = listen(sockfd, 5);

//         if(listenfd == 0)
//             printf("listening....\n");
//         else 
//         {
//             printf("Listening failed...\n");
//             exit(0);
//         }
//     //--------------------------------------------------------------------------------------------------------------------
//     //  > Accept connection from clients:
//     //--------------------------------------------------------------------------------------------------------------------
//         char buffer1[1024], buffer2[1024];
//         struct sockaddr_in cliaddr1, cliaddr2;

//         int len1 = sizeof(cliaddr1);
//         int len2 = sizeof(cliaddr2);

//         int connfd1 = accept(sockfd, (struct sockaddr *)&cliaddr1, &len1);
//         int connfd2 = accept(sockfd, (struct sockaddr *)&cliaddr2, &len2);
//     //--------------------------------------------------------------------------------------------------------------------
//     //  > First client1 messages and client2 replies:
//     //--------------------------------------------------------------------------------------------------------------------
//         while(1)
//         {
//             recv(connfd1, buffer1, 1024, 0);
//             printf("From client1 : %s\n", buffer1);
//             send(connfd2, buffer1, 1024, 0);

//             recv(connfd2, buffer2, 1024, 0);
//             printf("From client2 : %s\n", buffer2);
//             send(connfd1, buffer2, 1024, 0);
//         }
//     //--------------------------------------------------------------------------------------------------------------------





// }

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>

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

    servaddr.sin_port = htons(15001);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;

    int bindfd = bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    if(bindfd == 0)
        printf("Binding successful\n");
    else 
    {
        printf("Binding failed..\n");
        exit(0);
    }

    int listenfd = listen(sockfd, 5);

    if(listenfd == 0)
        printf("listening......\n");
    else
    {
        printf("Listening error....\n");
        exit(0);
    }

    char buffer1[1024];
    char buffer2[1024];

    struct sockaddr_in cli1;
    struct sockaddr_in cli2;

    int len1 = sizeof(cli1);
    int len2 = sizeof(cli2);

    int connfd1 = accept(sockfd, (struct sockaddr *)&cli1, &len1);
    int connfd2= accept(sockfd, (struct sockaddr *)&cli2, &len2);

    printf("Hello0\n");
    while(1)
    {
        printf("Hello0\n");

        int n1 = recv(connfd1, buffer1, 1024, 0);
        printf("From client1 : %s\n", buffer1);
        send(connfd2, buffer1, n1, 0);

        int n2 = recv(connfd2, buffer2, 1024, 0);
        printf("From client2 : %s\n", buffer2);
        send(connfd1, buffer2, n2, 0);
    }
}