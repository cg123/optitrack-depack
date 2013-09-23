#include "client.h"
#include "api.h"

EXPORT_FUNC(NatNetClient*) natnetclient_init(uint32_t addr) {
    return new NatNetClient(addr);
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
