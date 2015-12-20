PROG = tictac2

DESTDIR =/usr/games
LIBDIR  = $(DESTDIR)/lib
MANDIR  = /usr/man/man6

CC     ?= gcc
CFLAGS ?= -g -O2
CFLAGS += -std=c99 -Wall -Wextra
CFLAGS += $(shell ncurses5-config --cflags)
LDLIBS += $(shell ncurses5-config --libs)

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
DEPS = .depends

all: $(DEPS) $(PROG)
.PHONY: all

$(PROG): $(OBJS)

install: all
	install -c -o bin -g root -m 755 $(PROG) $(DESTDIR)
	install -c -o root -g root -m 444 $(PROG).6 $(MANDIR)
.PHONY: install

uninstall:
	$(RM) $(DESTDIR)/$(PROG)
	$(RM) $(MANDIR)/$(PROG).6
.PHONY: uninstall

clean:
	$(RM) $(PROG) $(OBJS)
.PHONY: clean

depend:
	$(RM) $(DEPS)
	make $(DEPS)
.PHONY: depend

$(DEPS):
	touch $(DEPS)
	makedepend -Y -f $(DEPS) -- $(CFLAGS) $(CPPFLAGS) -- $(SRCS) >&/dev/null

sinclude $(DEPS)
