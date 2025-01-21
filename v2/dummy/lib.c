// math.c
#include <stdio.h>
#include <string.h>

typedef struct {
    char *uname;
    int score;
} User;

void print_users(User *users, int count) {
    printf("Users:\n");
    for (int i = 0; i < count; i++) {
        printf("Username: %s, Score: %d\n", users[i].uname, users[i].score);
    }
}

void read_and_print_users_from_csv(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    char line[512];
    int user_count = 0;

    // First, count the number of lines (excluding the header)
    fgets(line, sizeof(line), file);  // Skip the header
    while (fgets(line, sizeof(line), file)) {
        user_count++;
    }

    // Rewind file to parse data
    rewind(file);
    fgets(line, sizeof(line), file);  // Skip the header

    // Allocate memory for the users array
    User *users = (User *)malloc(sizeof(User) * user_count);
    if (!users) {
        perror("Failed to allocate memory");
        fclose(file);
        return;
    }

    int index = 0;
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        if (token) {
            strncpy(users[index].uname, token, sizeof(users[index].uname) - 1);
            users[index].uname[sizeof(users[index].uname) - 1] = '\0';
        }
        token = strtok(NULL, ",");
        if (token) {
            users[index].score = atoi(token);
        }
        index++;
    }
    fclose(file);

    // Print users
    printf("Users from CSV:\n");
    for (int i = 0; i < user_count; i++) {
        printf("Username: %s, Score: %d\n", users[i].uname, users[i].score);
    }

    free(users);
}