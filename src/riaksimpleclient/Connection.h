#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <string.h>

namespace RiakSimpleClient {
    class Connection {
        private:
            int sock;
            struct sockaddr_in server_info;
            struct in_addr addr;
        public:
            Connection(const char *ip_address);
            ~Connection();
            int send_msg( char *message, char *buffer );
            int disconnect();
    };
}

