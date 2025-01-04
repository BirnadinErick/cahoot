#include <endian.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#endif

#include "tahoot.h"

#ifdef _WIN32
typedef SOCKET socket_t;
#else
typedef int socket_t;
#endif

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

Question* get_next_question(uint8_t user_id) {
    Question* quptr = (Question*)malloc(sizeof(Question));
    char** ansgrpptr = (char**)malloc(sizeof(char*) * 4);
    UserAnswer* _usransptr = (UserAnswer*)malloc(sizeof(UserAnswer));

    if (quptr == NULL || ansgrpptr == NULL || _usransptr == NULL) {
        return NULL;
    }

    // TODO: dev; swap with actual implementation later!

    quptr->qu_id = 69;
    quptr->qu_str = "Du brauchst mir nicht zu helfen.\0";

    *(ansgrpptr) = "musst\0;";
    *(ansgrpptr + 1) = "kannst\0;";
    *(ansgrpptr + 2) = "willst\0;";
    *(ansgrpptr + 3) = "darfst\0;";
    quptr->ans_grp = ansgrpptr;

    _usransptr->qu_id = 69;
    _usransptr->answer_idx = UNINITVAL;
    _usransptr->score = UNINITVAL;
    quptr->usransptr = _usransptr;

    // TODO: end of dev impl; replace later!
    return quptr;
}

Bool check_user_answer(UserAnswer* answer) {
    answer->score = 100;
    return TRUE;
}