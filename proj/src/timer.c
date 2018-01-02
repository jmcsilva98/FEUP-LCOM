#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/driver.h>
#include "i8254.h"
#include "timer.h"
#include "graphics.h"
#include "gamestates.h"
#include "matrix.h"

int hook_id = 0;
unsigned int counter = 0;

void check_timer_events(Game * ColourPop){

  switch (getStateMachine()->currentState) {
    case MENU:
    drawMenu(ColourPop);

    break;

    case PLAY_MODE:
    drawGame(ColourPop);
    checkIfLost(ColourPop);


    if(getStateMachine()->throwingBubbleState == THROWING){

      if(ColourPop->t_counter % 3 == 0){
        throwingDirection(ColourPop, ColourPop->throwingBubble);
      }
    }

    if(ColourPop->t_counter % (60*20) == 0){
      if(getStateMachine()->throwingBubbleState != THROWING)
          addRow(ColourPop);
        ColourPop->score++;
    }

    if(getStateMachine()->throwingBubbleState == EXPLODING){
      if(ColourPop->t_counter % 10 == 0){
      explodeBubbles(ColourPop);
      }
    }

    if(getStateMachine()->throwingBubbleState == CHANGING){
      changeThrowingBubble(ColourPop);
      getStateMachine()->throwingBubbleState = STILL;
    }
    break;

    case ENTER_NAME_MENU:
    drawEnterNameMenu(ColourPop);
    break;

    case HIGHSCORES_MENU:
    drawHighscoresMenu(ColourPop);
    break;

    case GAME_OVER:
    drawGameOverMenu(ColourPop);
    break;

    case START_OVER:
    playAgain(ColourPop);
    break;

    case PAUSED:
    drawPausedMenu(ColourPop);
    break;

    case FINISHING_UP:
    drawGame(ColourPop);
    turnBubblesBlack(ColourPop);
    default:
    break;
  }
}

void timer_int_handler(Game * ColourPop) {
	ColourPop->t_counter++;
}

int timer_set_frequency(unsigned char timer, unsigned long freq) {

	//checks if the timer is valid
	if (timer < 0 || timer > 2) {
		printf("This timer doesn't exist!\n");
		return 1;
	}

	unsigned char st;
	unsigned char preservedBits;
	unsigned long msb, lsb, div;

	timer_get_conf(timer, &st);
	preservedBits = st << 4; //preserving the 4 least-significant bits
	preservedBits = preservedBits >> 4;


	unsigned long controlWord = (TIMER_SEL0 + (timer | TIMER_LSB_MSB | preservedBits));

	div = TIMER_FREQ / freq;


    msb = (unsigned char) (div >> 8);
   	lsb = (unsigned char) div;

	int writingControlWord = sys_outb(TIMER_CTRL, controlWord);

	if (writingControlWord != OK)
		return 1;

	int loadingTimer = sys_outb(TIMER_0 + timer, lsb);

	if (loadingTimer != OK)
		return 1;

	loadingTimer = sys_outb(TIMER_0 + timer, msb);

	if (loadingTimer != OK)
		return 1;

	return 0;
}

int timer_subscribe_int(void) {

	int h_tmp=hook_id;//using h_tmp is used to preserve hook_id
	int kernelCall = sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id);

	if (kernelCall != OK) {
		printf("Error in sys_irqsetpolicy!\n");
		return -1;
	}

	kernelCall = sys_irqenable(&hook_id);

	if (kernelCall != OK) {
		printf("Error in sys_irqenable!\n");
		return -1;
	}

	return BIT(h_tmp);
}

int timer_unsubscribe_int() {

	int kernelCall = sys_irqdisable(&hook_id);

	if (kernelCall != OK) {
		printf("Error in sys_irqdisable!\n");
		return 1;
	}

	kernelCall = sys_irqrmpolicy(&hook_id);

	if (kernelCall != OK) {
		printf("Error in sys_irqrmpolicy!\n");
		return 1;
	}

	return 0;
}


int timer_get_conf(unsigned char timer, unsigned char *st) {
	//Checks if the timer used is valid, if it isn't the function returns 1
	if (timer < 0 || timer > 2) {
		printf("This timer doesn't exist!\n");
		return 1;
	}

	unsigned long conf;
	unsigned long read_back_command = (TIMER_RB_CMD | TIMER_RB_COUNT_
			| TIMER_RB_SEL(timer));

	//Writes in the control register
	sys_outb(TIMER_CTRL, read_back_command);
	//Loads to the address of the timer
	sys_inb(TIMER_0 + timer, &conf);

	*st = (unsigned char) conf;

	return 0;
}
