#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>

void fact(char *str){
    int n = atoi(str);
    int fact = 1;
    for(int i=1;i<=n;i++){
        fact = fact*i;
    }
    sprintf(str,"%d",fact);
}

int main()
{
    int sd,lsd;
    socklen_t clientlen;
    struct sockaddr_in serveraddr,clientaddr;
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_addr.s_addr=htonl(INADDR_ANY);
    serveraddr.sin_port=htons(8892);
    sd = socket(AF_INET,SOCK_STREAM,0);
    bind(sd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    listen(sd,5);
    printf("Server Running\n");
    clientlen=sizeof(clientaddr);
    lsd = accept(sd,(struct sockaddr*)&clientaddr,&clientlen);
    printf("Client Connected\n");
    while(1){
        char buffer[100];
        recv(lsd,buffer,sizeof(buffer),0);
        fact(buffer);
        printf("Client :%s\n",buffer);
        //strcpy(buffer,"");
        // printf("Sever :");
        //fgets(buffer,sizeof(buffer),stdin);
        send(lsd,buffer,100,0);
    }

}
