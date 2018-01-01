#include "i8042.h"


.global _read_asm
.global _sc_asm

.bss
.lcomm _sc_asm, 8

.text

_read_asm:
		  xor %eax, %eax
          inb $STAT_REG
          testb $OUT_BUF_FULL, %al
          inb $OUT_BUF
					movb %al, _sc_asm

			ret

.end read_asm
