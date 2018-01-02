#include "bitmap.h"
#include "video_gr.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "video_gr.h"
#include "timer.h"
#include "keyboard.h"
#include "gamestates.h"
#include "i8042.h"
#include "math.h"
#include "matrix.h"
#include "graphics.h"

Spear *spear = NULL;
Bar * limitBar = NULL;

//SPEAR FUNCTIONS
Spear * newSpear(){

  Spear * spear = (Spear*) malloc (sizeof(Spear));
	spear->angle = 0;
  spear->s0 = loadBitmap("/home/lcom/proj/res/spear0.bmp");
  spear->s1 = loadBitmap("/home/lcom/proj/res/spear1.bmp");
  spear->s2 = loadBitmap("/home/lcom/proj/res/spear2.bmp");
  spear->s3 = loadBitmap("/home/lcom/proj/res/spear3.bmp");
  spear->s4 = loadBitmap("/home/lcom/proj/res/spear4.bmp");
  spear->s5 = loadBitmap("/home/lcom/proj/res/spear5.bmp");
  spear->s6 = loadBitmap("/home/lcom/proj/res/spear6.bmp");
  spear->s7 = loadBitmap("/home/lcom/proj/res/spear7.bmp");
  spear->s8 = loadBitmap("/home/lcom/proj/res/spear8.bmp");
  spear->s9 = loadBitmap("/home/lcom/proj/res/spear9.bmp");
  spear->sm1 = loadBitmap("/home/lcom/proj/res/spear-1.bmp");
  spear->sm2 = loadBitmap("/home/lcom/proj/res/spear-2.bmp");
  spear->sm3 = loadBitmap("/home/lcom/proj/res/spear-3.bmp");
  spear->sm4 = loadBitmap("/home/lcom/proj/res/spear-4.bmp");
  spear->sm5 = loadBitmap("/home/lcom/proj/res/spear-5.bmp");
  spear->sm6 = loadBitmap("/home/lcom/proj/res/spear-6.bmp");
  spear->sm7 = loadBitmap("/home/lcom/proj/res/spear-7.bmp");
  spear->sm8 = loadBitmap("/home/lcom/proj/res/spear-8.bmp");
  spear->sm9 = loadBitmap("/home/lcom/proj/res/spear-9.bmp");

  spear->reverse_change = 0;

	return spear;
}


Spear * getSpear(){

  if(!spear){
	   spear = newSpear();
  }

  return spear;
}


void updateSpear(Game * ColourPop){

  if(getStateMachine()->event ==  MOVE_SPEAR_RIGHT){
    if(getSpear()->angle==9) return;
      else getSpear()->angle++;
  }else if(getStateMachine()->event ==  MOVE_SPEAR_LEFT){
    if(getSpear()->angle==-9) return;
    else getSpear()->angle--;
  }


    switch (getSpear()->angle) {
      case 0:
      ColourPop->spear =  getSpear()->s0;
      break;
      case 1:
      ColourPop->spear =  getSpear()->s1;
      break;
      case 2:
      ColourPop->spear =  getSpear()->s2;
      break;
      case 3:
      ColourPop->spear =  getSpear()->s3;
      break;
      case 4:
      ColourPop->spear =  getSpear()->s4;
      break;
      case 5:
      ColourPop->spear =  getSpear()->s5;
      break;
      case 6:
      ColourPop->spear =  getSpear()->s6;
      break;
      case 7:
      ColourPop->spear =  getSpear()->s7;
      break;
      case 8:
      ColourPop->spear =  getSpear()->s8;
      break;
      case 9:
      ColourPop->spear =  getSpear()->s9;
      break;
      case -1:
      ColourPop->spear =  getSpear()->sm1;
      break;
      case -2:
      ColourPop->spear =  getSpear()->sm2;
      break;
      case -3:
      ColourPop->spear =  getSpear()->sm3;
      break;
      case -4:
      ColourPop->spear =  getSpear()->sm4;
      break;
      case -5:
      ColourPop->spear =  getSpear()->sm5;
      break;
      case -6:
      ColourPop->spear =  getSpear()->sm6;
      break;
      case -7:
      ColourPop->spear =  getSpear()->sm7;
      break;
      case -8:
      ColourPop->spear =  getSpear()->sm8;
      break;
      case -9:
      ColourPop->spear =  getSpear()->sm9;
      break;
    }
}


