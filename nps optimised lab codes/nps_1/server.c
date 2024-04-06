#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<unistd.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<arpa/inet.h>

// socket
// bind
// listen
// accept

int main(){
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
    //  > Binding:
    //-----------------------------------------------------------------------------------------------------
        int bindfd = bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
        
        if(bindfd == 0)
		    printf("Binding Successfull\n");
    //-----------------------------------------------------------------------------------------------------
    //  > Listening:
    //-----------------------------------------------------------------------------------------------------
        int listenfd = listen(sockfd, 5);
    //-----------------------------------------------------------------------------------------------------
    //  > Accept the request
    //-----------------------------------------------------------------------------------------------------
        struct sockaddr_in cli;
        int len = sizeof(cli);

        int connfd = accept(sockfd, (struct sockaddr *)&cli, &len);

        if(connfd > 0)
        {
            char filename[1024];
            char buffer[1024];
            //-----------------------------------------------------------------------------------------------------
            //  > receive the filename from the client
            //-----------------------------------------------------------------------------------------------------

                recv(connfd, filename, 1024, 0);

                int openfd = open(filename, O_RDONLY);

                if(openfd < 0)
                {
                    printf("Error in openening the file\n");
                    exit(0);
                }   

                int n = read(openfd, buffer, 1024);

                if(n > 0)
                    send(connfd, buffer, n, 0);

                close(connfd);
            //-----------------------------------------------------------------------------------------------------


        }

        close(sockfd);
    

}