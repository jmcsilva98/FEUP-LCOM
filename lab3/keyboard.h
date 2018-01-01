#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/driver.h>
#include "timer.h"
#include "i8042.h"
#include "test3.h"

/*DECLARATION OF ADDED FUNCTIONS*/
int subscribe_kb(int *hook_id_kb);
int unsubscribe_kb(int *hook_id_kb);
void kbc_handler_asm();
int send_cmd_kbc(unsigned long cmd, unsigned long reg);
int kbc_handler_c();
void printScancodes();




 #endif