void deleteSpear(){
  free(getSpear());
}



//LIMIT BAR
Bar * newBar(){
  Bar * limitBar = (Bar*) malloc (sizeof(Bar));
  limitBar->xi =  264;
  limitBar->yi = 559;
  limitBar->bitmap =loadBitmap("/home/lcom/proj/res/bar.bmp");
  return limitBar;
}


Bar * getBar(){
  if(!limitBar)
    limitBar = newBar();
  return limitBar;
}


void deleteBar(){
  free(getBar());
}


//MATRIX FUNCTIONS
void drawMatrix(Game *ColourPop){
  unsigned int c_column= 0;

  for (; c_column < 50; c_column++) {
    drawRow(ColourPop,c_column);
  }
}


void drawRow(Game *ColourPop, unsigned int c_column){

  unsigned c_row = 0;

  for(c_row = 0; c_row<MAX_BUBBLES_LINE; c_row++){
    if(m[c_column][c_row]!= NULL)
      drawBubble(m[c_column][c_row]);
  }
}

void throwingDirection(Game * ColourPop, Bubble * b){
  int xmax = RIGHT_X_EDGE - 49;
  int xmin = LEFT_X_EDGE;
  int ymin = UPPER_Y_EDGE;
  int angle = getSpear()->angle;


  if(angle > 0) getStateMachine()->throwingBubbleEvent = THROW_RIGHT;
  else if(angle < 0) getStateMachine()->throwingBubbleEvent = THROW_LEFT;
  else getStateMachine()->throwingBubbleEvent = THROW;



  if(checkMovement(ColourPop)!=NULL){
    if(getSpear()->reverse_change == 1){
      getSpear()->angle = - getSpear()->angle;
      getSpear()->reverse_change = 0;
    }
    snapIntoGrid(ColourPop, ColourPop->throwingBubble, checkMovement(ColourPop));
    getStateMachine()->throwingBubbleEvent = DONE_THROWING;
    return;
  }

  if(ColourPop->throwingBubble->upperLimit <=UPPER_Y_EDGE){
    snapIntoGrid(ColourPop, ColourPop->throwingBubble, NULL);
    return;
  }

  if(getStateMachine()->throwingBubbleEvent == THROW_RIGHT){
    if(b->leftLimit == xmax){
      angle = -angle;
      getSpear()->reverse_change = 1;
      getStateMachine()->throwingBubbleEvent = THROW_LEFT;
    }else {
      throwBubble_line(b, angle, ymin);
  }}


  if(getStateMachine()->throwingBubbleEvent == THROW_LEFT){
    if(b->leftLimit == xmin){
      angle = -angle;
      getSpear()->reverse_change = 1;
      getStateMachine()->throwingBubbleEvent = THROW_RIGHT;
    }else {
      throwBubble_line(b, angle,  ymin);
    }
  }

  if(getStateMachine()->throwingBubbleEvent == THROW) throwBubble_line(b, angle, ymin);

  getSpear()->angle = angle;
}


Bubble * checkMovement(Game * ColourPop){

  int i  = 0;
  int j;
  for (i = ColourPop->rows-1; i >= 0; i--) {
    for (j = 0; j < MAX_BUBBLES_LINE; j++) {

      if(m[i][j] == NULL){
        continue;
      }


      else{
        if(checkColision(ColourPop->throwingBubble, m[i][j])){
          return m[i][j];

        }
      }
    }
  }
  return NULL;
}

//THROWING BUBBLE


void changeThrowingBubble(Game * ColourPop){
  getStateMachine()->throwingBubbleEvent = CHANGE;
  ColourPop->throwingBubble = ColourPop->nextBubble;
  ColourPop->throwingBubble->upperLimit = 618;
  ColourPop->throwingBubble->leftLimit = 486;
  ColourPop->nextBubble = generateBubble(286,574);
}


void turnBubblesBlack(Game * ColourPop){
  unsigned int i;
  unsigned int j;

  for (i = ColourPop->rows+2; i >= 0; i--) {
    for (j = 0; j < MAX_BUBBLES_LINE; j++) {
      if(m[i][j]!= NULL && m[i][j]->type != BLACK){
      turnBlack(m[i][j]);
      if(j==9 && i == 0) getStateMachine()->event = TURNED_BLACK;
      return;
      }
    }
  }
}


