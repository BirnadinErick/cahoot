dev:
	clang -o tahoot main.c -Werror -Wall -Wpedantic
	./tahoot

clean: 
	rm tahoot

.PHONY: dev clean