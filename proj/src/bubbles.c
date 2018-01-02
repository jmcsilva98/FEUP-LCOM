#include "bubbles.h"
#include "math.h"
#include<stdio.h>
#include<math.h>
#include "gamestates.h"
#include "i8042.h"

#define PI 3.14159265359



void drawBubble(Bubble * b){
  drawBitmap(b->image, b->leftLimit, b->upperLimit, ALIGN_LEFT);
}


Bubble * generateBubble(unsigned int xi, unsigned int yi){

  Bubble * b = (Bubble*) malloc(sizeof(Bubble));

  b->upperLimit = yi;
  b->leftLimit = xi;
  b->type = rand()%5;
  b->exploded = 0;

  switch(b->type){
    case 0:
    b->image = loadBitmap("/home/lcom/proj/res/blueball.bmp");
    break;

    case 1:
    b->image = loadBitmap("/home/lcom/proj/res/silverball.bmp");
    break;

    case 2:
    b->image = loadBitmap("/home/lcom/proj/res/pinkball.bmp");
    break;

    case 3:
    b->image = loadBitmap("/home/lcom/proj/res/yellowball.bmp");
    break;

    case 4:
    b->image = loadBitmap("/home/lcom/proj/res/greenball.bmp");
    break;

    default:
    break;
  }
  return b;
}


void deleteBubble(Bubble * b){
  deleteBitmap(b->image);
  free(b);
}


int explodeBubble(Bubble * b){

  if(b->exploded==0){
    b->image = loadBitmap("/home/lcom/proj/res/exploded.bmp");
    b->exploded = 1;
    return 0;

  }else{
    b->exploded = -1;
    deleteBubble(b);
    return 1;
  }
}


void turnBlack(Bubble * b){
  b->image = loadBitmap("/home/lcom/proj/res/blackball.bmp");
  b->type = 5;
}


void throwBubble_line(Bubble * b, int angle, unsigned int ymin){
  int xmax = RIGHT_X_EDGE-49;
  int xmin = LEFT_X_EDGE;
  int ang = angle * 6;

  int xspeed = 30 * cos((90-ang)*PI/180);
  int yspeed = 30 * sin((90-ang)*PI/180);

  b->upperLimit -= (int) yspeed;

  if(b->upperLimit < ymin){
    b->upperLimit = ymin;
    return;
  }


  b->leftLimit += (int) xspeed;

  if(b->leftLimit > xmax){
      b->leftLimit = xmax;
      return ;
    }

  if(b->leftLimit < xmin){
      b->leftLimit = xmin;
      return ;
  }
}


int checkColision(Bubble * b1, Bubble * b2){
  int x1, x2, y1, y2, dx, dy, h;
  // Calculate the distance between the centers
  x1 = b1->leftLimit + 43/2;
  x2 = b2->leftLimit + 43/2;
  y1 = b1->upperLimit + 43/2;
  y2 = b2->upperLimit + 43/2;
  dx = x1 - x2;
  dy = y1 - y2;
  h = sqrt(dx * dx + dy * dy);

  if (h < 44) {
    return 1;
  }else return 0;
}
