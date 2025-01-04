CC = clang
CFLAGS = -Werror -Wall -Wpedantic -Wno-unused-label -Wno-unused-variable
COMMON_SRC = ttime.c
SRV_SRC = server.c $(COMMON_SRC)
CLT_SRC = client.c $(COMMON_SRC)
SRV_BIN = tahoot-server
CLT_BIN = tahoot-client

# Rules
all: $(SRV_BIN) $(CLT_BIN)

$(SRV_BIN): $(SRV_SRC)
	$(CC) -o $@ $^ $(CFLAGS)

$(CLT_BIN): $(CLT_SRC)
	$(CC) -o $@ $^ $(CFLAGS)

dev: $(SRV_BIN)
	./$(SRV_BIN)

devc: $(CLT_BIN)
	./$(CLT_BIN)

clean:
	rm -f $(SRV_BIN) $(CLT_BIN)

.PHONY: all dev devc clean

