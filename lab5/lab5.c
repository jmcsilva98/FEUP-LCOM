#include "test5.h"
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <minix/drivers.h>
#include "pixmax.h"
#include "read_xpm.h"


static int proc_args(int argc, char **argv);
static unsigned long parse_ulong(char *str, int base);
static void print_usage(char **argv);


int main(int argc, char **argv)
{
	sef_startup(); /*Service initialization*/

	sys_enable_iop(SELF); /*Enable IO-sensitive operations for ourselfs*/

	if (argc == 1) {					/* Prints usage of the program if no arguments are passed */
		print_usage(argv);
		return 0;
	}
	else return proc_args(argc, argv);

}


static void print_usage(char **argv)
{
	printf("Usage: one of the following:\n"
			"\t service run %s -args \"test_init <mode> <delay>\"\n"
			"\t service run %s -args \"test_square <x, y, size, color>\"\n"
      "\t service run %s -args \"test_line <xi, yi, xf, yf, color>\"\n"
			"\t service run %s -args \"test_xpm <xpm[], xi, yi>\"\n"
			"\t service run %s -args \"test_move <xpm[], xi, yi, xf, yf, speed, frame_rate>\"\n"
			"\t service run %s -args \"test_controller\"\n",
				argv[0], argv[0], argv[0], argv[0], argv[0], argv[0]);
}

