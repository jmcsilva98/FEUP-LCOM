#include "mouse.h"
#include "keyboard.h"
#include "video_gr.h"
#include "graphics.h"
#include "gamestates.h"

int hook_id_mouse=2;
int packet[3];

Mouse *mouse = NULL;

Mouse * newMouse(){
	Mouse * mouse = (Mouse*) malloc (sizeof(Mouse));
	mouse->x = 512;
	mouse->y = 384;

	mouse->left_button_pressed = 0;
	mouse->right_button_pressed = 0;
	mouse->left_button_released = 0;
	mouse->right_button_released = 0;

	mouse->deltax_pos = 0;
	mouse->deltax_neg = 0;

	return mouse;
}


void drawMouse(Game * ColourPop){

	drawBitmap(ColourPop->cursor, getMouse()->x, getMouse()->y, ALIGN_LEFT);
}


Mouse * getMouse(){

if(!mouse){
	enable_sMode();
	enable_packets();
	mouse = newMouse();
}

	return mouse;
}

void deleteMouse(){
	free(getMouse());
}


int subscribe_mouse(int *hook_id_mouse) {
	int h_tmp = *hook_id_mouse;

	int kernelCall = sys_irqsetpolicy(MOUSE_IRQ,IRQ_REENABLE | IRQ_EXCLUSIVE, hook_id_mouse);

	if (kernelCall != OK) {
		printf("Error in sys_irqsetpolicy()\n");
		return -1;
	}

	kernelCall = sys_irqenable(hook_id_mouse);

	if (kernelCall != OK) {
		printf("Error in sys_irqenable()\n");
		return -1;
	}
	return BIT(h_tmp);

}


int unsubscribe_mouse(int *hook_id_mouse) {

	int kernelCall = sys_irqdisable(hook_id_mouse);

	if (kernelCall != OK) {
		printf("Error in sys_irqdisable()\n");
		return 1;
	}

	kernelCall = sys_irqrmpolicy(hook_id_mouse);

	if (kernelCall != OK) {
		printf("Error in sys_irqmpolicy()\n");
		return 1;
	}
	return 0;

}



unsigned long mouse_handler(int ass) {
	unsigned long stat, data;

	if (ass == 1){
		 data = read_asm();
		 return data;
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

			return data;  //passes data read to global variable

			if ((stat & (PAR_ERR | TO_ERR)) == 0)
				return 0;
			else
				return -1;
		}


		tickdelay(micros_to_ticks(DELAY_US));

	}

	printf("Error in reading data from  KBC\n");
	return -1;

}






int write_mouse(unsigned long cmd){

if (send_cmd_kbc(WRITE_BYTE_TO_MOUSE,STAT_REG) == -1)
{
    printf("Error in sending command\n");
    return -1;
}

if(send_cmd_kbc(cmd,IN_BUF) == -1)
{
    printf("Error in sending command\n");
    return -1;
}
return 0;
}




int disable_mouse(){

unsigned long data;

if(write_mouse(DISABLE_STREAM_MODE) == -1)
{
  printf("Error in in disabling the stream mode\n");
  return -1;
}

  if (sys_inb(OUT_BUF, &data) != OK) {
    printf("Error in sys_inb\n");
    return -1;
  }

	if( data == ACK){
		return 0;
	}else return disable_mouse();
}



int enable_sMode(){
  unsigned long data;

  if(write_mouse(SET_STREAM_MODE) == -1)
  {
    printf("Error in setting stream mode\n");
    return -1;
  }

  if (sys_inb(OUT_BUF, &data) != OK) {
    printf("Error in sys_inb\n");
    return -1;
  }

	if( data == ACK){
		return 0;
	}else return enable_sMode();

}



int enable_packets(){

unsigned long data;

  if(write_mouse(ENABLE_SENDING_DATA) == -1)
{
  printf("Error in sending data packets\n");
  return -1;
}
if (sys_inb(OUT_BUF, &data) != OK) {
  printf("Error in sys_inb\n");
  return -1;
}

if( data == ACK){
	return 0;
}else enable_packets();



enable_sMode();
return 0;
}



void mouse_h(Game * ColourPop){
	unsigned long data;

	data = mouse_handler(1); //Choose 1 for assembly or 0 for c


	if (data == -1) {
		printf("Error in reading data\n");
		return ;
	}


	if (ColourPop->m_counter == 0){
			if((data & BIT(3)) == BIT(3)){
				packet[0] = data;
        ColourPop->m_counter++;
      }
	}

	else if(ColourPop->m_counter == 1){

		packet[1] = data;
		ColourPop->m_counter++;
	}

	else{

		packet[2] = data;
    ColourPop->m_counter = 0;
		updateMouse(ColourPop);
}}


