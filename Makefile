PROG = tictac2

DESTDIR =/usr/games
LIBDIR  = $(DESTDIR)/lib
MANDIR  = /usr/man/man6

CC     ?= gcc
CFLAGS ?= -O
CFLAGS += $(shell ncurses5-config --cflags)
LIBS   += $(shell ncurses5-config --libs)

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
DEPS = tictac2.h

all: $(PROG)
.PHONY: all

$(PROG): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

%.o: %.c $(DEPS)

install: all
	install -c -o bin -g root -m 755 $(PROG) $(DESTDIR)
	install -c -o root -g root -m 444 $(PROG).6 $(MANDIR)
.PHONY: install

clean:
	$(RM) $(PROG) $(OBJS)
.PHONY: clean
