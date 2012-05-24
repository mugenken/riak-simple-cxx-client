#include "../proto/riak.pb.h"
#include <google/protobuf/message_lite.h>
#include <arpa/inet.h> // for htonl to serialize message length

namespace RiakSimpleClient {
namespace Message {
    using namespace simpleriakclient;
    using namespace google::protobuf;

    typedef unsigned char mc_t;

    // riak api message codes
    static const mc_t RPB_ERROR_RESP           = 0;
    static const mc_t RPB_PING_REQ             = 1;
    static const mc_t RPB_PING_RESP            = 2;
    static const mc_t RPB_GET_CLIENT_ID_REQ    = 3;
    static const mc_t RPB_GET_CLIENT_ID_RESP   = 4;
    static const mc_t RPB_SET_CLIENT_ID_REQ    = 5;
    static const mc_t RPB_SET_CLIENT_ID_RESP   = 6;
    static const mc_t RPB_GET_SERVER_INFO_REQ  = 7;
    static const mc_t RPB_GET_SERVER_INFO_RESP = 8;
    static const mc_t RPB_GET_REQ              = 9;
    static const mc_t RPB_GET_RESP             = 10;
    static const mc_t RPB_PUT_REQ              = 11;
    static const mc_t RPB_PUT_RESP             = 12;
    static const mc_t RPB_DEL_REQ              = 13;
    static const mc_t RPB_DEL_RESP             = 14;
    static const mc_t RPB_LIST_BUCKETS_REQ     = 15;
    static const mc_t RPB_LIST_BUCKETS_RESP    = 16;
    static const mc_t RPB_LIST_KEYS_REQ        = 17;
    static const mc_t RPB_LIST_KEYS_RESP       = 18;
    static const mc_t RPB_GET_BUCKET_REQ       = 19;
    static const mc_t RPB_GET_BUCKET_RESP      = 20;
    static const mc_t RPB_SET_BUCKET_REQ       = 21;
    static const mc_t RPB_SET_BUCKET_RESP      = 22;
    static const mc_t RPB_MAP_RED_REQ          = 23;
    static const mc_t RPB_MAP_RED_RESP         = 24;


    class empty_message {};
    int message_serialize( mc_t code, char *buffer, MessageLite *message );
    int message_deserialize( mc_t code, char *buffer, MessageLite *message );

    template <mc_t code, class T=empty_message>
        struct message : public T {
            static const int mc = code;
            int serialize( char *buffer ){
                return message_serialize( code, buffer, this);
            }
            int deserialize( char *buffer ){
                return message_deserialize( code, buffer, this);
            }
        };

    typedef message<RPB_ERROR_RESP, RpbErrorResp> error_resp;

    typedef message<RPB_PING_REQ, RpbPingReq> ping_req;
    typedef message<RPB_PING_RESP, RpbPingResp> ping_resp;

    typedef message<RPB_GET_CLIENT_ID_REQ, RpbGetClientIdReq> get_client_id_req;
    typedef message<RPB_GET_CLIENT_ID_RESP, RpbGetClientIdResp> get_client_id_resp;

    typedef message<RPB_SET_CLIENT_ID_REQ, RpbSetClientIdReq> set_client_id_req;
    typedef message<RPB_SET_CLIENT_ID_RESP, RpbSetClientIdResp> set_client_id_resp;

    typedef message<RPB_GET_SERVER_INFO_REQ, RpbGetServerInfoReq> get_server_info_req;
    typedef message<RPB_GET_SERVER_INFO_RESP, RpbGetServerInfoResp> get_server_info_resp;

    typedef message<RPB_GET_REQ, RpbGetReq> get_req;
    typedef message<RPB_GET_RESP, RpbGetResp> get_resp;

    typedef message<RPB_PUT_REQ, RpbPutReq> put_req;
    typedef message<RPB_PUT_RESP, RpbPutResp> put_resp;

    typedef message<RPB_DEL_REQ, RpbDelReq> del_req;
    typedef message<RPB_DEL_RESP, RpbDelResp> del_resp;

    typedef message<RPB_LIST_BUCKETS_REQ, RpbListBucketReq> list_buckets_req;
    typedef message<RPB_LIST_BUCKETS_RESP, RpbListBucketsResp> list_buckets_resp;

    typedef message<RPB_LIST_KEYS_REQ, RpbListKeysReq> list_keys_req;
    typedef message<RPB_LIST_KEYS_RESP, RpbListKeysResp> list_keys_resp;

    typedef message<RPB_GET_BUCKET_REQ, RpbGetBucketReq> get_bucket_req;
    typedef message<RPB_GET_BUCKET_RESP, RpbGetBucketResp> get_bucket_resp;

    typedef message<RPB_SET_BUCKET_REQ, RpbSetBucketReq> set_bucket_req;
    typedef message<RPB_SET_BUCKET_RESP, RpbSetBucketResp> set_bucket_resp;

    typedef message<RPB_MAP_RED_REQ, RpbMapRedReq> map_red_req;
    typedef message<RPB_MAP_RED_RESP, RpbMapRedResp> map_red_sesp;

    template <class Request, class Response>
        class operation {
            public:
                typedef Request  request_type;
                typedef Response response_type;
                static const mc_t request_code  = request_type::mc;
                static const mc_t response_code = response_type::mc;
                Request  &request()  { return _request;  }
                Response &response() { return _response; }
            private:
                Request _request;
                Response _response;
        };

    typedef operation<ping_req, ping_resp> ping;
    typedef operation<get_client_id_req, get_client_id_resp> get_client_id;
    typedef operation<set_client_id_req, set_client_id_resp> set_client_id;
    typedef operation<get_server_info_req, get_server_info_resp> get_server_info;
    typedef operation<get_req, get_resp> get;
    typedef operation<put_req, put_resp> put;
    typedef operation<del_req, del_resp> del;
    typedef operation<list_buckets_req, list_buckets_resp> list_buckets;
    typedef operation<list_keys_req, list_keys_resp> list_keys;
    typedef operation<get_bucket_req, get_bucket_resp> get_bucket;
    typedef operation<set_bucket_req, set_bucket_resp> set_bucket;
    typedef operation<map_red_req, map_red_sesp> map_reduce;

}
}
