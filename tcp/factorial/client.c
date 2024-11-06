#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
int main()
{
    int sd;
    socklen_t clinetlen;
    struct sockaddr_in serveraddr;
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_addr.s_addr=htonl(INADDR_ANY);
    serveraddr.sin_port=htons(8892);
    sd = socket(AF_INET,SOCK_STREAM,0);
    connect(sd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    while(1){
        char buffer[100];
        printf("Client :");
        fgets(buffer,sizeof(buffer),stdin);
        send(sd,buffer,sizeof(buffer),0);
        recv(sd,buffer,sizeof(buffer),0);
        printf("Server :%s",buffer);
    }
}