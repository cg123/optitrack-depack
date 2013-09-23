#include "client.h"

#define EXPORT_FUNC(__type__) extern "C" __type__ __cdecl

EXPORT_FUNC(NatNetClient*) natnetclient_init() {
    return new NatNetClient();
}

EXPORT_FUNC(void) natnetclient_ping(NatNetClient* self, uint32_t host) {
	self->Ping(host);
}

EXPORT_FUNC(void) natnetclient_process_frame(NatNetClient* self) {
	self->ProcessFrame();
}

EXPORT_FUNC(void) natnetclient_destroy(NatNetClient* self) {
	delete self;
}
