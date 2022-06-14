//This code is contributed by subindavid605@gmail.com
//KTU S6 Lab programs
//2022
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

#define port 8060

int sockfd, clientfd;
struct sockaddr_in server;

void initialize()
{

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        printf("Socket creation failed\n");
        return;
    }
    printf("Socket created successfully\n");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(port);

    if (connect(sockfd, (struct sockaddr *)&server, (socklen_t)sizeof(server)) < 0)
    {
        perror("Connect failed\n");
        return;
    }
    printf("Connect success\n");

    char msg[2000];
    while (1)
    {
    	fflush(stdin); fflush(stdout);
    	printf("Enter any HTTP request(eg www.google.com):\n");
    	scanf("%s",msg);
        //strcpy(msg, "www.google.com");
        send(sockfd, msg, sizeof(int) * strlen(msg), 0);
        sleep(2);
        strcpy(msg,"");
        if (recv(sockfd, msg, sizeof(char) * 2000, 0) > 0)
        {
            printf("%s\n", msg);
            perror(" ");
        }
    }
}

void main()
{
    initialize();
}
