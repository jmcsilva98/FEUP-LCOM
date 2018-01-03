#ifndef __MOUSE_H
#define __MOUSE_H


#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/driver.h>
#include "i8042.h"
#include "bitmap.h"

/**defgroup mouse mouse
*@{
* Functions that involve the mouse
*/


extern int hook_id_mouse;
extern int packet[3];

/**
*@struct Mouse
*@brief Struct that includes all of the information needed for the mouse
*/
typedef struct {
	int x; ///< x coordinate of the mouse
	int y; ///< y coordinate of the mouse
	int left_button_pressed; ///< 1 if left button pressed
	int right_button_pressed; ///< 1 if right button pressed
	int left_button_released; ///< 1 if the left button is released
	int right_button_released; ///< 1 if the right button is released
	int deltax_pos; ///< positive deslocation in x
	int deltax_neg;///< negative deslocation in x


} Mouse;

/**
* @brief Subscribes the mouse interrupts
*
* @param  hook_id_mouse hook id of the mouse
*
* @return 0 if subscribing successful, non-zero otherwise
*/

int subscribe_mouse(int *hook_id_mouse) ;

/**
 * @bried Unsubscribes the mouse interrupts
 *
 * @param hook_id_mouse hook id of the mouse
 *
 * @return 0 if unsubscribing successful, non-zero otherwise
 */

int unsubscribe_mouse(int *hook_id_mouse);

/**
 * @brief if ass == 1, reads data in assembly, if 0 reads data in c
 *
 * @param  ass  integer that tells if we are reading in assembly or c
 *
 * @return data that has been read
 */

unsigned long mouse_handler(int ass);

/**
 * @brief Writes the given command to the mouse
 *
 * @param  cmd command that needs to be send
 *
 * @return 0 upon success, non-zero otherwise
 */

int write_mouse(unsigned long cmd);

/**
 * @brief Enables stream mode
 *
 * @return 0 upon success, non-zero otherwise
 */

int enable_sMode();

/**
 * @brief Disables the mouse (stream mode)
 *
 * @return 0 upon success, non-zero otherwise
 */

int disable_mouse();

/**
 * @brief Enables mouse packets
 *
 * @return 0 upon success, non-zero otherwise
 */

int enable_packets();

/**
 * @brief Displays mouse cursor
 */
void drawMouse();

/**
 * @brief If there isn't a mouse creates one, else returns the existing one
 *
 * @return pointer to Mouse struct
 */
Mouse * getMouse();

/**
 * @brief Frees the memory allocated by the mouse
 */

void deleteMouse();

/**
 * @brief Initializes the mouse and allocates memory
 * @return pointer to Mouse struct;
 */

Mouse * newMouse();

/**
 * @brief Checks the events of the mouse
 */
void check_mouse_events();

/**
 * @brief Checks if the mouse cursor is inside a given area
 *
 * @param  xi Horizontal left limit of the area
 * @param  xf Horizontal right limit of the area
 * @param  yi Vertical bottom limit of the area
 * @param  yf Vertical top limit of the area
 *
 * @return 1 if inside of the given area, 0 otherwise
 */

int check_mouse_click(unsigned int xi, unsigned int xf,unsigned int yi,unsigned int yf);

/** @} end of mouse */
 #endif/* MOUSE_H */
