#include "keyboard.h"

unsigned int counter_inb;
unsigned long read_asm();

int subscribe_kb(int *hook_id_kbd) {
	int h_tmp = *hook_id_kbd;
	int kernelCall = sys_irqsetpolicy(KEYBOARD_IRQ,IRQ_REENABLE | IRQ_EXCLUSIVE, hook_id_kbd);

	if (kernelCall != OK) {
		printf("Error in sys_irqsetpolicy()\n");
		return -1;
	}

	kernelCall = sys_irqenable(hook_id_kbd);

	if (kernelCall != OK) {
		printf("Error in sys_irqenable()\n");
		return -1;
	}
	return BIT(h_tmp);

}



int unsubscribe_kb(int *hook_id_kbd) {

	int kernelCall = sys_irqdisable(hook_id_kbd);

	if (kernelCall != OK) {
		printf("Error in sys_irqdisable()\n");
		return 1;
	}

	kernelCall = sys_irqrmpolicy(hook_id_kbd);

	if (kernelCall != OK) {
		printf("Error in sys_irqmpolicy()\n");
		return 1;
	}
	return 0;

}


int kbc_handler_c() {
	unsigned long stat, data;


	while (1) {

		if (sys_inb(STAT_REG, &stat) != OK) {
			printf("Error in sys_inb\n");
			return 1;
		}

#ifdef LAB3
		counter_inb++;
#endif

		if (stat & OBF) {

			if (sys_inb(OUT_BUF, &data) != OK) {
				printf("Error in sys_inb\n");
				return -1;
			}

			scancode = data;  //passes data read to global variable

#ifdef LAB3
		counter_inb++;
#endif

			if ((stat & (PAR_ERR | TO_ERR)) == 0)
				return 0;
			else
				return -1;
		}


		tickdelay(micros_to_ticks(DELAY_US)); /* function needed to give the keyboard or kbc time to respond*/

	}
	/*  if the loop ends and no value is returned, there's an error */
	printf("Error in reading data from  KBC\n");
	return -1;

}



int send_cmd_kbc(unsigned long cmd, unsigned long reg) {
	unsigned long stat;


	while (1) {


		if (sys_inb(STAT_REG, &stat) != OK) {
			printf("Error in sys_inb\n");
			return 1; /* sees if IN_BUF is empty*/
		}

#ifdef 	LAB3
		counter_inb++;
#endif

		if ((stat & IBF) == 0) {

			if (sys_outb(reg, cmd) != OK) {
				printf("Error in sys_outb\n");
				return -1;
			} else
				return 0;
		}

		tickdelay(micros_to_ticks(DELAY_US)); /* function needed to give the keyboard or kbc time to respond*/

	}
	/*  if the loop ends and no value is returned, there's an error */
	printf("Error sending data to KBC\n");
	return -1;

}




void kbc_handler_asm() {
		 read_asm();
		 scancode=sc_asm;
}



void printScancodes() {
	unsigned long sc_temp = scancode;
	if (sc_temp == TWO_BYTE_SCANCODES) {
		if (sc_temp & BIT(7)) /*BIT(7) refers to BREAKCODE*/
			printf("BREAKCODE: 0xE0%02X\n\n", sc_temp);
		else
			printf("MAKECODE: 0xE0%02X\n", sc_temp);
	}

	else {
		if (sc_temp & BIT(7))
			printf("BREAKCODE: 0x%x\n\n", sc_temp);
		else
			printf("MAKECODE: 0x%x\n", sc_temp);
	}
}
