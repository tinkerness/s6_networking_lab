#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

int main(int argc, char* argv[])
{
    // create udp socket using - socket(domain,type,protocol)
    struct sockaddr_in server,client;

    if (argc != 3)
        printf("incorrect input format\n");

    int sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if (sockfd == -1) {
        printf("error in socket()\n");
    }
    else
        printf("socket created\n");

    // set server's address and port number 
    // # port number is at 2nd index
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[2]));

    // read message form user using fgets() & store it in buffer
    char buffer[100];
    printf("enter message to be sent to server : ");

    fgets(buffer,100,stdin);
    printf("message entered: %s\n",buffer);
    
    // send message to server using sendto(socket,buff,size,flag,dest_addr,dest_len) & then terminate
    if(sendto(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&server,sizeof(server))<0)
        printf("Error in sendto");
    else
        printf("message sent successfully\n");

    return 0;
}