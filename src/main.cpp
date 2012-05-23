#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include "proto/riak.pb.h"
#include "riaksimpleclient/Connection.h"
#include "riaksimpleclient/Message.h"

using namespace std;
using namespace RiakSimpleClient;

int main(int argc, const char *argv[])
{

    GOOGLE_PROTOBUF_VERIFY_VERSION;

    if (argc < 2){
        cerr << "Usage: " << argv[0] << " <ip_addr>" << endl;
        return -1;
    }

    Connection *conn;

    try {
        conn = new Connection(argv[1]);
    }
    catch (const char* e){
        cerr << "Exception: " << e << endl;
        return -1;
    }

    if (conn){
        cout << "Successfuly connected." << endl;
    }

    Message::get_server_info *operation;
    operation = new Message::get_server_info;

    char * buffer = (char *)malloc(0);
    int buffer_size = (&operation->request())->serialize(buffer);

    char *msg_buffer = (char *)malloc(0);
    int msg_size = conn->send_msg( buffer, msg_buffer );

    if (!(&operation->response())->ParseFromArray(msg_buffer, msg_size)){
        std::cerr << "Failed to parse" << std::endl;
        return -1;
    }
    else {
        std::cout << "Node: " << (&operation->response())->node() << std::endl;
        std::cout << "Version: " << (&operation->response())->server_version() << std::endl;
    }

    conn->disconnect();

    // clean up
    delete operation;
    delete conn;
    free(msg_buffer);

    return 0;
}

