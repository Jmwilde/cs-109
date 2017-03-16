#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "TCPSocket.h"

using namespace std;

void terminate_with_error (int sock)
{
    close (sock);
    perror("Error Binding Socket:");
    exit(1);

}

int main (int argc,char ** argv)
{
    if ( argc != 2)
    {
        printf ("Usage: ./client <server-address>\n");
        exit(1);
    }

    // Constructs a client socket
    TCPSocket client("0.0.0.0", 9999);

    // Prints the client's address
    cout << "My address is " << client.getMyAddress() << "." << endl;
    cout << "My server's address is " << client.getRemoteAddress() << "." << endl;

    char * myBuffer = "What's Up Dawg? \nBlaze to dis bitches!";
    client.writeToSocket(myBuffer, strlen(myBuffer));

    // int sock;
    // struct sockaddr_in serverAddr;
    // socklen_t sin_size = sizeof(struct sockaddr_in);

    // if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    //     {
    //     perror("Error Creating Socket");
    //     exit(1);
    // }
    // memset((char *) &serverAddr, 0,sizeof(serverAddr));
    // serverAddr.sin_family = AF_INET;
    // serverAddr.sin_port = htons(9999);
    // struct hostent *server = gethostbyname(argv[1]);
    // //cout << "Connecting client to IP: " << gethostbyname(argv[1]) << endl; 
    // if ( server == NULL ) terminate_with_error(sock);

    // memcpy((char *)&serverAddr.sin_addr.s_addr,(char *)server->h_addr, server->h_length);
    // memset(&(serverAddr.sin_zero), 0, 8);

    // if (connect(sock,(sockaddr *)&serverAddr,sizeof(serverAddr)) == -1 ) terminate_with_error(sock);
    // send (sock,"Hello from CMPS109!",strlen("Hello from CMPS109!"),0);
    // close(sock);
}
