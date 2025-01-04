#pragma once

#include <endian.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/socket.h>
#include <time.h>

/* Descriptive Error Type */
typedef enum { OK = 0, NETZ_FAIL, UNKNOWN , VERSION_MISMATCH} Error;

/* send given timestamp in a network agnostic way */
Error send_time(int socket_fd, time_t _time);

/* receive a timestamp */
Error receive_time(int socket_fd, time_t* timeptr);