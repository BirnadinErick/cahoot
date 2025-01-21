#include <stdio.h>
#include <stdlib.h>

#include "eg.pb-c.h"

int main() {
    // Read the serialized data from file
    FILE *file = fopen("message.bin", "rb");
    fseek(file, 0, SEEK_END);
    size_t len = ftell(file);
    fseek(file, 0, SEEK_SET);

    void *buf = malloc(len);
    fread(buf, len, 1, file);
    fclose(file);

    // Deserialize the message
    Example *msg = example__unpack(NULL, len, buf);
    if (msg == NULL) {
        fprintf(stderr, "Error unpacking message\n");
        return 1;
    }

    printf("Received: ID=%d, Name=%s, Value=%f\n", msg->id, msg->name,
           msg->value);

    example__free_unpacked(msg, NULL);
    free(buf);

    return 0;
}
