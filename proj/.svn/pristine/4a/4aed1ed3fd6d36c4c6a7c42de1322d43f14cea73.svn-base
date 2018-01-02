#include "i8042.h"


.global _read_asm


.text

_read_asm:
xor %eax, %eax

CICLE:			inb $STAT_REG
						testb $OUT_BUF_FULL, %al
						loopz CICLE
						inb $OUT_BUF

		ret
.end  read_asm