Bitmap * convertDateToBMP(int date_number, Game * ColourPop){

  switch(date_number){
    case 0:
    return ColourPop->n0;
    break;
    case 1:
    return ColourPop->n1;
    break;
    case 2:
    return ColourPop->n2;
    break;
    case 3:
    return ColourPop->n3;
    break;
    case 4:
    return ColourPop->n4;
    break;
    case 5:
    return ColourPop->n5;
    break;
    case 6:
    return ColourPop->n6;
    break;
    case 7:
    return ColourPop->n7;
    break;
    case 8:
    return ColourPop->n8;
    break;
    case 9:
    return ColourPop->n9;
    break;
    default:
    return NULL;
    break;
  }
}

Bitmap * convertCharToBMP(char char_key, Game * ColourPop){

  Bitmap * key;

  switch (char_key) {
    case 'a':
    key = ColourPop->a;
    break;
    case 'b':
    key = ColourPop->b;
    break;
    case 'c':
    key = ColourPop->c;
    break;
    case 'd':
    key = ColourPop->d;
    break;
    case 'e':
    key = ColourPop->e;
    break;
    case 'f':
    key = ColourPop->f;
    break;
    case 'g':
    key = ColourPop->g;
    break;
    case 'h':
    key = ColourPop->h;
    break;
    case 'i':
    key = ColourPop->i;
    break;
    case 'j':
    key = ColourPop->j;
    break;
    case 'k':
    key = ColourPop->k;
    break;
    case 'l':
    key = ColourPop->l;
    break;
    case 'm':
    key = ColourPop->m;
    break;
    case 'n':
    key = ColourPop->n;
    break;
    case 'o':
    key = ColourPop->o;
    break;
    case 'p':
    key = ColourPop->p;
    break;
    case 'q':
    key = ColourPop->q;
    break;
    case 'r':
    key = ColourPop->r;
    break;
    case 's':
    key = ColourPop->s;
    break;
    case 't':
    key = ColourPop->t;
    break;
    case 'u':
    key = ColourPop->u;
    break;
    case 'v':
    key = ColourPop->v;
    break;
    case 'w':
    key = ColourPop->w;
    break;
    case 'x':
    key = ColourPop->x;
    break;
    case 'y':
    key = ColourPop->y;
    break;
    case 'z':
    key = ColourPop->z;
    break;
    default:
    key = NULL;
    break;
  }
  return key;
}

char convertScancodeToChar(unsigned long code){

  char key;

  switch (code) {
    case A_KEY:
    key = 'a';
    break;
    case B_KEY:
    key = 'b';
    break;
    case C_KEY:
    key = 'c';
    break;
    case D_KEY:
    key = 'd';
    break;
    case E_KEY:
    key = 'e';
    break;
    case F_KEY:
    key = 'f';
    break;
    case G_KEY:
    key = 'g';
    break;
    case H_KEY:
    key = 'h';
    break;
    case I_KEY:
    key = 'i';
    break;
    case J_KEY:
    key = 'j';
    break;
    case K_KEY:
    key = 'k';
    break;
    case L_KEY:
    key = 'l';
    break;
    case M_KEY:
    key = 'm';
    break;
    case N_KEY:
    key = 'n';
    break;
    case O_KEY:
    key = 'o';
    break;
    case P_KEY:
    key = 'p';
    break;
    case Q_KEY:
    key = 'q';
    break;
    case R_KEY:
    key = 'r';
    break;
    case S_KEY:
    key = 's';
    break;
    case T_KEY:
    key = 't';
    break;
    case U_KEY:
    key = 'u';
    break;
    case V_KEY:
    key = 'v';
    break;
    case W_KEY:
    key = 'w';
    break;
    case X_KEY:
    key = 'x';
    break;
    case Y_KEY:
    key = 'y';
    break;
    case Z_KEY:
    key = 'z';
    break;
    default:
    key = -1;
    break;
  }
  return key;
}




void enterName(Game * ColourPop){
  unsigned int i;
  unsigned int full = 0;
  Bitmap * letter = convertCharToBMP(convertScancodeToChar(ColourPop->scancode), ColourPop);

  for ( i = 0; i <= 4; i++) {
    if(i==4){
      full = 1;
      break;
    }

    if(ColourPop->name[i] == 0)
    break;
  }

  if(!full){
    if(letter!=NULL){
      ColourPop->name[i] = convertScancodeToChar(ColourPop->scancode);
      ColourPop->scancode = 0;
    }
  }
}


