#include "Message.h"
#include <iostream>

namespace RiakSimpleClient {
namespace Message {
    int message_serialize ( mc_t code, char *buffer, MessageLite * message ){
        // 4 byte length + 1 byte mc + message size
        buffer = (char*)realloc(buffer, message->ByteSize() + sizeof(int32_t) + sizeof(char));
        char * serialized_buffer = (char *)malloc(message->ByteSize());

        if (!message->SerializeToArray(serialized_buffer, message->ByteSize())){
            return -1;
        }

        int riak_msg_length_i = htonl(message->ByteSize() + 1);
        char * riak_msg_length = (char *)&riak_msg_length_i;

        // put it together
        memcpy(buffer, riak_msg_length, sizeof(char) * 4);
        memcpy(buffer + sizeof(char) * 4, &code, sizeof(char));
        memcpy(buffer + sizeof(char) * 5, serialized_buffer, message->ByteSize());

        // clean up
        free(serialized_buffer);

        return 5 * sizeof(char) + message->ByteSize();
    }

    int message_deserialize ( mc_t code, char *buffer, MessageLite * message ){
        return 0xdead;
    }
}
}
