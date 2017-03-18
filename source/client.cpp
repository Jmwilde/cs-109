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
    string commandLine = "RULE Parent($X,$Y):- AND Father($X,$Z) Mother($Z,$Y)";
    ofstream sri_file;
    char* remote_ip = (char*)"0.0.0.0";
    int port = 9999;

    cout << "\nWelcome to the Simple Rule Inference Engine!\n";

    // user inputs a command, and hits Enter/Return
    // terminates when user inputs 'x'

    // while(commandLine != "x"){
      TCPSocket client(remote_ip, port);
      char file_name[1024];
      memset(file_name,0,1024);
      // cout << "\nInput any of the following commands:" << endl;
      // cout << "- LOAD 'filename.sri'" << endl;
      // cout << "- DUMP 'filename.sri'" << endl;
      // cout << "- FACT 'FactName(A,B)'" << endl;
      // cout << "- RULE 'RuleName($A,$B)'" << endl;
      // cout << "- INFERENCE 'Query($A,$B)'" << endl;
      // cout << "- DROP 'Query'" << endl;
      // cout << "- Enter 'x' to terminate\n" << endl;
      // getline(cin, commandLine);
      // if(commandLine == "") continue;
      // if(commandLine == "x") break;
      sri.dump("file_name.sri");
      sri_file.open("file_name.sri", ios::app);
      sri_file << commandLine+"\n";
      sri_file.close();
      const char * myBuffer = "file_name.sri";
      client.writeToSocket(myBuffer, strlen(myBuffer));
      client.readFromSocket(file_name, 1023);
      sri.socket_parse("file_name");
      sri.dump("final_file.sri");
      client.shutDown();
    // }

    cout << "\nBye!" << endl;

    // Constructs a client socket
    // char* remote_ip = (char*)"0.0.0.0";
    // int port = 9999;
    //
    // TCPSocket client(remote_ip, port);
    //
    // // Prints the client's address
    // cout << "My address is " << client.getMyAddress() << "." << endl;
    // cout << "My server's address is " << client.getRemoteAddress() << "." << endl;
    //
    // ofstream output;
    // output.open("new.txt");
    // output << "Hello Cruel World!\n";
    // output.close();
    //
    // const char * myBuffer = "testcase2.sri";
    // client.writeToSocket(myBuffer, strlen(myBuffer));

    // NOTE: Both the server and the client have to be in the same directory
    // for the server to be able to open the file...

    // char contents[1024]; // A buffer for holding the file name
    // memset(contents,0,1024); // Initialize the buffer
    // int read_bytes = client.readFromSocket(contents,1023); // read from socket the file name to be fetched
    // if( read_bytes > 0)
    // {
    //     cout << "Received file contents: \n";
    //     cout << contents << endl;
    // }

    // while(true)
    // {

    // }



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