void showName(Game * ColourPop, char * name, unsigned int x, unsigned int y){
  unsigned int i;
  unsigned int size = 0;

  drawBitmap(ColourPop->blueball,0, 0, ALIGN_LEFT);

  for ( i = 0; i < 4; i++) {
    if(convertCharToBMP(name[i], ColourPop)!=NULL)
      size++;
  }

  switch(size){
      case 1:
        drawBitmap(convertCharToBMP(name[size-1], ColourPop),x-12, y, ALIGN_LEFT);
        break;
      case 2:
        drawBitmap(convertCharToBMP(name[size-2], ColourPop),x-24, y, ALIGN_LEFT);
        drawBitmap(convertCharToBMP(name[size-1], ColourPop),x, y, ALIGN_LEFT);
          break;
      case 3:
        drawBitmap(convertCharToBMP(name[size-3], ColourPop),x-24-12, y, ALIGN_LEFT);
        drawBitmap(convertCharToBMP(name[size-2], ColourPop),x-12, y, ALIGN_LEFT);
        drawBitmap(convertCharToBMP(name[size-1], ColourPop), x+12, y, ALIGN_LEFT);
          break;
      case 4:
        drawBitmap(convertCharToBMP(name[size-4], ColourPop),x-24*2, y, ALIGN_LEFT);
        drawBitmap(convertCharToBMP(name[size-3], ColourPop),x-24, y, ALIGN_LEFT);
        drawBitmap(convertCharToBMP(name[size-2], ColourPop),x, y, ALIGN_LEFT);
        drawBitmap(convertCharToBMP(name[size-1], ColourPop),x+24, y, ALIGN_LEFT);
        break;
    }
}


void ShowNumber(Game * ColourPop, int number, int x, int y){
  Bitmap * n1;
  Bitmap * n2;

  if(number < 10) {
    n1 = ColourPop->n0;
    n2 = convertDateToBMP(number, ColourPop);
  }
  else{
    n1 =  convertDateToBMP(number/10, ColourPop);
    n2 = convertDateToBMP(number % 10, ColourPop);
  }

  drawBitmap(n1, x, y, ALIGN_LEFT);
  drawBitmap(n2, x+20, y, ALIGN_LEFT);
}


void showDate(Game * ColourPop, Date * date, unsigned int xi, unsigned int yi){

  ShowNumber(ColourPop, date->dayOfMonth, xi, yi);
  xi+=40;
  drawBitmap(ColourPop->dash, xi, yi, ALIGN_LEFT);
  xi+=20;
  ShowNumber(ColourPop, date->month, xi, yi);
  xi+=40;
  drawBitmap(ColourPop->dash, xi, yi, ALIGN_LEFT);
  xi+=20;
  ShowNumber(ColourPop, date->year, xi, yi);

}


void showTime(Game * ColourPop, Date * date, unsigned int xi, unsigned int yi){


  ShowNumber(ColourPop, ColourPop->date->hours, xi, yi);
  xi+=40;
  drawBitmap(ColourPop->colon, xi, yi, ALIGN_LEFT);
  xi+=20;
  ShowNumber(ColourPop, ColourPop->date->minutes, xi, yi);
  xi+=40;
  drawBitmap(ColourPop->colon, xi, yi, ALIGN_LEFT);
  xi+=20;
  ShowNumber(ColourPop, ColourPop->date->seconds, xi, yi);

}



//GENERAL GRAPHICS

void drawGame(Game * ColourPop){

  drawBackGround(ColourPop->playingBackground, 0, 0, ALIGN_LEFT);
  drawBitmap(getBar()->bitmap, getBar()->xi, getBar()->yi, ALIGN_LEFT);
  drawMatrix(ColourPop);
  drawBitmap(ColourPop->spear, 433, 552, ALIGN_LEFT);
  drawBitmap(ColourPop->nextBubble->image, ColourPop->nextBubble->leftLimit, ColourPop->nextBubble->upperLimit,ALIGN_LEFT);
  drawBitmap(ColourPop->tunel, 280, 596, ALIGN_LEFT);
  drawBitmap(ColourPop->throwingBubble->image, ColourPop->throwingBubble->leftLimit, ColourPop->throwingBubble->upperLimit,ALIGN_LEFT);
  showDate(ColourPop, ColourPop->date, 20, 30);
  showTime(ColourPop, ColourPop->date, 20, 50);
  drawBitmap(ColourPop->score_bitmap, 908, 30, ALIGN_LEFT);
  drawScore(ColourPop,ColourPop->score, 917, 1009, 50);
}


