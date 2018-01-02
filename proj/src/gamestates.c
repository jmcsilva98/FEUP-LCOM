#include "gamestates.h"
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/driver.h>

State_Machine * stateMachine = NULL;

State_Machine * startStateMachine(){
  stateMachine = (State_Machine*) malloc(sizeof(State_Machine));
  stateMachine->currentState = MENU;
  stateMachine->event = EMPTY;
  stateMachine->throwingBubbleState = STILL;
  return stateMachine;
}

State_Machine * getStateMachine(){
  if(!stateMachine){
    startStateMachine();
  }
   return stateMachine;
}

void check_throwing_bubble_state(){
  switch (stateMachine->throwingBubbleState) {
    case STILL:
    if(stateMachine->throwingBubbleEvent == THROW){
      stateMachine->throwingBubbleState = THROWING;
    }
    if(stateMachine->throwingBubbleEvent == THROW_RIGHT){
      stateMachine->throwingBubbleState = THROWING;
    }
    if(stateMachine->throwingBubbleEvent == THROW_LEFT){
      stateMachine->throwingBubbleState = THROWING;
    }
    break;
    case THROWING:
    if(stateMachine->throwingBubbleEvent == DONE_THROWING){
      stateMachine->throwingBubbleState = EXPLODING;
    }
    break;

    case EXPLODING:
    if(stateMachine->throwingBubbleEvent == CHANGE){
      stateMachine->throwingBubbleState = CHANGING;
    }

    case ENTER_NAME_MENU:


    default:
    break;
  }
}


void check_game_state(){
  switch (stateMachine->currentState) {
    case MENU:
    if(stateMachine->event == EXIT_BUTTON){
      stateMachine->currentState = DONE;
      stateMachine->event = EMPTY;
    }
    if(stateMachine->event == PLAY_BUTTON){
      stateMachine->currentState = ENTER_NAME_MENU;
      stateMachine->event = EMPTY;
    }

    if(stateMachine->event == HIGHSCORES_BUTTON){
      stateMachine->currentState = HIGHSCORES_MENU;
      stateMachine->event = EMPTY;
    }
    break;
    /////////////////////////////////////
    case ENTER_NAME_MENU:
    if(stateMachine->event == PRESSED_KEY){
      stateMachine->currentState = PLAY_MODE;
      stateMachine->event = EMPTY;
    }

    /////////////////////////////////////
    case HIGHSCORES_MENU:
    if(stateMachine->event == ESCAPE){
      stateMachine->currentState = MENU;
    }
    break;

    /////////////////////////////////////
    case PLAY_MODE:
    if(stateMachine->event == ESCAPE){
      stateMachine->currentState = DONE;
    }

    if(stateMachine->event == LINE_OVER_BAR){
      stateMachine->currentState = FINISHING_UP;
    }

    break;
    case FINISHING_UP:
    if(stateMachine->event == TURNED_BLACK){
      stateMachine->currentState = GAME_OVER;
    }

    /////////////////////////////////////
    case GAME_OVER:
    if(stateMachine->event == PLAY_BUTTON){
      stateMachine->currentState = START_OVER;
    }

    if(stateMachine->event == EXIT_BUTTON){
      stateMachine->currentState = DONE;
    }
    break;



    default:
    break;
  }
}
