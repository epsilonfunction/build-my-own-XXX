
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ip.h>

using namespace std;

int main() {
	// Step 1: obtain a socket handle
	// refer to man socket.2 for how to create socket syscall
	int fd = socket( AF_INET, SOCK_STREAM, 0); // -> obtain the socket handle
		// AF_INET -> IPv4 Protcol
		// SOCK_STREAM (a communication semantic) -> a form of sequenced, reliable, two-way, connection-based byte streams. aka. TCP protocol
		// third argument is a dummy and does nothing.

	// Step 2: Set Socket Options
	int val = 1;
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR,&val, sizeof(val)); // this merely passes parameter to socket constructor, like bind(), actual socket has not been created yet.
		// 2nd & 3rd ags specify options
		// 4th args is option value
		// different options use different types, therefore sizeof(val) to specify size of option val
		// -> sets SO_RESUSEADDR := 1
			// relates to delayed packets and TCP TIME_WAIT. nontrivial
			// SO_RESUSEADDR is important as it allows for binidng to same IP:port after a restart. the contrary is undesirable for TCP.

	// Step 3: Bind to address
	struct sockaddr_in addr = {};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1234); 	// binding to ip port of 1234
	addr.sin_addr.s_addr = htonl(0); 	// wildcard IP 0.0.0.0
	int rv = bind(fd, (const struct sockaddr *)&addr, sizeof(addr));	// binds the sending to the receiving (ie. 'rv') with the address

	if (rv) {die("bind()")};

	// Step 3-1. Defining IPv4 Port-Pair.
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






	// step 4: listen
	// previous steps are merely passing parameters
	// this step actually creates the socket, which happens at listen()
	rv = listen(fd, SOMAXCONN);	// SOMAXCONN is 4096, the size of queue, which does not matter as accept () is the bottle neck.
	if (rv) { die("listen()"); }

	// Step 5: accept connection
	while (true) {
		// accept
		/struct sockaddr_in client_addr = {};
		socklen_t addrlen = sizeof(client_addr);
		int connfd = accept(fd, (struct sockaddr *)&client_addr, &addrlen);
		
		if ( connfd < 0) {
			continue; 	// error 
		}
		
		do_something(connfd);
		close(connfd);
	}
}
static void do_something(int connfd) {
	char rbuf[64] = {};
	ssize_t n = read(connfd, rbuf, sizeof(rbuf) - 1);
	if (n<0) {
		msg("read() error");
		return;
	}
	printf("client says: %s\n",rbuf);

	char wbuf[] = "world";
	write(connfd, wbuf, strlen(wbuf));
}


