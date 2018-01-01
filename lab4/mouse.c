#include "mouse.h"
#include "keyboard.h"

int hook_id_mouse=2;
int packet[3];



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



unsigned long mouse_handler() {
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

			return data;  //passes data read to global variable

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

int disable_sMode(){

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
	}else return disable_sMode();
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

void print_packets(){

printf("B1=0x%02X ", packet[0]);
printf("B2=0x%02X ", packet[1]);
printf("B3=0x%02X ", packet[2]);

if((packet[0] & BIT(0)) != 0)
  printf("LB=1 ");
else
  printf("LB=0 ");

if((packet[0] & BIT(2)) != 0)
  printf("MB=1 ");
else
  printf("MB=0 ");

if((packet[0] & BIT(1)) != 0)
	printf("RB=1 ");
else
	printf("RB=0 ");

if((packet[0] & BIT(6)) != 0)
  printf("XOV=1 ");
else
  printf("XOV=0 ");

if((packet[0] & BIT(7)) != 0)
  printf("YOV=1 ");
else
  printf("YOV=0 ");

if((packet[1] & BIT(4)) != 0)
{
  packet[1] ^= MOUSE_RESET; //0xFF
  packet[1]++;
  printf("X=-%u ", packet[1]);
}
else
printf("X=%u ", packet[1]);

if((packet[2] & BIT(5))!=0)
{
  packet[2] ^= MOUSE_RESET; //0xFF
  packet[2]++;
  printf("Y=-%u ", packet[2]);
}
else
printf("Y=%u ", packet[2]);

}
