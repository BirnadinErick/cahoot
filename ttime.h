#pragma once

#include <endian.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/socket.h>
#include <time.h>

#include "tahoot_error.h"

/* send given timestamp in a network agnostic way */
Error send_time(int socket_fd, time_t _time);

/* receive a timestamp */
Error receive_time(int socket_fd, time_t* timeptr);
