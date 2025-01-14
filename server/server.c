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
uint8_t NEXT_UID = 1;

typedef struct {
    User *user;
    UserNode *next;
} UserNode;

UserNode *LAST_USERNODE = NULL;

Error register_user(User *userref) {
    UserNode *new_user = (UserNode *)malloc(sizeof(UserNode));
    if (new_user == NULL) {
        return MALLOCFAIL;
    }

    new_user->user = userref;
    new_user->next = NULL;

    if (LAST_USERNODE == NULL) {
        LAST_USERNODE = new_user;
    } else {
        LAST_USERNODE->next = new_user;
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

Error handle_question(char buffer, int sockfd);

int main(void) {
    // variables initialization
    int EXIT_STATUS = EXIT_SUCCESS;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char *question = "What is 2 + 2?";

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
            switch (handle_question(qu_buffer[0], new_socket)) {
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

Error handle_question(char qu, int sockfd) {
    unsigned char version = (qu & 0xe0) >> 5;
    if (version != VERSION) {
        printf("version: %u\n", version);
        puts("unsupported client.");
        return VERSION_MISMATCH;
    }

    unsigned char qu_no = (qu & 0x1c) >> 2;
    switch (qu_no) {
        case 1: {
            puts("register new client...");
            char *uname = (char *)malloc(256);
            User *new_user = (User *)malloc(sizeof(User));
            if (uname == NULL || new_user == NULL) {
                puts("failed to allocate new memory!");
            }

            if (create_user(uname, new_user, &NEXT_UID) != OK &&
                register_user(new_user) != OK) {
                puts("something went wrong");
                break;
            }

            puts("new client registered!");
            printf("latest uid %d\n", new_user->uid);

            unsigned char ans = VERSION << 5;
            ans = ans | new_user->uid;
            break;
        }
        case 2: {
            puts("checkup...");

            unsigned char ans = VERSION << 5;
            ans = ans | players_no;
            int _res = send(sockfd, &ans, sizeof(ans), 0);
            if (_res == -1) {
                return NETZ_FAIL;
            }

            printf("time send is %lu\n", game_start);
            switch (send_time(sockfd, game_start)) {
                case OK:
                    break;
                default:
                    return NETZ_FAIL;
            }
            break;
        }
        default: {
            puts("unsupported question");
            return UNKNOWN;
        }
    }

    return OK;
}
