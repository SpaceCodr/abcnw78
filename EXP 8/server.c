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
struct sockaddr_in server, client;

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
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr *)&server, (socklen_t)sizeof(server)) < 0)
    {
        printf("Bind failed\n");
        return;
    }

    printf("Bind success\n");

    listen(sockfd, 5);
    printf("listening...\n");
    int len=sizeof(client);
    
    clientfd = accept(sockfd, (struct sockaddr *)&client, (socklen_t*) &len);
    if (clientfd < 0)
    {
         printf("Accept failed\n");
         return;
    }

    printf("Accept success\n");

    while (1)
    {
        char msg[100];
        if (recv(clientfd,msg,sizeof(char)*100,0)>0){
            printf("%s\n",msg);
        }
        char retmsg[100];
        strcpy(retmsg,"ping ");
        strcat(retmsg,msg);
        strcat(retmsg," -c 5 > output.txt");
        
        system(retmsg);
        
        printf("Fetching data...\n");
        sleep(2);
        
        char temp[200];  char data[2000];
        FILE *f;
        f=fopen("output.txt","r");
        
        while (!feof(f)){
	        fflush(stdin); fflush(stdout);
        	fscanf(f,"%s",temp); //printf("%s",data);
        	strcat(data,temp);
        }
        //printf("%s",data);
        send(clientfd,data,sizeof(char)*strlen(data),0);
        //break;
    }
}

void main()
{
    initialize();
}
