//This code is contributed by subindavid605@gmail.com
//KTU S6 Lab programs
//2022
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define port 8080

static int sockfd;
struct sockaddr_in server;


void* receiveMsg(void * arg){                                                                                
    while (1){
        char *recmsg=(char *)malloc(sizeof(char)*100);
        recv(sockfd,recmsg,sizeof(char)*50,0);
        if (strlen(recmsg)>0){
            fflush(stdin);  fflush(stdout);
            printf("%s\n",recmsg);
        }
        strcpy(recmsg,"");
        sleep(1);
    }
}

void * sendMsg(void * arg){
    int flag=1;
    int started=0;

    while (1){
        
        char *msg=(char *)malloc(sizeof(char)*100);

        if (flag){
            fflush(stdin);  fflush(stdout);
            printf("Enter message(1 word) to be sent(type start to initiate the process):\n");
            scanf("%s",msg); sleep(1);
            if (!strcmp(msg,"start") && !started){
                started=1;
                flag=0;
            }
            else{
                fflush(stdin);  fflush(stdout);
                printf("Enter a valid message!!\n");
            }
        }
        else{
            fflush(stdin);  fflush(stdout);
            printf("Enter message(1 word) to be sent(type stop to stop sending):\n");
            scanf("%s",msg);
            if (!strcmp(msg,"stop") && started){
                started=0;
                flag=1;
            }
            else{
                char smsgs[100];
                strcpy(smsgs,"Message from client1: ");
                strcat(smsgs,msg);
                send(sockfd,smsgs,sizeof(char)*strlen(smsgs),0);         
                smsgs[0]='\0';  
            }
        }
        strcpy(msg,"");
        sleep(1);
    }
}   

void main(){

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if (sockfd==-1){
        perror("Socket creation failed!!\n");
        return;
    }
    else{
        printf("Socket created successfully\n");
    }

    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(port);

    if (connect(sockfd,(struct sockaddr*)&server,(socklen_t)sizeof(server))<0){
        perror("Connection failed!!\n");
    }
    printf("Connection success\n");

    pthread_t t2;
    pthread_create(&t2,NULL,receiveMsg,NULL);

    pthread_t t1;
    pthread_create(&t1,NULL,sendMsg,NULL);

    pthread_join(t1,NULL);
}