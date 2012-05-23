#include "Connection.h"
#include "../proto/riak.pb.h"
#include "Message.h"
#include <iostream>

namespace RiakSimpleClient {
    using namespace simpleriakclient;

    Connection::Connection(const char *ip_address){
        // convert ip from string to network byte order
        if (inet_aton( ip_address, &addr) == 0){
            throw "Invaid IP address";
        }

        // allocate memory for socket address info
        memset(&server_info, 0, sizeof(sockaddr_in));

        // copy address ino and set port
        memcpy( (char *)&server_info.sin_addr, &addr, sizeof(in_addr));
        server_info.sin_port = htons(8087);
        server_info.sin_family = AF_INET;

        // create tcp socket
        sock = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

        // connect
        if (connect( sock, (struct sockaddr *)&server_info, sizeof(sockaddr)) == -1){
            throw "Connection failed";
        }
    }

    Connection::~Connection(){
        std::cout << "Disconnected" << std::endl;
    }

    int Connection::send_msg ( char *message, char *buffer ){
        int bytes_recvd;

        if ( send( sock, message, sizeof(message), 0) < 5){
            std::cerr << "ERROR: Message sent too short" << std::endl;
            return -1;
        }

        // read header -> 5 bytes
        char length[4];
        char mc[1];

        bytes_recvd = recv( sock, length, 4, 0 );

        // get message length
        int32_t msg_length = ntohl( *((int32_t*)length) );

        if (msg_length <= 0){
            std::cerr << "ERROR: Invalid message length" << std::endl;
            return -1;
        }

        // allocate space for message
        buffer = (char*)realloc(buffer, msg_length * sizeof(char));

        bytes_recvd += recv( sock, mc, 1, 0); // message code
        bytes_recvd += recv( sock, buffer, msg_length - 1, 0); // rest of the message

        // size without message code
        return msg_length - 1;
    }

    int Connection::disconnect ( void ){
        return close( sock );
    }
}

