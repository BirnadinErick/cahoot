#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "eg.pb-c.h"

int main() {
    // Initialize Protobuf message
    Example msg = EXAMPLE__INIT;
    msg.id = 42;
    msg.name = "PRotobuf Example";
    msg.value = 123.45;

    // Serialize the message
    size_t len = example__get_packed_size(&msg);
    void *buf = malloc(len);
    example__pack(&msg, buf);

    // Save serialized data to a file
    FILE *file = fopen("message.bin", "wb");
    fwrite(buf, len, 1, file);
    fclose(file);
    free(buf);

    printf("Message serialized to message.bin\n");
    return 0;
}
