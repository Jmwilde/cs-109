#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "../headers/TCPSocket.h"
#include "../headers/rule_engine.h"

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


    RuleEngine sri;
    sri.parseInput("FACT Father(John,Adam)");
    sri.parseInput("FACT Mother(Adam,Bob)");
    string commandLine = "RULE Parent($X,$Y):- OR Father($X,$Z) Mother($Z,$Y)"
    ofstream sri_file;
    char* remote_ip = (char*)"0.0.0.0";
    int port = 9999;

    cout << "\nWelcome to the Simple Rule Inference Engine!\n";

    TCPSocket client(remote_ip, port);

    char file_name[1024];
    memset(file_name,0,1024);
    sri.dump("send.sri");
    
    sri_file.open("file_name.sri");
    sri_file << commandLine+"\n";
    sri_file.close();
    const char * myBuffer = "file_name.sri";
    client.writeToSocket(myBuffer, strlen(myBuffer));
    client.readFromSocket(file_name, 1023);
    sri.socket_parse("file_name");
    sri.dump("final_file.sri");
    client.shutDown();

    // Constructs a client socket
    // char* remote_ip = (char*)"0.0.0.0";
    // int port = 9999;
    //
    // TCPSocket client(remote_ip, port);
    //
    // // Prints the client's address
    // cout << "My address is " << client.getMyAddress() << "." << endl;
    // cout << "My server's address is " << client.getRemoteAddress() << "." << endl;
}
