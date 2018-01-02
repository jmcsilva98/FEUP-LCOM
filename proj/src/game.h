
#ifndef GAME_H
#define GAME_H

#include "bitmap.h"
#include "mouse.h"
#include "bubbles.h"
#include "rtc.h"

/** @defgroup game game
* @{
*/

/**
 * @struct Game
 * @brief Struct that represents the game
 */
typedef struct{
  Date * date;
  unsigned int score;
  char name[5];
} High_Score;


typedef struct {

  int irq_set_kb; ///< states the keyboard irq
  int irq_set_timer; ///< states the timer irq
  int irq_set_mouse; ///< states the mouse irq
  int irq_set_rtc; ///< states the rtc irq

  unsigned char packets[3]; ///< mouse packets of the last interrupt
  int t_counter; ///< timer counter
  int m_counter; ///< mouse packets counter
  unsigned long scancode; ///< keyboard last interrupt scancode
  int done; ///< if 1, exit game
  unsigned int rows; ///< number of rows in the game matrix
  unsigned int score; ///< game score
  char name[5];

  Date * date; ///< pointer to the Date struct
  High_Score * high_score_1; ///< pointer to the High_Score struct
  High_Score * high_score_2;  ///< pointer to the High_Score struct
  High_Score * high_score_3;  ///< pointer to the High_Score struct
 /**@name bitmaps*/
 /**@{
 */
  Bitmap * playingBackground;
  Bitmap * blueball;
  Bitmap * silverball;
  Bitmap * greenball;
  Bitmap * yellowball;
  Bitmap * pinkball;
  Bitmap * tunel;
  Bitmap * cursor;
  Bitmap * spear;
  Bubble * throwingBubble;
  Bubble * nextBubble;
  Bitmap * menu;
  Bitmap * limitBar;
  Bitmap * gameOverMenu;
  Bitmap * gameOverMenu2;
  Bitmap * pausedMenu;
  Bitmap * enterNameMenu;
  Bitmap * highScoresMenu;

  //Numbers
  Bitmap * n0;
  Bitmap * n1;
  Bitmap * n2;
  Bitmap * n3;
  Bitmap * n4;
  Bitmap * n5;
  Bitmap * n6;
  Bitmap * n7;
  Bitmap * n8;
  Bitmap * n9;

  //letter
  Bitmap * a;
  Bitmap * b;
  Bitmap * c;
  Bitmap * d;
  Bitmap * e;
  Bitmap * f;
  Bitmap * g;
  Bitmap * h;
  Bitmap * i;
  Bitmap * j;
  Bitmap * k;
  Bitmap * l;
  Bitmap * m;
  Bitmap * n;
  Bitmap * o;
  Bitmap * p;
  Bitmap * q;
  Bitmap * r;
  Bitmap * s;
  Bitmap * t;
  Bitmap * u;
  Bitmap * w;
  Bitmap * v;
  Bitmap * x;
  Bitmap * y;
  Bitmap * z;

  Bitmap * dash;
  Bitmap * colon;
  Bitmap * score_bitmap;
/** @} end of bitmaps */
} Game;

/**
 * @brief Initializes the game
 *
 * Subscribes timer, keyboard, mouse and rtc. Loads bitmaps in the Game struct, creates date and allocates the game's initial matrix
 *
 * @return pointer of the struct Game
 */

Game * startGame();

/**
 * @brief Handles the interrupts from the devices used (timer, keyboard, mouse and rtc). Unsubscribes the devices and calls function to free de game
 *
 *  @param ColourPop  pointer to an object of the struct Game
 *
 *  @return  0 if success and non-zero otherwise
 */

int interrupt_h(Game * ColourPop);

/**
 * @brief Handles timer interrupts
 *
 * @param ColourPop  pointer to an object of the struct Game
 */

void timer_h(Game * ColourPop);

/**
 * @brief Handles keyboard interrupts
 *
 * @param ColourPop  pointer to an object of the struct Game
 */

void keyboard_h(Game * ColourPop);

/**
 * @brief Handles mouse interrupts. Reads the packets
 *
 * @param ColourPop  pointer to an object of the struct Game
 */

void mouse_h(Game * ColourPop);

/**
 * @brief Updates the position of the mouse cursor and checks if the right or left button are being pressed
 *
 *  @param ColourPop  pointer to an object of the struct Game
 */

void updateMouse(Game * ColourPop);

/**
 * @brief Frees all of the allocated memory
 *
 * @param ColourPop  pointer to an object of the struct Game
 */

void freeGame(Game * ColourPop);
/**
 * @brief
 *
 *  @param ColourPop  pointer to an object of the struct Game
 */
void updateWithTimer(Game * ColourPop);

/**
 * @brief Checks if the number of rows has exceeded the line over bar and updates highscore
 *
 *  @param ColourPop   pointer to an object of the struct Game
 */

void checkIfLost(Game * ColourPop);
/**
 * @brief deletes allocated memory of the game matrix, deleting the bubbles
 *
 * @param ColourPop  pointer to an object of the struct Game
 */

void freeMatrix(Game * ColourPop);

/**
 * @brief Allocates a new game
 *
 * @param ColourPop  pointer to an object of the struct Game
 */
void playAgain(Game * ColourPop);


/** @} end of game */

#endif /* GAME_H */
