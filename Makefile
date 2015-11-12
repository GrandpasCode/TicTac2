# make file for tictac2.  edit to needs.

PROG= tictac2

DESTDIR=/usr/games
LIBDIR= $(DESTDIR)/lib
MANDIR= /usr/man/man6
CC=     gcc
CFLAGS= -O -I/usr/include/ncurses

SRCS=	screen.c main.c moves.c ai.c 
	
OBJS=	screen.o main.o moves.o ai.c

LIBS=	-lncurses

all:	$(PROG)

$(PROG):	$(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(PROG)

$(OBJS):        tictac2.h	
	$(CC) $(CFLAGS) -c $*.c -o $@

install:	all
	install -c -o bin -g root -m 755 $(PROG) $(DESTDIR)
	install -c -o root -g root -m 444 $(PROG).6 $(MANDIR)

clean:
	rm -f $(PROG) core *.o
