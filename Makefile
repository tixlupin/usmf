SRCS=usmf.c
PROG=usmf

all:
	gcc -Wall -o $(PROG) $(SRCS) -lncurses

clean:
	rm -f $(PROG)
