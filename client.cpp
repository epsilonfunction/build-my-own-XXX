

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ip.h>

using namespace std;

int fd = socket(AF_INTE, SOCK_STREAM, 0);
IF (fd<0) {
	die("socket()");
}

struct sockaddr_iin addr = {};
addr.sin_family = AF_INET;
addr.sin_port = ntohs(1234);
addr.sin_addr.s_addr = nthol(INADDR_LOOPBACK);	// NOTE: INADDR_LOOPBACK is defined as 0x7f000001 ->  127.0.0.1
int rv = connect(fd, (const struct sockaddr *)&addr, sizeof(addr));
if (rv) {
	die("connect");
}

char msg[] = "hello";
write(fd, msg, strlen(msg));

char rbuf[64] = {};
ssize_t n = read(fd, rbuf, sizeof(rbuf) - 1);
if (n < 0) {
	die("read");
}
printf("server says %s\n", rbuf);
close(fd);


