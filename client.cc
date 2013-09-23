#include "client.h"
#include <boost/exception/all.hpp>

using namespace boost::asio;
using namespace boost::system;

#define MULTICAST_ADDRESS		"239.255.42.99"     // IANA, local network
#define PORT_COMMAND            1510
#define PORT_DATA  			    1511                // Default multicast group
#define RCVBUF_SIZE				0x100000

NatNetClient::NatNetClient() : commandSocket(io), dataSocket(io), valid(false) {
	// CreateCommandSocket() 
	ip::udp::endpoint command_ep(ip::address_v4::any(), PORT_COMMAND);
	commandSocket.open(command_ep.protocol());
	commandSocket.bind(command_ep);
	commandSocket.set_option(ip::udp::socket::broadcast(true));
	commandSocket.set_option(ip::udp::socket::receive_buffer_size(RCVBUF_SIZE));

	// Random junk in main()
	ip::udp::endpoint data_ep(ip::address_v4::any(), PORT_DATA);
	dataSocket.set_option(ip::udp::socket::reuse_address(true));
	dataSocket.open(data_ep.protocol());
	dataSocket.bind(data_ep);
	dataSocket.set_option(ip::multicast::join_group(ip::address::from_string(MULTICAST_ADDRESS)));
	dataSocket.set_option(ip::udp::socket::receive_buffer_size(RCVBUF_SIZE));
}

void NatNetClient::Ping(uint32_t host) {
	natnet_packet_t packet;
	packet.header.type = NAT_PING;
	packet.header.sz = 0;
	SendPacket(host, &packet);
}

void NatNetClient::SendPacket(uint32_t host, natnet_packet_t* msg)
{
	char* rawBytes = reinterpret_cast<char*>(msg);
	if (commandSocket.send_to(buffer(rawBytes, sizeof(natnet_msg_header_t) + msg->header.sz), ip::udp::endpoint(ip::address_v4(host), PORT_COMMAND)) < sizeof(natnet_msg_header_t)) {
		boost::throw_exception(std::runtime_error("Unable to send message"));
	}
}

void NatNetClient::ProcessFrame()
{
	// Process the command socket
	ip::udp::endpoint sender;
	int bytesRead = commandSocket.receive_from(buffer(buf, sizeof(buf)), sender);
	if (bytesRead > 0)
	{
		natnet_packet_t* msg = reinterpret_cast<natnet_packet_t*>(&buf[0]);
		std::cout << "[Command] Received command from " << sender.address().to_string() << ": Type=" << msg->header.type << ", Size=" << msg->header.sz << "\n";
	}
	// Process the data socket
	bytesRead = dataSocket.receive_from(buffer(buf, sizeof(buf)), sender);
	if (bytesRead > 0)
	{
		natnet_packet_t* msg = reinterpret_cast<natnet_packet_t*>(&buf[0]);
		std::cout << "[Data] Received data from " << sender.address().to_string() << ": Type=" << msg->header.type << ", Size=" << msg->header.sz << "\n";
	}
}
