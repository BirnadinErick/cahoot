#include <arpa/inet.h>
#include <assert.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#include "tahoot.h"

#define PORT 6969
#define BUFFER_SIZE 1024
#define TRUE 1
#define FALSE 0
#define VERSION 1

// global vars to gracefully shutdown the server
int server_fd, new_socket;
unsigned char players_no = 0;
time_t game_start;
uint8_t NEXT_UID = 0;
User *users;

PacketHeader parse_packet_header(uint8_t byte) {
    PacketHeader header;
    header.version = (byte & 0xE0) >> 5;
    header.question = (byte & 0x1C) >> 2;
    header.padding = byte & 0x03;
    return header;
}

Error send_response(int sockfd, uint8_t version, uint8_t answer) {
    uint8_t response = (version << 5) | (answer << 2);
    int res = send(sockfd, &response, sizeof(response), 0);
    if (res == -1) {
        perror("send failed");
        return NETZ_FAIL;
    }
    return OK;
}

void handle_shutdown(int sig) {
    puts("shutting down...");

    // clean up
    if (new_socket >= 0) {
        close(new_socket);
    }

    if (server_fd >= 0) {
        close(server_fd);
    }

    puts("exit.");
    exit(EXIT_SUCCESS);
}

Error handle_question(PacketHeader header, int sockfd);

int main(void) {
    // variables initialization
    int EXIT_STATUS = EXIT_SUCCESS;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char *question = "What is 2 + 2?";
    users = (User *)malloc(sizeof(User) * 32);

    /*
     * since the deployment is in Linux, these are the only
     * bare minimum signals I hafta worry about;
     */
    signal(SIGINT, handle_shutdown);
    signal(SIGTERM, handle_shutdown);

    // create a socket fd
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("failed to create a new socket.");
        EXIT_STATUS = EXIT_FAILURE;
        goto exit;
    }

    // configure the socket fd with porper attrs
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // bind the socket fd with PORT
    int _bind_res =
        bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    if (_bind_res < 0) {
        perror("failed to bind the socket fd.");
        EXIT_STATUS = EXIT_FAILURE;
        goto exit;
    }

    int _listent_res = listen(server_fd, 3);
    if (_listent_res < 0) {
        perror(
            "failed to create a listener, what a shame! shame! (bell clings)");
        EXIT_STATUS = EXIT_FAILURE;
        goto exit;
    }

    printf("listening for new connections at %d.\n", PORT);

    game_start = time(NULL);
    while (TRUE) {
        puts("w8ing for new connection...");

        // accept new bound connection
        new_socket = accept(server_fd, (struct sockaddr *)&address,
                            (socklen_t *)&addrlen);
        if (new_socket < 0) {
            perror("failed to accept a new connection!");
            EXIT_STATUS = EXIT_FAILURE;
            goto exit;
        }
        puts("connection established with a client.");

        /* question answer protocol */
        char qu_buffer[1];
        unsigned int BYTES_TO_READ = 1;

        int bytes_read = recv(new_socket, qu_buffer, BYTES_TO_READ, 0);
        if (bytes_read < 0) {
            perror("recv failed");
        } else if (bytes_read == 0) {
            puts("client disconnected.");
        } else {
            // check question and payload; answer.
            puts("handling the question");

            players_no = 27;  // dev; remove later.

            // few assertions to stay safe
            assert(players_no <= 32);

            // Parse the packet header
            PacketHeader header = parse_packet_header(qu_buffer[0]);

            switch (handle_question(header, new_socket)) {
                case OK:
                    continue;
                    break;  // failsafe incase continue did not work!
                default: {
                    perror("something went wrong");
                    EXIT_STATUS = EXIT_FAILURE;
                    goto exit;
                }
            }
        }
        close(new_socket);
    }

exit:
    close(server_fd);
    exit(EXIT_STATUS);
}

Error handle_question(PacketHeader header, int sockfd) {
    unsigned char version = header.version;
    if (version != VERSION) {
        printf("version: %u\n", version);
        puts("unsupported client.");
        return VERSION_MISMATCH;
    }

    unsigned char qu_no = header.question;
    switch (qu_no) {
        case 1: {
            // recv uname
            assert(/* only 32 players are allowed */ NEXT_UID < 32);

            char buf[1];
            int bytes_read = recv(sockfd, buf, 1, 0);
            size_t uname_len = (size_t)buf[0];

            assert(/*only 255 chars are allowed in the user display name*/
                   uname_len < 256);
            printf("%d length of char to be expected\n", (int)uname_len);

            char *uname = (char *)malloc(uname_len);
            User *new_user = (User *)malloc(sizeof(User));
            if (uname == NULL || new_user == NULL) {
                puts("failed to allocate new memory!");
                return MALLOCFAIL;
            }

            bytes_read = recv(sockfd, uname, uname_len, 0);
            *(uname + uname_len) = '\0';

            puts("register new client...");

            new_user->score = -1;
            new_user->uname = uname;
            new_user->uid = NEXT_UID;
            *(users + NEXT_UID) = *new_user;
            NEXT_UID++;

            puts("new client registered!");
            printf("latest uid %d\n", new_user->uid);

            puts("current users table...");
            print_users_table(users, 1);

            return send_response(sockfd, VERSION, new_user->uid);
        }
        case 2: {
            puts("checkup...");
            return send_response(sockfd, VERSION, players_no);
        }
        default: {
            puts("unsupported question");
            return UNKNOWN;
        }
    }

    return OK;
}
