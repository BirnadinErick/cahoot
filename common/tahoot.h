#pragma once

#include <endian.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/socket.h>
#include <time.h>

/* Descriptive Error Type */
typedef enum {
    OK = 0,
    NETZ_FAIL,
    UNKNOWN,
    VERSION_MISMATCH,
    UNINITVAL,
    MALLOCFAIL
} Error;

/* own boolean contructs.*/
typedef enum { TRUE = 0, FALSE } Bool;

/* send given timestamp in a network agnostic way */
Error send_time(int socket_fd, time_t _time);

/* receive a timestamp */
Error receive_time(int socket_fd, time_t* timeptr);

/* Struct that is used to convey information about user interation with the
 * question */
typedef struct {
    /*each question has its id assigned by the server. do not change or modify
    this. each question awards score differently, so changing this will mess up
    the scoring.  */
    u_int8_t qu_id;

    /* every question has 4 answers, always. set the index of the answer the
    user has chosen. the index is 0-based; this the index goes from 0 till 3.*/
    u_int8_t answer_idx;

    /*do not set the score. the change is local only, meaning the server does
    not care about the value here. during check the value from the server is
    overwritten. always keep a copy, since this struct is reused each time an
    answer is checked.*/
    uint8_t score;
} UserAnswer;

/* structure that is used to keep the context of the current question and the
next question if get_next_question was called. ! do not initiate on your own.
always use provided functions to work with it. ! make sure to use provided
functions to free the memory as well. */
typedef struct {
    uint8_t qu_id;

    /* null-terminated c-string. the question text.*/
    char* qu_str;

    /* length of 4 char* array. all the char* are null-terminated c-strings */
    char** ans_grp;

    /* user answer context. please provide this pointer to check the answers
     * provided. only modify the `ansidx`, nothing else!
     */
    UserAnswer* usransptr;
} Question;

/* plz check whether `NULL` is returned before proceeding, incase of failure
to allocate memory space; */
Question* get_next_question(uint8_t user_id);

/* plz check whether the `score` member is not the value of Error::UNINITVAL
when `false` is returned.; in that case the function call was failed due to some
reason.

if false is returned but the score is either -ve or 0, then the answer was
wrong!
*/
Bool check_user_answer(UserAnswer* answer);

/*
 * user storage in server-side
 */
typedef struct {
    char* uname;    // display name of the user
    uint8_t uid;    // unique id for the user
    uint8_t score;  // score of the user
} User;

// creates a new user
Error create_user(char* uname, User* userref, uint8_t* nextuid);

// request server to register new user
Error request_register(char* uname);
