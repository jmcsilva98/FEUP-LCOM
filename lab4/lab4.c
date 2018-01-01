#include "test4.h"
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <minix/drivers.h>


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
			"\t service run %s -args \"test_packet <decimal no. number of packets>\"\n"
			"\t service run %s -args \"test_async <time without packets>\"\n"
      "\t service run %s -args \"test_remote <period in ms> <decimal no. number of packets>\"\n"
			"\t service run %s -args \"test_gesture <length> \"\n",
				argv[0], argv[0], argv[0], argv[0]);
}

static int proc_args(int argc, char **argv)
{
	unsigned short n_Packets, idle_time, period;
	short length;

	if (strncmp(argv[1], "test_packet", strlen("test_packet")) == 0) {
		if (argc != 3) {
			printf("test_packet: wrong no. of arguments for mouse_test_packet()\n");
			return 1;
		}
		n_Packets = parse_ulong(argv[2], 10);						/* Parses string to unsigned long */
		if (n_Packets == ULONG_MAX)
			return 1;
		printf("test4::mouse_test_packet(%d)\n", n_Packets);
		return mouse_test_packet(n_Packets);
	}


	else if (strncmp(argv[1], "test_async", strlen("test_async")) == 0) {
		if (argc != 3) {
			printf("test_async : wrong no. of arguments for mouse_test_async()\n");
			return 1;
		}
		idle_time = parse_ulong(argv[2], 10);						/* Parses string to unsigned long */
		if (idle_time == ULONG_MAX)
			return 1;
		printf("test4::mouse_test_async(%d)\n", idle_time);
		return mouse_test_async(idle_time);
	}

	else if (strncmp(argv[1], "test_remote", strlen("test_remote")) == 0) {
		if (argc != 4) {
			printf("test_remote : wrong no of arguments for mouse_test_remote())\n");
			return 1;
		}
		period = parse_ulong(argv[2], 10);						/* Parses string to unsigned long */
		if (period == ULONG_MAX)
			return 1;
		n_Packets = parse_ulong(argv[3], 10);						/* Parses string to unsigned long */
		if (n_Packets == ULONG_MAX)
			return 1;
		printf("test4::mouse_test_remote(%d, %d)\n", period, n_Packets);
		return mouse_test_remote(period, n_Packets);
	}

	else if (strncmp(argv[1], "test_gesture", strlen("test_gesture")) == 0) {
		if (argc != 3) {
			printf("test_gesture : wrong no. of arguments for mouse_test_gesture()\n");
			return 1;
		}
		length = (short) parse_ulong(argv[2], 10);						/* Parses string to unsigned long */
		if (length == ULONG_MAX)
			return 1;
		printf("test4::mouse_test_gesture(%d)\n", length);
		return mouse_test_gesture(length);
	}

	else {
		printf("test4: %s - no valid function!\n", argv[1]);
		return 1;
	}
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
