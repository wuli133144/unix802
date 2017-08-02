CC = gcc
CFLAGS = -O0 -g -Wall -Wextra -std=c89 -pedantic-errors

CPPC = g++
CPPFLAGS = -O0 -g -Wall -Wextra

all: test testcpp
 
.PHONY: test testcpp
test: main.c mio_buf.c
	$(CC) $(CFLAGS) -o $@ main.c mio_buf.c
	./$@

testcpp: main.c mio_buf.c
	$(CPPC) $(CPPFLAGS) -o $@ main.c mio_buf.c
	./$@

clean:
	rm -f test *.o


