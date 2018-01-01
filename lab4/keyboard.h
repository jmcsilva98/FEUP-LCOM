#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/driver.h>
#include "timer.h"
#include "i8042.h"

extern int hook_id_kb;
/*DECLARATION OF ADDED FUNCTIONS*/
int subscribe_kb(int *hook_id_kb);
int unsubscribe_kb(int *hook_id_kb);
int send_cmd_kbc(unsigned long cmd, unsigned long reg);
int kbc_handler_c();
void printScancodes();




 #endif
