#include "test3.h"
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
			"\t service run %s -args \"test_scan <decimal no. assembly = 1, c = 0\"\n"
			"\t service run %s -args \"test_poll\"\n"
			"\t service run %s -args \"test_timed_scan <seconds> \"\n",
				argv[0], argv[0], argv[0]);
}

static int proc_args(int argc, char **argv)
{
	unsigned short ass, time;

	if (strncmp(argv[1], "test_scan", strlen("test_scan")) == 0) {
		if (argc != 3) {
			printf("test_scan : wrong no. of arguments for kbd_test_scan()\n");
			return 1;
		}
		ass = parse_ulong(argv[2], 10);						/* Parses string to unsigned long */
		if (ass == ULONG_MAX)
			return 1;
		printf("test3::kbd_test_scan(%lu)\n", ass);
		return kbd_test_scan(ass);
	}


	else if (strncmp(argv[1], "test_poll", strlen("test_poll")) == 0) {
		if (argc != 2) {
			printf("test3: wrong no. of arguments for kbd_test_poll()\n");
			return 1;
		}
		printf("test3::kbd_test_poll()\n");
		return kbd_test_poll();
	}

	else if (strncmp(argv[1], "test_timed_scan", strlen("test_timed_scan")) == 0) {
		if (argc != 3) {
			printf("test3: wrong no of arguments for kbd_test_timed_scan()\n");
			return 1;
		}
		time = parse_ulong(argv[2], 10);						/* Parses string to unsigned long */
		if (time == ULONG_MAX)
			return 1;
		printf("test3::kbd_test_timed_scan(%lu)\n", time);
		return kbd_test_timed_scan(time);
	}
	else {
		printf("test3: %s - no valid function!\n", argv[1]);
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


