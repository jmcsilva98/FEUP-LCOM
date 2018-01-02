#ifndef __GAMESTATES_H
#define __GAMESTATES_H
#include <stdio.h>
#include <stdlib.h>

/**@defgroup gamestates gamestates
 * @{
 * Functions that handle the state machine
 */

///Possible game states
typedef enum {
	MENU=0, PLAY_MODE, GAME_OVER, TURNING_BLACK, DONE, START_OVER, PAUSED, FINISHING_UP, HIGHSCORES_MENU, ENTER_NAME_MENU
}Game_State;

///Types of events in game
typedef enum {
	EXIT_BUTTON,
	PLAY_BUTTON,
	HIGHSCORES_BUTTON,
	ESCAPE,
	MOVE_SPEAR_RIGHT,
	MOVE_SPEAR_LEFT,
	LINE_OVER_BAR,
	TURNED_BLACK,
	PRESSED_KEY,
  EMPTY
}Game_Event;

/// Types of bubble events
typedef enum {
	THROW,
	THROW_RIGHT,
	THROW_LEFT,
	CHANGE,
	EXPLODING,
	DONE_THROWING
}Bubble_Event;

///States of bubbles
typedef enum {
	STILL,
	CHANGING,
	THROWING,
	THROWING_RIGHT,
	THROWING_LEFT
}Bubble_State;

/**
 * @struct State_Machine
 * @brief Struct of the state machine that operates the game
 */
typedef struct{
	Bubble_Event throwingBubbleEvent;
	Bubble_State throwingBubbleState;
  Game_Event event;
  Game_State currentState;
}State_Machine;

/**
 * @brief Initializes state machine
 *
 * @return pointer to the struct State_Machine
 */

State_Machine * startStateMachine();

/**
 * @brief If there isn't a state machine creates one, else returns the existing one
 *
 * @return pointer to the struct State_Machine
 */

State_Machine * getStateMachine();

/**
 * @brief Checks in which state the throwing bubble is at
 */
void check_throwing_bubble_state();
/**
 * @brief Checks in which state the game is at
 */
void check_game_state();


/** @} end of gamestates */
#endif /* GAMESTATES_H */
