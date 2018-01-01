#ifndef __MOUSE_H
#define __MOUSE_H


#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/driver.h>
#include "i8042.h"
extern int hook_id_mouse;
extern int packet[3];

/*DECLARATION OF ADDED FUNCTIONS*/


int subscribe_mouse(int *hook_id_mouse) ;
int unsubscribe_mouse(int *hook_id_mouse);
unsigned long mouse_handler();
int write_mouse(unsigned long cmd);
int enable_sMode();
int disable_sMode();
int enable_packets();
void print_packets();






 #endif
