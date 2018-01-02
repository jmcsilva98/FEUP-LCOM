#ifndef BUBBLES_H
#define BUBBLES_H

#include "bitmap.h"
#include <stdio.h>
#include <stdlib.h>

/**@defgroup bubbles bubbles
 *@{
 *
 * Funtions involving the game bubbles
 *
 */


/// Types of bubbles (color)
typedef enum {
	BLUE = 0,
  SILVER, PINK, YELLOW, GREEN, BLACK
} Type;

/**
 * @struct Bubble
 *
 * @brief Struct with necessary bubble information
 */

typedef struct {
  unsigned int upperLimit; ///< bubble's vertical max position
  unsigned int leftLimit; ///< bubble's horizontal left positon
  Type type; ///< type of bubble
  Bitmap * image; ///< bubble bitmap
	int exploded; ///< 1 if bubble exploded
} Bubble;

/**
 * @brief Draws the bitmap of the given bubble
 *
 * @param b - pointer to an object of the struct Bubble
 */

void drawBubble(Bubble * b);

/**
 * @brief Creates a bubble and alters the created bubble's characteristics, such has upperLimit, leftLimit, type and exploded
 *
 * @param  xi bubble's upper limit
 * @param  yi bubble's left limit
 *
 * @return pointer to the Bubble struct
 */

Bubble * generateBubble(unsigned int xi, unsigned int yi);

/**
 * @brief Deletes the given bubble's bitmap and frees the memory allocated
 *
 * @param b  pointer to an object of the struct Bubble
 */

void deleteBubble(Bubble * b);

/**
 * @brief Shows the exploding animation if the bubble still hasn't exploded and deletes the bubble if the animation already appeared
 * @param  b  pointer to an object of the struct Bubble
 * @return 0 if showing the exploding animation, 1 if deleted the bubble (bubble previously exploded)
 */
int explodeBubble(Bubble * b);

/**
 * @brief Loads the black type bubble bitmap
 * @param b  pointer to an object of the struct Bubble
 */

void turnBlack(Bubble * b);

/**
 * @brief Throws bubble with given angle until it reaches a certain vertical position
 *
 * @param b  pointer to an object of the struct Bubble
 * @param angle  bubble's moving angle
 * @param ymin  y max position the bubble can reach
 *
 */
void throwBubble_line(Bubble * b, int angle, unsigned int ymin);

/**
 * @brief Checks if there is colision between two bubbles
 * @param  b1  pointer to an object of the struct Bubble
 * @param  b2  pointer to an object of the struct Bubble
 *
 *  @return 1 if there's colision, 0 if not
 */
int checkColision(Bubble * b1, Bubble * b2);

/** @} end of bubbles */

#endif /* BUBBLES_H */
