
# 1. Introduction

## 1.1 The OSI layer


## 1.2 Socket Primitives
socket() method allocates and returns a socket fd (handle)
handle must be closed to free up system resource

Listening is a call indicating 'readiness to accept TCP connection from a given PORT'
OS then returns a handle referencing that port.

from socket, app can retrieve/accept incoming TCP, represented by a socket handle.

1. listening socket
2. connection socket

    `pseudocode - listening socket
    fd = socket()
    bind(fd, address)
    listen(fd)
    while True:
        conn_fd = accept(fd)
        do_function(conn_fd)
        close(conn_fd)

a connectiion socket is as follows:

    `pseudocode - connecting socket
    fd = socket()
    connect(fd, address)
    do_function(fd)
    close(fd)

socket() is a typeless socket, type is determined after listen/connect call
bind() merely sets a parameter
setsockopt() API can set other parameters

:

