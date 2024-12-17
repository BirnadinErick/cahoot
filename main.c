#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 6969
#define BUFFER_SIZE 1024
#define TRUE 1
#define FALSE 0

// global vars to gracefully shutdown the server
int server_fd, new_socket;

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

        send(new_socket, question, strlen(question), 0);
        printf("Sent question: %s\n", question);

        int valread = read(new_socket, buffer, BUFFER_SIZE);
        printf("Received answer: %s\n", buffer);

        if (strcmp(buffer, "4") == 0) {
            char *response = "Correct! You got 10 points.";
            send(new_socket, response, strlen(response), 0);
        } else {
            char *response = "Incorrect answer.";
            send(new_socket, response, strlen(response), 0);
        }

        close(new_socket);
    }

exit:
    close(server_fd);
    exit(EXIT_STATUS);
}
