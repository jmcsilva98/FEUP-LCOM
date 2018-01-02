#ifndef MATRIX_H
#define MATRIX_H
#include "game.h"

/**defgroup matrix matrix
 *@{
 * Functions that handle the game matrix
 */
extern Bubble * m[50][12]; ///game matrix
Bubble * bubblesToExplode[50];

/**
 * @brief Allocates the initial matrix
 *
 * @param ColourPop  pointer to an object of the Game struct
 *
 */
void allocateInitialMatrix(Game *ColourPop);

/**
 * @brief Allocates matrix row
 *
 * @param ColourPop   pointer to an object of the Game struct
 * @param c_column    column index
 */
void allocateRow(Game *ColourPop, unsigned int c_column);

/**
 * @brief Adds a row of bubbles at the begining of the matrix
 *
 * @param ColourPop  pointer to an object of the Game struct
 */
void addRow(Game *ColourPop);

/**
 * @brief Initializes bubbles to explode
 */
void initializeBubblesToExplode();

/**
 * @brief Places throwing bubble in the matrix
 *
 * @param ColourPop       pointer to an object of the Game struct
 * @param throwing_bubble pointer to an object of the Bubble struct, in this case the throwing bubble
 * @param b_colision      pointer to an object of the Bubble struct
 */

void snapIntoGrid(Game * ColourPop, Bubble * throwing_bubble, Bubble * b_colision);

/**
 * @brief Checks if row was added successfully
 *
 * @param  ColourPop  pointer to an object of the Game struct
 *
 * @return 0 if success, non-zero otherwise
 */

int checkIfRowAdded(Game * ColourPop);

/**
 * @brief Adds bubbles to explode
 *
 * @param b pointer to an object of the Bubble struct
 */
void addToBubblesToExplode(Bubble * b);

/**
 * @brief Checks if the buuble is to explode
 *
 * @param  b pointer to an object of the Bubble struct
 *
 * @return  1 if the bubble is to explode, 0 if not
 */

int findInBubblesToEXplode(Bubble * b);

/**
 * @brief Checks if the bubble is the same of its neighbours
 *
 * @param ColourPop pointer to an object of the Game struct
 * @param b         pointer to an object of the Bubble struct
 * @param i         column index
 * @param j         row index
 */

void checkNeighbours(Game *ColourPop, Bubble * b, unsigned int i, unsigned int j);

/**
 * @brief Explodes the bubbles of the same type
 *
 * @param ColourPop pointer to an object of the Game struct
 */

void explodeBubbles(Game *ColourPop);
/** @} end of matrix */
#endif/* MATRIX_H */
