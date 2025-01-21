#include <stdio.h>
#include <string.h>

#define HTTP_IMPLEMENTATION
#include "http.h"

typedef enum {
    OK = 0,
    NETZFAIL,
    MEMFAIL,
    UNKNOWN,
} Error;

Error get_score(int qu_id, int ans_idx, int* score) {
    int prev_size = -1;
    char url[256];

    // construct the url
    snprintf(url, sizeof(url),
             "http://localhost:8080/score?qu_id=%d&ans_idx=%d", qu_id, ans_idx);

    http_t* request = http_get(url, NULL);
    if (!request) {
        printf("Invalid request.\n");
        return UNKNOWN;
    }

    http_status_t status = HTTP_STATUS_PENDING;
    while (status == HTTP_STATUS_PENDING) {
        status = http_process(request);
        if (prev_size != (int)request->response_size) {
            prev_size = (int)request->response_size;
        }
    }

    if (status == HTTP_STATUS_FAILED) {
        return NETZFAIL;
    }

    *score = atoi(request->response_data);

    http_release(request);
    return OK;
}

Error post_username(const char* username, int* res) {
    int prev_size = -1;
    char url[256];

    snprintf(url, sizeof(url), "http://localhost:8080/uname");
    const char* post_data = username;

    http_t* request = http_post(url, post_data, strlen(post_data), NULL);
    if (!request) {
        printf("Invalid request.\n");
        return UNKNOWN;
    }

    http_status_t status = HTTP_STATUS_PENDING;
    while (status == HTTP_STATUS_PENDING) {
        status = http_process(request);
        if (prev_size != (int)request->response_size) {
            prev_size = (int)request->response_size;
        }
    }

    if (status == HTTP_STATUS_FAILED) {
        http_release(request);
        return NETZFAIL;
    }

    const char* _res = (const char*)request->response_data;
    *res = atoi(_res);

    http_release(request);
    return OK;
}

int main(void) {
    int scoreref = -1;

    switch (get_score(9, 4, &scoreref)) {
        case OK:
            printf("score: %d\n", scoreref);
            break;

        default:
            puts("something went wrong");
            break;
    }

    int resref = -1;
    const char* username = "birnadin erick";
    switch (post_username(username, &resref)) {
        case OK:
            printf("res: %d\n", resref);
            break;

        default:
            puts("something went wrong");
            break;
    }

    return 0;
}