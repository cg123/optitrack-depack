#ifndef OPTITRACK_CLIENT_H_
#define OPTITRACK_CLIENT_H_

#include <boost/asio.hpp>
#include "wire.h"

class NatNetClient {
public:
    NatNetClient(uint32_t addr);
	~NatNetClient();
    
	void SendPacket(uint32_t host, natnet_packet_t* msg);
	void Ping(uint32_t host);
    void ProcessFrame();

private:
	bool valid;
    boost::asio::io_service io;
	
	boost::asio::ip::udp::socket commandSocket;
	boost::asio::ip::udp::socket dataSocket;

    unsigned char buf[sizeof(natnet_packet_t)];
};

#endif//OPTITRACK_CLIENT_H_
