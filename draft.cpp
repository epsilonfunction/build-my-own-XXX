
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
//	