void drawMenu(Game * ColourPop){
  drawBackGround(ColourPop->menu, 0, 0, ALIGN_LEFT);
  drawMouse(ColourPop);
}


void drawGameOverMenu(Game * ColourPop){
  drawBitmap(ColourPop->gameOverMenu, 0, 0, ALIGN_LEFT);
  drawScore(ColourPop,ColourPop->score, 463, 573, 302);
  drawScore(ColourPop,ColourPop->high_score_1->score, 431, 611, 413);
  drawMouse(ColourPop);
}

void drawEnterNameMenu(Game * ColourPop){
  drawBitmap(ColourPop->enterNameMenu, 0, 0, ALIGN_LEFT);
  showName(ColourPop, ColourPop->name, 500, 420);
}


void drawPausedMenu(Game * ColourPop){
  drawBitmap(ColourPop->pausedMenu, 0, 0, ALIGN_LEFT);
  drawMouse(ColourPop);
}

void drawHighscoresMenu(Game * ColourPop){
  drawBitmap(ColourPop->highScoresMenu, 0, 0, ALIGN_LEFT);
  showDate(ColourPop, ColourPop->high_score_1->date, 300, 422);
  showName(ColourPop, ColourPop->high_score_1->name, 565, 420);
  drawScore(ColourPop ,ColourPop->high_score_1->score, 717, -1, 422);
  showDate(ColourPop, ColourPop->high_score_2->date, 300, 482);
  showName(ColourPop, ColourPop->high_score_2->name, 565, 480);
  drawScore(ColourPop,ColourPop->high_score_2->score, 717, -1, 482);
  showDate(ColourPop, ColourPop->high_score_3->date, 300, 542);
  showName(ColourPop, ColourPop->high_score_3->name, 565, 540);
  drawScore(ColourPop,ColourPop->high_score_3->score, 717, -1, 542);
}


void drawScore(Game * ColourPop, unsigned int score, unsigned int xi, int xf,unsigned int yi){
  unsigned int x = (xi + xf)/2;

  if(xf!=-1){
    if(score < 10){
      drawBitmap(convertDateToBMP(score, ColourPop),x-NMBS_WIDTH/2, yi , ALIGN_LEFT );
    }else if((score < 100)){
      drawBitmap(convertDateToBMP(score / 10 , ColourPop), x - NMBS_WIDTH, yi , ALIGN_LEFT );
      drawBitmap(convertDateToBMP(score % 10, ColourPop), x, yi , ALIGN_LEFT );
    }else{
      drawBitmap(convertDateToBMP(score / 100 , ColourPop), x - 3 * NMBS_WIDTH/2, yi , ALIGN_LEFT );
      drawBitmap(convertDateToBMP((score % 100) / 10, ColourPop), x-NMBS_WIDTH/2 , yi , ALIGN_LEFT );
      drawBitmap(convertDateToBMP(score % 10, ColourPop), x + NMBS_WIDTH/2, yi , ALIGN_LEFT );
    }
  }else{
    if(score < 10){
      drawBitmap(convertDateToBMP(score, ColourPop),xi-NMBS_WIDTH, yi , ALIGN_LEFT );
    }else if((score < 100)){
      drawBitmap(convertDateToBMP(score / 10 , ColourPop), xi - NMBS_WIDTH*2, yi , ALIGN_LEFT );
      drawBitmap(convertDateToBMP(score % 10, ColourPop), xi-NMBS_WIDTH, yi , ALIGN_LEFT );
    }else{
      drawBitmap(convertDateToBMP(score / 100 , ColourPop), xi - NMBS_WIDTH*3, yi , ALIGN_LEFT );
      drawBitmap(convertDateToBMP((score % 100) / 10, ColourPop), xi-NMBS_WIDTH*2 , yi , ALIGN_LEFT );
      drawBitmap(convertDateToBMP(score % 10, ColourPop), xi-NMBS_WIDTH, yi , ALIGN_LEFT );
    }
  }
}
