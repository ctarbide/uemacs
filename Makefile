
uname_S := Linux

PROGRAM = em

SRC = ansi.c basic.c bind.c buffer.c debug.c display.c eval.c exec.c \
	file.c fileio.c ibmpc.c input.c isearch.c line.c lock.c main.c \
	pklock.c posix.c random.c region.c search.c spawn.c tcap.c \
	termio.c vmsvt.c vt52.c window.c word.c names.c globals.c version.c \
	usage.c wrapper.c utf8.c util.c alloc.c munix.c misc.c

OBJ = ansi.o basic.o bind.o buffer.o debug.o display.o eval.o exec.o \
	file.o fileio.o ibmpc.o input.o isearch.o line.o lock.o main.o \
	pklock.o posix.o random.o region.o search.o spawn.o tcap.o \
	termio.o vmsvt.o vt52.o window.o word.o names.o globals.o version.o \
	usage.o wrapper.o utf8.o util.o alloc.o munix.o misc.o

HDR = ebind.h edef.h efunc.h epath.h estruct.h evar.h util.h version.h

CC = gcc
WARNINGS = -Wall -Wstrict-prototypes
CFLAGS = -O2 $(WARNINGS) -g
# CFLAGS = -O0 $(WARNINGS) -ggdb3
#CC = c89 +O3			# HP
#CFLAGS =  -D_HPUX_SOURCE -DSYSV
#CFLAGS = -O4 -DSVR4		# Sun
#CFLAGS = -O -qchars=signed	# RS/6000
ifeq ($(uname_S),Linux)
 DEFINES = -DAUTOCONF -DPOSIX -DUSG -D_XOPEN_SOURCE=600 -D_GNU_SOURCE -D_DEFAULT_SOURCE
endif
ifeq ($(uname_S),FreeBSD)
 DEFINES = -DAUTOCONF -DPOSIX -DSYSV -D_FREEBSD_C_SOURCE -D_BSD_SOURCE -D_SVID_SOURCE -D_XOPEN_SOURCE=600
endif
ifeq ($(uname_S),Darwin)
 DEFINES = -DAUTOCONF -DPOSIX -DSYSV -D_DARWIN_C_SOURCE -D_BSD_SOURCE -D_SVID_SOURCE -D_XOPEN_SOURCE=600
endif
#DEFINES = -DAUTOCONF
#LIBS = -ltermcap			# BSD
LIBS = -lcurses			# SYSV
#LIBS = -ltermlib
#LIBS = -L/usr/lib/termcap -ltermcap
LFLAGS = -hbx
PREFIX = /usr
BINDIR = $(PREFIX)/bin
LIBDIR = $(PREFIX)/lib/uemacs

DEFINES += -DNEED_ICON_RELFILE
DEFINES += -DNEED_ICON_SALLOC

INSTALL = ./tools/install.sh

all: $(PROGRAM)

$(PROGRAM): $(OBJ)
	$(CC) $(LDFLAGS) $(DEFINES) -o $@ $(OBJ) $(LIBS)

clean:
	rm -f $(PROGRAM) core lintout makeout tags makefile.bak *.o

install: $(PROGRAM)
	$(INSTALL) -D -m 555 em '$(DESTDIR)$(BINDIR)/em'
	$(INSTALL) -D -m 444 emacs.hlp '$(DESTDIR)$(LIBDIR)/emacs.hlp'
	$(INSTALL) -D -m 444 emacs.rc '$(DESTDIR)$(LIBDIR)/.emacsrc'
	$(INSTALL) -D -m 444 em.rc '$(DESTDIR)$(LIBDIR)/em.rc'

tags:	$(SRC)
	@rm -f tags
	ctags $(SRC)

.c.o:
	$(CC) $(CFLAGS) $(DEFINES) -c $*.c

# DO NOT DELETE THIS LINE -- make depend uses it

ansi.o: ansi.c estruct.h edef.h
basic.o: basic.c estruct.h edef.h
bind.o: bind.c estruct.h edef.h epath.h
buffer.o: buffer.c estruct.h edef.h
display.o: display.c estruct.h edef.h utf8.h
eval.o: eval.c estruct.h edef.h evar.h
exec.o: exec.c estruct.h edef.h
file.o: file.c estruct.h edef.h
fileio.o: fileio.c estruct.h edef.h
ibmpc.o: ibmpc.c estruct.h edef.h
input.o: input.c estruct.h edef.h
isearch.o: isearch.c estruct.h edef.h
line.o: line.c estruct.h edef.h
lock.o: lock.c estruct.h edef.h
main.o: main.c estruct.h efunc.h edef.h ebind.h
pklock.o: pklock.c estruct.h
posix.o: posix.c estruct.h utf8.h
random.o: random.c estruct.h edef.h
region.o: region.c estruct.h edef.h
search.o: search.c estruct.h edef.h
spawn.o: spawn.c estruct.h edef.h
tcap.o: tcap.c estruct.h edef.h
termio.o: termio.c estruct.h edef.h
utf8.o: utf8.c utf8.h
vmsvt.o: vmsvt.c estruct.h edef.h
vt52.o: vt52.c estruct.h edef.h
window.o: window.c estruct.h edef.h
word.o: word.c estruct.h edef.h

# DEPENDENCIES MUST END AT END OF FILE
# IF YOU PUT STUFF HERE IT WILL GO AWAY
# see make depend above
