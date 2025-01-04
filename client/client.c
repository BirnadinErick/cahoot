#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <arpa/inet.h>
#include <unistd.h>
#endif

#define PORT 6969
#define BUFFER_SIZE 1024

int main(void) {
    int sock = 0;
    char buffer[BUFFER_SIZE] = {0};
    char answer[BUFFER_SIZE];
    int EXIT_STATUS = EXIT_SUCCESS;

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

/* this is necessary in window OS as it uses different
 * socket implementation
 */
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed.\n");
        return 1;
    }
#endif

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket creation error.\n");
        EXIT_STATUS = EXIT_FAILURE;
        goto exit;
    }

    char ip_addr[] = "127.0.0.1";
    int _inet_parse_res = inet_pton(AF_INET, ip_addr, &serv_addr.sin_addr);
    if (_inet_parse_res <= 0) {
        perror("failed to parse given IP address\n");
        EXIT_STATUS = EXIT_FAILURE;
        goto exit;
    }

    int _conn_res =
        connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (_conn_res < 0) {
        perror("failed to connect to the given host at port 6969!\n");
        EXIT_STATUS = EXIT_FAILURE;
        goto exit;
    }

exit:
    exit(EXIT_STATUS);
}
