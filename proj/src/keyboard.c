#include "keyboard.h"
#include "graphics.h"
#include "gamestates.h"

int hook_id_kb=1;
unsigned long scancode;

unsigned int counter_inb;


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


int kbc_handler(Game *ColourPop, int ass) {
		unsigned long stat, data;

	if (ass == 1){
		 data = read_asm();
		 ColourPop->scancode = data;
		 return 0;
	 }


			while (1) {

				if (sys_inb(STAT_REG, &stat) != OK) {
					printf("Error in sys_inb\n");
				return 1;
			}


			if (stat & OBF) {

				if (sys_inb(OUT_BUF, &data) != OK) {
					printf("Error in sys_inb\n");
					return -1;
				}

				ColourPop->scancode = data;  //passes data read to global variable


				if ((stat & (PAR_ERR | TO_ERR)) == 0)
				return 0;
				else
				return -1;
		} else return  0;


		tickdelay(micros_to_ticks(DELAY_US));

	}
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


int readOutBuffer(){
unsigned long data;

	if (sys_inb(OUT_BUF, &data) != OK) {
		printf("Error in sys_inb\n");
		return -1;
	}
	else return 0;
}



void check_keyboard_events(Game * ColourPop){

	switch (getStateMachine()->currentState){
		case PLAY_MODE:

		if(ColourPop->scancode == ESC_KEY){
			getStateMachine()->event = ESCAPE;
		}

		if(ColourPop->scancode == SPACE_KEY){
			getStateMachine()->throwingBubbleEvent = THROW;
		}

		if(ColourPop->scancode == D_KEY_MAKECODE){
			getStateMachine()->event = MOVE_SPEAR_RIGHT;
			updateSpear(ColourPop);
		}

		if(ColourPop->scancode == A_KEY_MAKECODE){
			getStateMachine()->event = MOVE_SPEAR_LEFT;
			updateSpear(ColourPop);
		}

		if(ColourPop->scancode == P_KEY){
			getStateMachine()->currentState = PAUSED;
		}
		break;

		case ENTER_NAME_MENU:
		enterName(ColourPop);
		if(ColourPop->scancode == ENTER_KEY){
			getStateMachine()->event = PRESSED_KEY;
		}
		break;

		case PAUSED:
		if(ColourPop->scancode == R_KEY){
			getStateMachine()->currentState = PLAY_MODE;
		}
		break;

		case HIGHSCORES_MENU:
		if(ColourPop->scancode == ESC_KEY){
			getStateMachine()->event = ESCAPE;
		}
		break;

		default:
		break;
  }
}
