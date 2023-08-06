#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

int main(int argc, char* argv[])
{
    // create udp socket using - socket(domain,type,protocol)
    struct sockaddr_in server,client;

    if (argc != 2)
        printf("incorrect input format");

    int sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if (sockfd == -1) {
        printf("error in socket()\n");
    }
    else
        printf("socket created\n");

    // set server's address and port number
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[1]));

    // bind socket to server's address using -  bind(socket,server_address,address_len)
    if (bind(sockfd,(struct sockaddr*)&server,sizeof(server)) < 0) {
        printf("error in bind()\n");
    }
    else
        printf("bind successful\n");

    // wait for datagram packets
    char buff[100];
    socklen_t server_len = sizeof(server);
    printf("server waiting...\n");

    // receive packets using -  recvfrom(socket,buff,max_size,flag,s_addr,addr_len)
    if (recvfrom(sockfd,buff,100,0,(struct sockaddr*)&server,&server_len) < 0) {
        printf("error in recvfrom()\n");
    }
    // print the message
    printf("got a datagram: %s\n",buff);
        
    return 0;
}
