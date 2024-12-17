dev:
	clang -o tahoot main.c -Werror -Wall -Wpedantic -Wno-unused-label -Wno-unused-variable
	./tahoot

clean: 
	rm tahoot

.PHONY: dev clean