static int proc_args(int argc, char **argv)
{
	unsigned short mode, delay, x, y, size, xi, yi, xf, yf;
	short speed;
	unsigned short frame_rate;
  unsigned long color;

	if (strncmp(argv[1], "test_init", strlen("test_init")) == 0) {
		if (argc != 4) {
			printf("test_init: wrong no. of arguments for video_test_init()\n");
			return 1;
		}
		mode = parse_ulong(argv[2], 16);						/* Parses string to unsigned long */
		if (mode == ULONG_MAX)
			return 1;
    delay = parse_ulong(argv[3], 10);						/* Parses string to unsigned long */
  	if (delay == ULONG_MAX)
  	return 1;

		printf("test5::video_test_init(%lu,%lu)\n", mode, delay);
		return (int)video_test_init(mode, delay);
	}


	else if (strncmp(argv[1], "test_square", strlen("test_square")) == 0) {
		if (argc != 6) {
			printf("test_square : wrong no. of arguments for video_test_square()\n");
			return 1;
		}
		x = parse_ulong(argv[2], 10);						/* Parses string to unsigned long */
		if (x == ULONG_MAX)
			return 1;
    y = parse_ulong(argv[3], 10);						/* Parses string to unsigned long */
    if (y == ULONG_MAX)
    return 1;
    size = parse_ulong(argv[4], 10);						/* Parses string to unsigned long */
    if (size == ULONG_MAX)
    return 1;
    color = parse_ulong(argv[5], 10);						/* Parses string to unsigned long */
    if (color == ULONG_MAX)
      return 1;
		printf("test5::video_test_square(%lu,%lu,%lu,%lu)\n", x, y, size, color);
		return video_test_square(x, y, size, color);
	}

	else if (strncmp(argv[1], "test_line", strlen("test_line")) == 0) {
		if (argc != 7) {
			printf("test_line : wrong no of arguments for video_test_line())\n");
			return 1;
		}
		xi = parse_ulong(argv[2], 10);						/* Parses string to unsigned long */
		if (xi == ULONG_MAX)
			return 1;
    yi = parse_ulong(argv[3], 10);						/* Parses string to unsigned long */
  	if (yi == ULONG_MAX)
  	return 1;
    xf = parse_ulong(argv[4], 10);						/* Parses string to unsigned long */
		if (xf == ULONG_MAX)
		return 1;
    yf = parse_ulong(argv[5], 10);						/* Parses string to unsigned long */
		if (xi == ULONG_MAX)
		return 1;
    color = parse_ulong(argv[6], 10);						/* Parses string to unsigned long */
		if (color == ULONG_MAX)
		return 1;

		printf("test5::video_test_line(%lu,%lu,%lu,%lu,%lu)\n", xi, yi, xf, yf, color);
		return video_test_line( xi, yi, xf, yf, color);
	}

	else if (strncmp(argv[1], "test_xpm", strlen("test_xpm")) == 0) {
		if (argc != 5) {
			printf("test_xpm : wrong no of arguments for video_test_xpm())\n");
			return 1;
		}

		xi = parse_ulong(argv[3], 10);						/* Parses string to unsigned long */
		if (xi == ULONG_MAX)
			return 1;
    yi = parse_ulong(argv[4], 10);						/* Parses string to unsigned long */
  	if (yi == ULONG_MAX)
  	return 1;

		if((strncmp(argv[2], "pic1", strlen("pic1")) == 0)){
		printf("test5::video_test_xpm(%s,%lu,%lu)\n", "pic1", xi, yi);
		return video_test_xpm(pic1, xi, yi);
		}

		else if((strncmp(argv[2], "pic2", strlen("pic2")) == 0)){
		printf("test5::video_test_xpm(%s,%lu,%lu)\n", "pic2", xi, yi);
		return video_test_xpm(pic2, xi, yi);
		}

		else if((strncmp(argv[2], "cross", strlen("cross")) == 0)){
		printf("test5::video_test_xpm(%s,%lu,%lu)\n", "cross", xi, yi);
		return video_test_xpm(cross, xi, yi);
		}

		else if((strncmp(argv[2], "pic3", strlen("pic3")) == 0)){
		printf("test5::video_test_xpm(%s,%lu,%lu)\n", "pic3", xi, yi);
		return video_test_xpm(pic3, xi, yi);
		}

		else if((strncmp(argv[2], "penguin", strlen("penguin")) == 0)){
		printf("test5::video_test_xpm(%s,%lu,%lu)\n", "penguin", xi, yi);
		return video_test_xpm(penguin, xi, yi);
		}

		else{
				printf("test5 : Pic wanted not available\n", argv[2]);
				return 1;
		}

	}


	else if (strncmp(argv[1], "test_move", strlen("test_move")) == 0) {
	if (argc != 9) {
	printf("test_move : wrong no of arguments for video_test_move())\n");
	return 1;
	}

	xi = parse_ulong(argv[3], 10);						/* Parses string to unsigned long */
	if (xi == ULONG_MAX)
		return 1;
	yi = parse_ulong(argv[4], 10);						/* Parses string to unsigned long */
	if (yi == ULONG_MAX)
	return 1;
	xf = parse_ulong(argv[5], 10);						/* Parses string to unsigned long */
	if (xf == ULONG_MAX)
		return 1;
	yf = parse_ulong(argv[6], 10);						/* Parses string to unsigned long */
	if (yf == ULONG_MAX)
	return 1;
	speed = parse_ulong(argv[7], 10);						/* Parses string to unsigned long */
	if (speed == ULONG_MAX)
		return 1;
	frame_rate = parse_ulong(argv[8], 10);						/* Parses string to unsigned long */
	if (frame_rate == ULONG_MAX)
	return 1;

	if((strncmp(argv[2], "pic1", strlen("pic1")) == 0)){
	printf("test5::video_test_move(%s,%lu,%lu,%lu,%lu,%lu,%lu)\n", "pic1", xi, yi,xf,yf,speed,frame_rate);
	return video_test_move(pic1, xi, yi, xf, yf,speed, frame_rate);
	}

	else if((strncmp(argv[2], "pic2", strlen("pic2")) == 0)){
	printf("test5::video_test_move(%s,%lu,%lu,%lu,%lu,%lu,%lu)\n", "pic2", xi, yi,xf,yf,speed,frame_rate);
	return video_test_move(pic2, xi, yi, xf, yf,speed, frame_rate);
	}

	else if((strncmp(argv[2], "cross", strlen("cross")) == 0)){
	printf("test5::video_test_move(%s,%lu,%lu,%lu,%lu,%lu,%lu)\n", "cross", xi, yi,xf,yf,speed,frame_rate);
	return video_test_move(cross, xi, yi, xf, yf,speed, frame_rate);
	}

	else if((strncmp(argv[2], "pic3", strlen("pic3")) == 0)){
	printf("test5::video_test_move(%s,%lu,%lu,%lu,%lu,%lu,%lu)\n", "pic3", xi, yi,xf,yf,speed,frame_rate);
	return video_test_move(pic3, xi, yi, xf, yf,speed, frame_rate);
	}

	else if((strncmp(argv[2], "penguin", strlen("penguin")) == 0)){
	printf("test5::video_test_move(%s,%lu,%lu,%lu,%lu,%lu,%lu)\n", "penguin", xi, yi,xf,yf,speed,frame_rate);
	return video_test_move(penguin, xi, yi, xf, yf,speed, frame_rate);
	}

	else{
			printf("test5 :, Pic wanted not available\n", argv[2]);
			return 1;
	}
}

else if (strncmp(argv[1], "test_controller", strlen("test_controller")) == 0) {


	printf("test5::test_controller()\n");
	return test_controller();
}
	return 0;
}

static unsigned long parse_ulong(char *str, int base)
{
	char *endptr;
	unsigned long val;

	/* Convert string to unsigned long */
	val = strtoul(str, &endptr, base);

	/* Check for conversion errors */
	if ((errno == ERANGE && val == ULONG_MAX) || (errno != 0 && val == 0)) {
		perror("strtoul");
		return ULONG_MAX;
	}

	if (endptr == str) {
		printf("timer: parse_ulong: no digits were found in %s\n", str);
		return ULONG_MAX;
	}

	/* Successful conversion */
	return val;
}
