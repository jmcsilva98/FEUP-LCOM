#include "test3.h"
#include "keyboard.h"

int hook_id_kb = 1;
unsigned long scancode;
unsigned int counter_inb;



int kbd_test_scan(unsigned short ass) {


	message msg;
	int ipc_status, r;
	unsigned int irq_set = subscribe_kb(&hook_id_kb);

	if (irq_set == -1) {
		printf("Error subscribing the keyboard.\n");
		return 1;
	}

	while (scancode != ESC_KEY) { //get a request message

		r = driver_receive(ANY, &msg, &ipc_status);

		if (r != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}

		if (is_ipc_notify(ipc_status)) {
			switch (_ENDPOINT_P(msg.m_source)) {

			case HARDWARE:    //hardware interrupt notification
				if (msg.NOTIFY_ARG & irq_set) {
					if(ass == 0){
						kbc_handler_c();
					}
					else if (ass==1){
						kbc_handler_asm();
					}


					if (scancode == -1) {
						printf("Error in scancode\n");
						return -1;
					}
printScancodes();
				}
			}
	}}

	printf("Exit code was pressed!\n");

	if (unsubscribe_kb(&hook_id_kb) != OK) {
		printf("Error unsubscribing the keyboard\n");
		return 1;
	}
	//if it's in lab3 prints nº sys_inb calls
#ifdef 	LAB3
			if(ass == 0)
	printf("Number of accesses to sys_inb : %d \n",counter_inb);
#endif

	return 0;
}





int kbd_test_poll() {
	unsigned long data;
	counter_inb=0;

	//writing command in keyboard controller
	send_cmd_kbc(CMD,KBC_CMD_REG);

	if (sys_inb(OUT_BUF, &data) != OK) {
		printf("Error in sys_inb\n");
		return -1;
	}


	while (scancode != ESC_KEY) {
		kbc_handler_c();

		if (scancode == -1) {
			printf("Error in scancode\n");
			return -1;
		}
		printScancodes();
	}
	printf("Exit code was pressed!\n");

//if it's in lab3 prints nº sys_inb calls
	#ifdef LAB3
	printf("Number of accesses to sys_inb : %d \n",counter_inb);
	#endif

//reenabling Minix console
	send_cmd_kbc(OUT_BUF, KBC_CMD_REG);
	send_cmd_kbc(data|OBF, OUT_BUF);

	return 0;
}



int kbd_test_timed_scan(unsigned short n) {
	message msg;
	int ipc_status, r;
	unsigned int irq_set_kb = subscribe_kb(&hook_id_kb);
	unsigned int irq_set_timer = timer_subscribe_int();
	int counter = 0;

	if (n < 0) {
		printf("Time invalid\n");
		return 1;
	}

	/* subscribing timer and keyboard */
	if (timer_subscribe_int() == -1) {
		printf("Error in timer_subscribe_int!\n");
		return 1;
	}

	if (irq_set_kb == -1) {
		printf("Error subscribing the keyboard.\n");
		return 1;
	}

	while ((scancode != ESC_KEY) && counter <= (60 * n)) { //get a request message

		r = driver_receive(ANY, &msg, &ipc_status);

		if (r != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}

		if (is_ipc_notify(ipc_status)) {
			switch (_ENDPOINT_P(msg.m_source)) {

			case HARDWARE:    //hardware interrupt notification
				if (msg.NOTIFY_ARG & irq_set_timer) {
					counter++;
					//exits if number of seconds passed as variable is reached
					if (n * 60 == counter) {
						printf("%d seconds have passed!\n\n",n);
						return 0;
					}
				}
				if (msg.NOTIFY_ARG & irq_set_kb) {
					counter = 0;
					kbc_handler_c();
					if (scancode == -1) {
						printf("Error in scancode\n");
						return -1;
					}
					printScancodes();
				}
				break;
			}
		}
	}
	printf("Exit code was pressed!\n");

	/* unsubscribing timer and keyboard */

	if (timer_unsubscribe_int() == 1) {
		printf("Error in timer_unsubscribe_int!\n");
		return 1;
	}

	if (unsubscribe_kb(&hook_id_kb) != OK) {
		printf("Error unsubscribing the keyboard\n");
		return 1;
	}
	return 0;
}
