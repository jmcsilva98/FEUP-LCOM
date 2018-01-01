# Makefile for lab5

COMPILER_TYPE= gnu

CC= gcc

PROG= lab5
SRCS= lab5.c test5.c vbe.c video_gr.c read_xpm.c video_test.c timer.c keyboard.c sprite.c

CFLAGS= -Wall


DPADD+= ${LIBDRIVER} ${LIBSYS}
LDADD+= -llm -ldriver -lsys


LDFLAGS+= -L .

BINDIR?= /usr/sbin

MAN=

.include <bsd.prog.mk>
.include <bsd.gcc.mk>
