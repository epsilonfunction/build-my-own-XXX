
// socket: a primitive that handles connections. 
// appropriately should be called socket API. 
// allocates and returns a socket fd (handle).
//
// handle creates the connections. 
// handle must be closed to free up resources on OS.
// handles are a ABC.
//
// 
// fd = socket() -> obtain the socket handle
// bind (fd, address) -> sets the listening IP port via bind
// listen (fd) -> create listening socket
// while True:
// 	conn_fd = accept(fd)
// 	do_fn(conn_fd)
// 	close(conn_fd)
//
//TCP and UDP share the same socet API, send() & receive(), 
//	in UDP, send/receive is 1 packet,
//	in TCP, send/receive is appeneded to a byte stream
//
//	however, send/receive is analogous to read/write, read/writes cannot be naively shared across different handle types.
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ip.h>

using namespace std;

// refer to man socket.2 for how to create socket syscall
int fd = socket( AF_INET, SOCK_STREAM, 0); // -> obtain the socket handle
	// AF_INET -> IPv4 Protcol
	// SOCK_STREAM (a communication semantic) -> a form of sequenced, reliable, two-way, connection-based byte streams. aka. TCP protocol
	// third argument is a dummy and does nothing.

int val = 1;
setsockopt(fd, SOL_SOCKET, SO_REUSEADDR,&val, sizeof(val)); // this merely passes parameter to socket constructor, like bind(), actual socket has not been created yet.
	// 2nd & 3rd ags specify options
	// 4th args is option value
	// different options use different types, therefore sizeof(val) to specify size of option val
	// -> sets SO_RESUSEADDR := 1
		// relates to delayed packets and TCP TIME_WAIT. nontrivial
		// SO_RESUSEADDR is important as it allows for binidng to same IP:port after a restart. the contrary is undesirable for TCP.
struct sockaddr_in {
	uint16_t 	sin_family; // -> AF_INET
	uint16_t 	sin_port; // -> port in big-endian 
	struct 	in_addr sin_addr; // -> IPv4
};

struct in_addr {
	uint32_t	s_addr; // IPv4 in big-endian
}
// NOTE: endian-ness refers to how bytes are stored.
	// little endian : least significant byte comes first
	// big endian: 	most significant byte comes first
// most things are in little-endian, therefore big-endian inputs need to undergo byte-swap

uint32_t htonl(uint32_t hostlong); 	// CPU endian <=> big-endian
//uint16_t hton

// For IPv6
struct sockaddr_in6{
	uint16_t	sin6_family; 	// AF_INET6
	uint16_t	sin6_port;	// port in big-endian
	uint32_t	sin6_flowinfo;	// ignore according to tutorial
	struct in6_addr	sin6_addr; 	// IPv6 address
	uint32_t	sin6_scope_id;	// ignore according to tutorial
}
struct in6_addr {
	uint8_t		s6_addr[16];	// IPv6 addr in 16 char
}




struct sockaddr_in addr = {};
addr.sin_family = AF_INET;
addr.sin_port = htons(1234); 	// binding to ip port of 1234
addr.sin_addr.s_addr = htonl(0); 	// wildcard IP 0.0.0.0
int rv = bind(fd, (const struct sockaddr *)&addr, sizeof(addr));	// binds the sending to the receiving (ie. 'rv') with the address

if (rv) {die("bind()")};


bind (fd, address) -> sets the listening IP port via bind
listen (fd) -> create listening socket
while True:
 	conn_fd = accept(fd)
 	do_fn(conn_fd)
	close(conn_fd)
//
//
//
