#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<pthread.h>

int clients[100];
int n=0;
pthread_mutex_t mutex;

void sentoall(char *msg,int curr)
{
    pthread_mutex_lock(&mutex);
    for(int i =0;i<n;i++){
        if(clients[i]!=curr){
            send(clients[i],msg,sizeof(msg),0);
        }
    }
    pthread_mutex_unlock(&mutex);
}
void *recvm(void *client)
{
    int sk = *((int *)client);
    while(1){
        char msg[100];
        recv(sk,msg,sizeof(msg),0);
        sentoall(msg,sk);
    }
}

int main(){
    int client=0,sockett=0;
    struct sockaddr_in serveraddr,clientaddr;
    pthread_t recvmp;
    sockett = socket(AF_INET,SOCK_STREAM,0);
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_addr.s_addr=htonl(INADDR_ANY);
    serveraddr.sin_port=htons(9998);
    bind(sockett,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    listen(sockett,20);
    while(1){
        client = accept(sockett,NULL,NULL);
        pthread_mutex_lock(&mutex);
        clients[n++] = client;
        pthread_mutex_unlock(&mutex);
        pthread_create(&recvmp,NULL,&recvm,&client);
    }
}