void updateMouse(Game * ColourPop){

  //temp variables important to not change the packets value
  unsigned long packet2, packet3;
  packet2 = packet[1];
  packet3 = packet[2];

	if(mouse->deltax_pos >= 7) mouse->deltax_pos = 0;
	if(mouse->deltax_neg >= 7) mouse->deltax_neg = 0;

	//read x
	if((packet[0] & BIT(4)) != 0)
	{
		packet2 ^= MOUSE_RESET; //0xFF
		packet2++;
		mouse->x -= packet2;
		mouse->deltax_pos++;
	}
	else{
	mouse->x += packet2;
	mouse->deltax_neg++;
	}

	//read y
	if((packet[0] & BIT(5))!=0)
	{
		packet3 ^= MOUSE_RESET; //0xFF
		packet3++;
		mouse->y += packet3;
	}
	else
	mouse->y -= packet3;

	//checks if the cursor leaves the screen
  if(mouse->x < 0){
    mouse->x = 0;
  }
  else if(mouse->x >= H_RES)
  mouse->x = H_RES - 1;

  if(mouse->y < 0){
    mouse->y = 0;
  }
  else if(mouse->y >= V_RES)
  mouse->y = V_RES - 2;

	//checks the buttons state

	if((packet[0] & BIT(0)) != 0)
	{
  	mouse->left_button_pressed = 1;
  	mouse->left_button_released = 0;
	}
	else if(mouse->left_button_pressed){
  	mouse->left_button_pressed = 0;
  	mouse->left_button_released = 1;
	}
	else{
  	mouse->left_button_pressed = 0;
  	mouse->left_button_released = 0;
	}

	if((packet[0] & BIT(1)) != 0)
  	{
    	mouse->right_button_pressed = 1;
    	mouse->right_button_released = 0;
  	}
  	else if(mouse->right_button_pressed){
    	mouse->right_button_pressed = 0;
    	mouse->right_button_released = 1;
  	}
  	else{
    	mouse->right_button_pressed = 0;
    	mouse->right_button_released = 0;
  	}
}


int check_mouse_click(unsigned int xi, unsigned int xf,unsigned int yi,unsigned int yf){
	if(getMouse()->x <= xf && getMouse()->x >= xi && getMouse()->y <= yf && getMouse()->y >= yi && getMouse()->left_button_pressed==1)
		return 1;
	else return 0;
}


void check_mouse_events(Game * ColourPop){

  switch (getStateMachine()->currentState){
    case MENU:
    if(check_mouse_click(144,360,448,548)){
  		getStateMachine()->event = PLAY_BUTTON;
			getMouse()->left_button_pressed=0;
		}
		if(check_mouse_click(414,628,512,610)){
  		getStateMachine()->event = HIGHSCORES_BUTTON;
			getMouse()->left_button_pressed=0;
		}
  	if(check_mouse_click(680,896,448,548))
  		getStateMachine()->event = EXIT_BUTTON;
    break;

		case PLAY_MODE:
			if(mouse->left_button_pressed == 1){
				getStateMachine()->throwingBubbleEvent = THROW;
			}

			//if mouse moves and a bubbles isn't being thrown, move spear accordingly
			if(mouse->deltax_neg == 7 && getStateMachine()->throwingBubbleState!=THROWING && getStateMachine()->throwingBubbleState!=THROWING_RIGHT && getStateMachine()->throwingBubbleState!=THROWING_LEFT){
				getStateMachine()->event = MOVE_SPEAR_RIGHT;
				updateSpear(ColourPop);}

			if(mouse->deltax_pos == 7 && getStateMachine()->throwingBubbleState!=THROWING && getStateMachine()->throwingBubbleState!=THROWING_RIGHT && getStateMachine()->throwingBubbleState!=THROWING_LEFT){
				getStateMachine()->event = MOVE_SPEAR_LEFT;
				updateSpear(ColourPop);
			}

		case GAME_OVER:
			if(check_mouse_click(136,335,507,607)){
				getStateMachine()->event = PLAY_BUTTON;
				getMouse()->left_button_pressed=0;
			}
			if(check_mouse_click(671,890,507,607))
				getStateMachine()->event = EXIT_BUTTON;
			if(check_mouse_click(404,623,570,670)){
				playAgain(ColourPop);
				getStateMachine()->currentState = MENU;
				getMouse()->left_button_pressed=0;
			}
			break;
		default:
		break;
  }
}
