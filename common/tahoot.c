#include <endian.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/socket.h>
#include <time.h>

#include "tahoot.h"

Error send_time(int socket_fd, time_t _time) {
    uint64_t time_to_send = (uint64_t)_time;
    time_to_send = htobe64(time_to_send);

    int _res = send(socket_fd, &time_to_send, sizeof(time_to_send), 0);
    if (_res == -1) {
        puts("did not send time!");
        return NETZ_FAIL;
    }

    puts("sent time!");
    return OK;
}

Error receive_time(int socket_fd, time_t* timeptr) {
    uint64_t received_time;

    ssize_t bytes_received =
        recv(socket_fd, &received_time, sizeof(received_time), 0);
    if (bytes_received != sizeof(received_time)) {
        return NETZ_FAIL;
    }

    received_time = be64toh(received_time);
    *timeptr = (time_t)received_time;

    return OK;
}
