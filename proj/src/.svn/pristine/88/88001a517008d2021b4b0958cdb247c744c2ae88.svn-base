#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/driver.h>
#include "timer.h"
#include "i8042.h"
#include "game.h"

/**defgroup keyboard keyboard
*@{
* Functions that involve the keyboard
*/


extern int hook_id_kb;
extern unsigned long scancode;

/**
 * @bried Subscribes the keyboard interrupts
 *
 * @param  hook_id_kb hook id of the keyboard
 *
 * @return 0 if subscribing successful, non-zero otherwise
 */

int subscribe_kb(int *hook_id_kb);

/**
 * @brief Unsubscribes the keyboard interrupts
 *
 * @param  hook_id_kb hook id of the keyboard
 *
 * @return 0 if unsubscribing successful, non-zero otherwise
 */

int unsubscribe_kb(int *hook_id_kb);

/**
 * @brief if ass == 1, reads data in assembly, if 0 reads data in c
 *
 * @param  ColourPop  pointer to an object of the struct Game
 * @param  ass        integer that tells if we are reading in assembly or c
 *
 * @return 0 if reading successful, non-zero otherwise
 */

int kbc_handler(Game *ColourPop, int ass);
/**
 * @brief Sends command to the kbc
 *
 * @param  cmd command that needs to be send
 * @param  reg register where the cmd is sent
 *
 * @return 0 if successful, non-zero otherwise
 */

int send_cmd_kbc(unsigned long cmd, unsigned long reg);

/**
 * @brief Cleans the output buffer of the keyboard
 *
 * @return 0 if successful, non-zero otherwise
 */

int readOutBuffer();

/**
 * @brief Checks the events of the keyboard
 *
 * @param ColourPop pointer to an object of the struct Game
 */

void check_keyboard_events(Game * ColourPop);


unsigned long read_asm();/// reads in assembly
/** @} end of keyboard */
 #endif/* KEYBOARD_H */
