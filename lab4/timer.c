#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/driver.h>
#include "i8254.h"
#include "timer.h"

int hook_id = 0;
unsigned int counter = 0;


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


	unsigned long controlWord = ((TIMER_SEL0 + timer) | TIMER_LSB_MSB | preservedBits);

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

void timer_int_handler() {
	counter++;
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

int timer_display_conf(unsigned char conf) {

	printf("Status of the timer: 0x%x\n", conf); //displays the byte written in the control register

	if ((conf & 0x01) == TIMER_BIN)
		printf("The counting mode of the control word is fixed on Binary\n");
	else
		printf("The counting mode of the control word is fixed on BCD\n");

	unsigned int OperatingMode = ((conf & (BIT(3) | BIT(2) | BIT(1))) >> 1); // logical and of conf and 00001110, followed by a right shift

	switch (OperatingMode) {
	case 0:
		printf("The operating mode is fixed on 0.\n");
		break;
	case 1:
		printf("The operating mode is fixed on 1.\n");
		break;
	case 2:
		printf("The operating mode is fixed on 2.\n");
		break;
	case 3:
		printf("The operating mode is fixed on 3.\n");
		break;
	case 4:
		printf("The operating mode is fixed on 4.\n");
		break;
	case 5:
		printf("The operating mode is fixed on 5.\n");
		break;
	case 6:
		printf("The operating mode is fixed on 2.\n");
		break;
	case 7:
		printf("The operating mode is fixed on 3.\n");
		break;
	default:
		printf("The number of the operating mode isn't valid...\n");
		return 1;
	}

	unsigned char TypeOfAccess = (conf & (BIT(5) | BIT(4)));

	if (TypeOfAccess == TIMER_LSB)
		printf("The type of access is LSB\n");
	else if (TypeOfAccess == TIMER_MSB)
		printf("The type of access is MSB\n");
	else if (TypeOfAccess == TIMER_LSB_MSB)
		printf("The type of access is LSB followed by MSB\n");
	else {
		printf("The number of type of access isn't valid...\n");
		return 1;
	}

	unsigned char NullCount = (conf & (BIT(6)));

	if(NullCount == BIT(6)){
		printf("Counter is 1.\n");
	}
	else
		printf("Counter is 0.\n");


	unsigned char Output = (conf & (BIT(7)));

	if(Output == BIT(7)){
		printf("Output is 1.\n");
	}
	else
		printf("Output is 0.\n");

	return 0;
}

int timer_test_time_base(unsigned long freq) {

	timer_set_frequency(0, freq);  //calls timer_set_frequency using timer 0
	return 0;
}

int timer_test_int(unsigned long time) {

	int ipc_status, r;
	message msg;
	unsigned char irq_set = timer_subscribe_int();


	if (timer_subscribe_int() == -1) {
		printf("Error in timer_subscribe_int!\n");
		return 1;
	}

	// executes cycle while counter is <= than the total interruptions
	while (counter <= (60 * time)) { //get a request message

		r = driver_receive(ANY, &msg, &ipc_status);

		if (r != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}

		if (is_ipc_notify(ipc_status)) {
			switch (_ENDPOINT_P(msg.m_source)) {

			case HARDWARE:    //hardware interrupt notification
				if (msg.NOTIFY_ARG & irq_set) {

					timer_int_handler(); //increments counter
					if (counter % 60 == 0)
							printf("One second has passed\n");
				}
				break;
			default:
				break;
			}
		} else {
		}
	}

	if (timer_unsubscribe_int() == 1) {
		printf("Error in timer_unsubscribe_int!\n");
		return 1;
	}

	return 0;
}

int timer_test_config(unsigned char timer) {
	unsigned char conf;
	timer_get_conf(timer, &conf);
	timer_display_conf(conf);
	return 0;
}
