#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<pthread.h>

void *recvm(void *client){
    int sd = *((int *)client);
    char msg[100];
    while(1)
    {
        recv(sd,msg,sizeof(msg),0);
        printf("CLI :%s",msg);
    }
}

int main()
{
    struct sockaddr_in server;
    pthread_t recvt;
    char sendmsg[30],clientname[30],tempmsg[60];
    int client = 0,sock = 0;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(9998);
    sock = socket(AF_INET,SOCK_STREAM,0);
    printf("Client Started\n");
    connect(sock,(struct sockaddr*)&server,sizeof(server));
    pthread_create(&recvt,NULL,recvm,&sock);
    while(fgets(sendmsg,30,stdin) > 0){
        send(sock,sendmsg,strlen(sendmsg),0);

    }
}