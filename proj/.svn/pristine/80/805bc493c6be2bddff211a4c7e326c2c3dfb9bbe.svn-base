# Makefile for proj

COMPILER_TYPE= gnu

CC= gcc

PROG= proj
SRCS= main.c
SRCS+=  vbe.c bitmap.c game.c graphics.c bubbles.c read_asm.S keyboard.c timer.c mouse.c video_gr.c gamestates.c rtc.c matrix.c highscores.c

CFLAGS= -Wall


DPADD+= ${LIBDRIVER} ${LIBSYS}
LDADD+= -llm -ldriver -lsys


LDFLAGS+= -L .

BINDIR?= /usr/sbin

MAN=

.include <bsd.prog.mk>
.include <bsd.gcc.mk>
