#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "game.h"

/**@defgroup graphics graphics
*@{
*/
extern Bubble * m[50][12];

/**
 * @struct Spear
 * @brief Struct of the spear that is used to launch the bubbles
 */
typedef struct {
	int angle; ///< spear's angle

	/**@name All of the spear bitmaps*/
  /**@{
  */
  Bitmap * s0;
  Bitmap * s1;
	Bitmap * s2;
	Bitmap * s3;
	Bitmap * s4;
	Bitmap * s5;
	Bitmap * s6;
	Bitmap * s7;
	Bitmap * s8;
	Bitmap * s9;
	Bitmap * sm1;
	Bitmap * sm2;
	Bitmap * sm3;
	Bitmap * sm4;
	Bitmap * sm5;
	Bitmap * sm6;
	Bitmap * sm7;
	Bitmap * sm8;
	Bitmap * sm9;

	/** @} end of the spear bitmaps */
	int reverse_change; ///< 1 if the spear diretion has changed,zero otherwise
} Spear;


/**
 * @struct Bar
 * @brief Bar struct
 */

typedef struct {
	Bitmap * bitmap; ///< bitmap of the bar
	unsigned int xi; ///< bar's horizontal position
	unsigned int yi;///< bar's vertical position
} Bar;


/**
 * @struct Score
 * @brief Score's struct
 */
typedef struct {
	Bitmap * character_1; ///< bitmap of the first algarism of the score
	Bitmap * character_2; ///< bitmap of the second algarism of the score
	Bitmap * character_3;	///< bitmap of the third algarism of the score
} Score;


/**
 * @brief Initializes the spear. Loads the bitmaps and allocates memory
 *
 * @return pointer to the struct Spear
 */

Spear * newSpear();

/**
 * @brief If there isn't a spear creates one, else returns the existing one
 *
 * @return pointer to the struct Spear
 */

Spear * getSpear();

/**
 * @brief Updates the spear's position and consequently its bitmap
 *
 * @param ColourPop   pointer to an object of the struct Game
 */

void updateSpear(Game * ColourPop);

/**
 * @brief Frees the allocated memory
 */
void deleteSpear();

/**
 * @brief Initializes the bar
 * @return pointer to the struct Bar
 */

Bar * newBar();

/**
*@brief If there isn't a bar creates one, else returns the existing one
*
*@return pointer to the struct Bar
*/

Bar * getBar();

/**
 * Frees the allocated memory
 */
void deleteBar();

/**
 * @brief Draws game matrix
 *
 * @param ColourPop  pointer to an object of the struct Game
 */
void drawMatrix(Game *ColourPop);

/**
 * @brief Draws matrix row
 *
 * @param ColourPop  pointer to an object of the struct Game
 * @param c_column  column index
 */
void drawRow(Game *ColourPop, unsigned int c_column);

/**
 * @brief Checks the given bubble's throwing diretion
 *
 * @param ColourPop  pointer to an object of the struct Game
 * @param b        	 pointer to an object of the struct Bubble
 */
void throwingDirection(Game * ColourPop, Bubble * b);

/**
 * @brief Checks movement of the throwing bubble
 *
 * @param  ColourPop	 pointer to an object of the struct Game
 *
 * @return pointer to the Bubble struct
 */

Bubble * checkMovement(Game * ColourPop);

/**
 * @brief The new throwing bubble is the previous next bubble and generates a new next bubble
 *
 * @param ColourPop  pointer to an object of the struct Game
 */
void changeThrowingBubble(Game * ColourPop);

/**
 * @brief Turns all bubbles black when the game is over
 *
 * @param ColourPop  pointer to an object of the struct Game
 */

void turnBubblesBlack(Game * ColourPop);

/**
 * @brief Converts an algarism to the equivalent bitmap
 *
 * @param  char to convert
 * @param  ColourPop   pointer to an object of the struct Game
 *
 * @return  pointer to equivalent Bitmap
 */

Bitmap * convertCharToBMP(char key, Game * ColourPop);

/**
* @brief Converts a key scancode to the equivalent char
*
* @param scancode
*
* @return equivalent char
*/
char convertScancodeToChar(unsigned long code);

/**
 * @brief Converts an algarism to the equivalent bitmap
 *
 * @param  date_number algarism of the date
 * @param  ColourPop   pointer to an object of the struct Game
 *
 * @return   pointer to number's bitmap
 */
Bitmap * convertDateToBMP(int date_number, Game * ColourPop);

/**
 * @brief Displays a number with one or two algarisms
 *
 * @param ColourPop 	pointer to an object of the struct Game
 * @param number    	number that we need to dispay
 * @param x         	x coordinate of the number
 * @param y         	y coordinate of the number
 *
*/

void ShowNumber(Game * ColourPop, int number, int x, int y);


/**
 * @brief Displays a player's name
 *
 * @param ColourPop 	pointer to an object of the struct Game
 * @param number    	number that we need to dispay
 * @param name 				pointer to array containing name string
 * @param x         	x coordinate of the number
 * @param y         	y coordinate of the number
 *
*/
void showName(Game * ColourPop, char * name, unsigned int x, unsigned int y);

/**
 * @brief Shows current date and hour in the game
 *
 * @param ColourPop  pointer to an object of the struct Game
 */
void showDate(Game * ColourPop, Date * date, unsigned int xi, unsigned int yi);

/**
 * @brief Shows real time in the game
 *
 * @param ColourPop  pointer to an object of the struct Game
 */
void showTime(Game * ColourPop, Date * date, unsigned int xi, unsigned int yi);


/**
 * @brief Displays graphics needed in game
 *
 * @param ColourPop 	pointer to an object of the struct Game
 */
void drawGame(Game * ColourPop);

/**
 * @brief Displays main menu
 *
 * @param ColourPop  pointer to an object of the struct Game
 */
void drawMenu(Game * ColourPop);

/**
 * @brief Displays paused menu
 *
 * @param ColourPop	 pointer to an object of the struct Game
 */
void drawPausedMenu(Game * ColourPop);

/**
 * @brief Displays highscores menu
 *
 * @param ColourPop	 pointer to an object of the struct Game
 */
void drawHighscoresMenu(Game * ColourPop);

/**
 * @brief Displays game over menu
 *
 *  @param ColourPop	 pointer to an object of the struct Game
 */
void drawGameOverMenu(Game * ColourPop);

/**
 * @brief Displays enter name menu
 *
 *  @param ColourPop	 pointer to an object of the struct Game
 */
void drawEnterNameMenu(Game * ColourPop);

/**
 * @brief Displays current game score
 * @param ColourPop 	pointer to an object of the struct Game
 * @param score				score to be dispplayed
 * @param xi        	initial x coordinate
 * @param xf        	final x coordinate
 * @param yi        	initial y coordinate
 */
void drawScore(Game * ColourPop, unsigned int score, unsigned int xi, int xf,unsigned int yi);

/**
 * @brief Updates frame as player writes name
 *
 *  @param ColourPop	 pointer to an object of the struct Game
 */
void enterName(Game * ColourPop);


/** @} end of graphics */
#endif /* GRAPHICS_H */
