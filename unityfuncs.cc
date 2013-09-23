#include "client.h"

extern "C" NatNetClient* __cdecl natnetclient_init() {
    return new NatNetClient();
}