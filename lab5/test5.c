#include "test5.h"
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/driver.h>
#include "read_xpm.h"
#include "lmlib.h"
#include "vbe.h"
#include "video_gr.h"
#include "i8254.h"
#include "i8042.h"
#include "timer.h"
#include "keyboard.h"
#include "video_test.h"
#include "sprite.h"
#include <stdint.h>
#include <machine/int86.h> // /usr/src/include/arch/i386



void *video_test_init(unsigned short mode, unsigned short delay) {

char *video_mem = vg_init(mode);
vbe_mode_info_t vbe_mode_info;

if(video_mem == NULL)
{
	vg_exit();
	printf("Error in vg_init\n");
	return NULL;
}

if(vbe_get_mode_info(mode, &vbe_mode_info)==1){
	printf("Error in vbe_get_mode_info\n");
	return NULL;
}

timer_test_int(delay);


if(vg_exit()!=0)
{
	printf("Error in vg_exit\n");
	return NULL;
}


return (void *) video_mem;
}


int video_test_square(unsigned short x, unsigned short y, unsigned short size, unsigned long color) {

		vg_init(0x105); //Changes to video mode

		//calls funtion to draw the square
		if(vg_draw_square(1024/2 + x- size/2, 768/2 + y - size/2, size, color) != 0){
			printf("Error in vg_draw_square\n");
			return 1;
		}

		video_dump_fb();
		kbd_test_scan();

		vg_exit();

		return 0;
}




int video_test_line(unsigned short xi, unsigned short yi,unsigned short xf, unsigned short yf, unsigned long color) {



	vg_init(0x105);

	vg_draw_line(xi, yi, xf, yf, color);

	video_dump_fb();

	//When the user releases the esc key the program goes back to the default text mode
	kbd_test_scan();

	vg_exit(); //Goes back to default text mode

	//TAMBEM SE TEM DE CHAMAR A FUNCAO get_mode_info, NAO PERCEBI ONDE - SUPOSTAMENTE JA SE CHAMA NA INIT

	return 0;
}


int video_test_xpm(char *xpm[], unsigned short xi, unsigned short yi){



	vg_init(0x105); //Changes to video mode

	//calls funtion to draw the square

	if(vg_xpm(xpm, xi,yi) != 0){
		printf("Error in vg_draw_square\n");
		return 1;
	}

	video_dump_fb();

	//When the user releases the esc key the program goes back to the default text mode

	kbd_test_scan();

	vg_exit(); //Goes back to default text mode

	return 0;

}


int video_test_move(char *xpm[], unsigned short xi, unsigned short yi, unsigned short xf, unsigned short yf, short speed, unsigned short frame_rate){


	message msg;
	int ipc_status, r;
	unsigned int irq_set_kb = subscribe_kb(&hook_id_kb);
	unsigned int irq_set_timer = timer_subscribe_int();
	int counter = 0;
	int fr;
	int xspeed, yspeed;
	int dx, dy;



	if(speed < 0)
	{
		fr = speed; //number of frames required
	}
		else
	{
		fr = 60/frame_rate;	//displacement in pixels between consecutive frames
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

	vg_init(0x105);

	if(xf < xi)
		xspeed = - speed;
	else
		xspeed = speed;

	if(yf < yi)
		yspeed = - speed;
	else
		yspeed = speed;


	dx = abs(xf-xi); //horizontal distance
	dy = abs(yf-yi); //vertical distance



	Sprite *sp = create_sprite(xpm, xi, yi, xspeed, yspeed);

	animate_sprite(sp);
	video_dump_fb();


	while (scancode != ESC_KEY) { //get a request message

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
					if (counter % fr == 0) {
						remove_sprite(sp);
						if(dx > dy)
						{
							sp->x += xspeed;
							animate_sprite(sp);
						}
						else
						{
							sp->y += yspeed;
							animate_sprite(sp);
					}}
				}
				if (msg.NOTIFY_ARG & irq_set_kb) {
					counter = 0;
					kbc_handler_c();
					if (scancode == -1) {
						printf("Error in scancode\n");
						return -1;
					}
				}
				break;
			}
		}

}

destroy_sprite(sp); //frees the memory ocupied by the sprite

video_dump_fb();


vg_exit(); //Goes back to default text mode

	return 0;
}

#define PB2BASE(x) (((x) >> 4) & 0x0F000)
#define PB2OFF(x) ((x) & 0x0FFFF)

int test_controller(){

	mmap_t buf;
	struct reg86u r;

	if(lm_init() == NULL)
	{
		printf("Error in test_controller : lm_init\n");
		return 1;
	}

	if(lm_alloc(sizeof(VbeInfoBlock), &buf) == NULL){
		printf("Error in test_controller : lm_alloc\n");
		return 1;}


VbeInfoBlock c;

r.u.w.ax = 0x4F00; /* VBE get mode info */
/* translate the buffer linear address to a far pointer */
r.u.w.es = PB2BASE(buf.phys); /* set a segment base */
r.u.w.di = PB2OFF(buf.phys); /* set the offset accordingly */
r.u.b.intno = 0x10;


if( sys_int86(&r) != OK ) {
	 /* call BIOS */
	 printf("Error in test_controller : sys_int86\n");
	 lm_free(&buf);
	 return 1;
}

c = *((VbeInfoBlock*)buf.virtual);

printf("%d.%d\n" , c.VbeVersion>>8, c.VbeVersion&0x0FF);



uint16_t *ptrVideoModes = (uint16_t *) c.Reserved;

while(*ptrVideoModes != 0x0FFFF )
{
	printf("0x%x:",*ptrVideoModes);
	ptrVideoModes++;
}
printf("\n");

printf("%d\n", c.TotalMemory* 64);

printf("%d\n", sizeof(VbeInfoBlock));

lm_free(&buf);

	return 0;
}
