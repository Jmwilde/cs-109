#include "../headers/Connection.h"
#include "../headers/rule_engine.h"
//Constructor: Call parent Thread Constructor

Connection::Connection(TCPSocket * p_tcpSocket): Thread(){
    tcpSocket = p_tcpSocket; // Set the TCP socket
    next_connection = NULL; // Set the next pointer to NULL
}

// A modifier that sets the pointer of the next connection
void Connection::setNextConnection(Connection * connection){
    next_connection = connection;
}

// A Selectot that returned a pointer to the next connection
Connection * Connection::getNextConnection (){
    return next_connection;
}

// Destructor: delete the TCP socket if set
Connection::~Connection(){
    if( tcpSocket != NULL ) delete (tcpSocket);
}

void * Connection::threadMainBody(void * arg) { // Main thread body for serving the connection
    RuleEngine sri;
    string last_line;
    string temp_line;
    string temp_name;
    string query;
    cout << "Running the threadMainBody of Connection\n\n";
    char file_name[1024]; // A buffer for holding the file name
    memset(file_name,0,1024); // Initialize the buffer

    int read_bytes = tcpSocket->readFromSocket(file_name,1023); // read from socket the file name to be fetched

    ifstream file_read(file_name);
    if(file_read.is_open()){
      while(getline(file_read, temp_line)){
        last_line = temp_line;
      }
      stringstream iss(last_line);
      getline(iss, temp_name, ' ');
      getline(iss, query, '(');
      file_read.close();
    }

    sri.load(file_name);
    sri.socket_dump("return_file.sri", query);
    const char * myBuffer = "return_file.sri";

    if( read_bytes > 0)
    { // If read successfully
        cout << "Successfully read the file\n";
        // Clean up file name
        if( file_name[strlen(file_name)-1]=='\n' || file_name[strlen(file_name)-1]== '\r') file_name[strlen(file_name)-1] = 0;
        if( file_name[strlen(file_name)-1]=='\n' || file_name[strlen(file_name)-1]=='\r') file_name[strlen(file_name)-1] = 0;

        FILE * f = fopen(file_name,"r"); // Try to open the file

        if( f != NULL) { // If opened
            cout << "Successfully opened the file\n";
            fseek (f,0,2); // Seek to the end of the file
            long fsize = ftell(f); // Get current location which represents the size
            char * buffer = (char *) calloc(fsize+1,sizeof(char)); // Allocate a buffer with the file size to read the content
            fseek (f,0,0); // Seek the beginning of the file
            fread(buffer,1,fsize,f); // Read the whole file into the buffer
            cout << "File contents: \n" << buffer << endl;
            tcpSocket->writeToSocket(myBuffer,strlen(myBuffer)); // Write the buffer to the socket
            free(buffer); // Free the buffer
            fclose(f); // Close the file
        }
        else {
            perror("Error With File\n"); // Print an error message
            tcpSocket->writeToSocket("Contents: Error\n",6);// Write error to the socket
        }
    }
    tcpSocket->shutDown(); // Shutdown the TCP Socket
    arg = NULL;
    return arg;
}
