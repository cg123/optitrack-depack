#ifndef OPTITRACK_WIRE_H_
#define OPTITRACK_WIRE_H_

#include <stdint.h>

typedef enum {
    NAT_PING = 0,
    NAT_PINGRESPONSE = 1,
    NAT_REQUEST = 2,
    NAT_RESPONSE = 3,
    NAT_REQUEST_MODELDEF = 4,
    NAT_MODELDEF = 5,
    NAT_REQUEST_FRAMEOFDATA = 6,
    NAT_FRAMEOFDATA = 7,
    NAT_MESSAGESTRING = 8,
    NAT_UNRECOGNIZED_REQUEST = 100
} natnet_msg_id_t;

typedef struct {
    uint16_t type;
    uint16_t sz;
} natnet_msg_header_t;

#define MAX_NAMELENGTH 256
typedef struct {
    char name[MAX_NAMELENGTH];
    char app_version[4];
    char natnet_version[4];
} natnet_sender_t;

#endif//OPTITRACK_WIRE_H_
