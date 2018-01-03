#include "matrix.h"
#include "gamestates.h"

void allocateInitialMatrix(Game *ColourPop){

  unsigned int c_column = 0;
  unsigned int c_row = 0;

  for(c_column = 0; c_column < 50; c_column++){
    if(c_column < N_ROWS_I)
      allocateRow(ColourPop,c_column);
    else{
      for(c_row = 0; c_row<MAX_BUBBLES_LINE; c_row++){
          m[c_column][c_row] = NULL;
      }
    }
  }

  initializeBubblesToExplode();

  }


void allocateRow(Game *ColourPop, unsigned int c_column){

  unsigned c_row = 0;
  unsigned int xi = LEFT_X_EDGE ;
  unsigned int yi = UPPER_Y_EDGE + c_column * BUBBLE_HIGHT;
  int odd = 0;

  if(c_column % 2 == 0){
    odd = 1;
  }
  else {
    odd = 0;
    xi += BUBBLE_WIDTH/2;
  }

  for(c_row = 0; c_row<MAX_BUBBLES_LINE; c_row++){

    if(!odd && c_row == 10){
      m[c_column][c_row] = NULL;
    }else{
      m[c_column][c_row] = generateBubble(xi, yi);
      xi += BUBBLE_WIDTH;
    }
  }
  ColourPop->rows++;
}


void addRow(Game *ColourPop){
  Bubble * temp1[MAX_BUBBLES_LINE];
  Bubble * temp2[MAX_BUBBLES_LINE];
  unsigned int i_row;
  unsigned int i_column;
  unsigned int xi = LEFT_X_EDGE;
  int odd;
  unsigned int i;

  for ( i = 0; i < MAX_BUBBLES_LINE; i++) {
    if(m[0][i]==NULL)
      continue;
    else{
      if((m[0][i]->leftLimit-LEFT_X_EDGE) % BUBBLE_WIDTH == 0){
        odd = 0;
        xi += BUBBLE_WIDTH/2;
      }else odd = 1;
      break;
    }
  }


    for(i_row = 0; i_row<MAX_BUBBLES_LINE; i_row++){
      if(i_row==10 && !odd){
        temp2[i_row]=NULL;
      }else{
        temp2[i_row] = generateBubble(xi, UPPER_Y_EDGE);
        xi += BUBBLE_WIDTH;
      }
    }

    for (i_column = 0; i_column <= ColourPop->rows; i_column++) {

      if(i_column == ColourPop->rows){
        for(i_row = 0; i_row<MAX_BUBBLES_LINE; i_row++){
            m[ColourPop->rows][i_row] = temp2[i_row];
          }

        }else{

          for(i_row = 0; i_row<MAX_BUBBLES_LINE; i_row++){

            if(m[i_column][i_row]!=NULL){

              m[i_column][i_row]->upperLimit+=BUBBLE_WIDTH;
              temp1[i_row] = m[i_column][i_row];
              m[i_column][i_row] = temp2[i_row];
              temp2[i_row] = temp1[i_row];

            }else{
              temp1[i_row] = m[i_column][i_row];
              m[i_column][i_row] = temp2[i_row];
              temp2[i_row] = temp1[i_row];
            }
          }
        }
      }

    ColourPop->rows++;

}


int checkIfRowAdded(Game * ColourPop){
  unsigned int i;

  for (i = 0; i < MAX_BUBBLES_LINE; i++) {
    if(m[ColourPop->rows][i] != NULL)
    return 1;
  }

  return 0;
}


void checkIfRowDeleted(Game * ColourPop){
  unsigned int i;
  unsigned int j;
  unsigned int empty = 1;
  unsigned int n = 0;

  for(j = ColourPop->rows-1; j>0; j--){
    for (i = 0; i < MAX_BUBBLES_LINE; i++) {
      if(m[j][i] != NULL){
        empty = 0;
      }
    }

    if(empty) n++;
    empty = 1;
  }

  ColourPop->rows -= n;
}


void snapIntoGrid(Game * ColourPop, Bubble * throwing_bubble, Bubble * b_colision){

  int centerXb1 = throwing_bubble->leftLimit + 43/2;
  int side = 0; //1 = right, -1 = left
  unsigned int i;
  unsigned int j;



  if(b_colision ==  NULL){
    throwing_bubble->upperLimit = UPPER_Y_EDGE+1;
    i = (throwing_bubble->leftLimit-LEFT_X_EDGE)/BUBBLE_WIDTH;
    j = (throwing_bubble->upperLimit-UPPER_Y_EDGE)/BUBBLE_WIDTH;
    if(m[j][i]!=NULL) m[j][i] = throwing_bubble;
    else m[j][i+1] = throwing_bubble;

    if(checkIfRowAdded(ColourPop))
      ColourPop->rows++;

    addToBubblesToExplode(ColourPop->throwingBubble);


    unsigned int k = 0;
    for(;k<50; k++ ){
  	  if(bubblesToExplode[k] != NULL){
  		  i = (bubblesToExplode[k]->leftLimit-LEFT_X_EDGE)/BUBBLE_WIDTH;
  		  j = (bubblesToExplode[k]->upperLimit-UPPER_Y_EDGE)/BUBBLE_WIDTH;
  		  checkNeighbours(ColourPop,bubblesToExplode[k], j, i);
  	  }
    }
    return;
  }


    j = (b_colision->upperLimit-UPPER_Y_EDGE)/BUBBLE_WIDTH; //assuming the bubble will be placed in the same level


    //verifie which direction the bubble is moving to: right or left
    if(abs(centerXb1 - b_colision->leftLimit) < abs(centerXb1 - (b_colision->leftLimit + BUBBLE_WIDTH))){
    side = -1;
    i = (b_colision->leftLimit-BUBBLE_WIDTH-LEFT_X_EDGE)/BUBBLE_WIDTH; //row index assuming the bubble will be placed in the same level
  }
    else{
    side = 1;
    i = (b_colision->leftLimit+BUBBLE_WIDTH-LEFT_X_EDGE)/BUBBLE_WIDTH; //row index assuming the bubble will be placed in the same level
  }


    if(side == 1){

    if(b_colision->leftLimit - BUBBLE_WIDTH > LEFT_X_EDGE && b_colision->leftLimit+BUBBLE_WIDTH*2<=RIGHT_X_EDGE && m[j][i]==NULL){ //place in same level if place is available and valid
    	throwing_bubble->leftLimit = b_colision->leftLimit + BUBBLE_WIDTH;
      throwing_bubble->upperLimit = b_colision->upperLimit;

    }else if(b_colision->leftLimit+BUBBLE_WIDTH > RIGHT_X_EDGE) {
      throwing_bubble->leftLimit = b_colision->leftLimit - BUBBLE_WIDTH/2;
      throwing_bubble->upperLimit = b_colision->upperLimit + BUBBLE_WIDTH;

    }/*else if(b_colision->leftLimit<=LEFT_X_EDGE){
      throwing_bubble->leftLimit = b_colision->leftLimit + BUBBLE_WIDTH/2;
      throwing_bubble->upperLimit = b_colision->upperLimit + BUBBLE_WIDTH;
    }*/

    else{ //place lower right
      throwing_bubble->leftLimit = b_colision->leftLimit + BUBBLE_WIDTH/2;
      throwing_bubble->upperLimit = b_colision->upperLimit + BUBBLE_WIDTH;
    }
  }

    else {
    if(b_colision->leftLimit - BUBBLE_WIDTH > LEFT_X_EDGE && b_colision->leftLimit+BUBBLE_WIDTH*2<=RIGHT_X_EDGE && m[j][i]==NULL){  //place in same level if place is available and valid
    	throwing_bubble->leftLimit = b_colision->leftLimit - BUBBLE_WIDTH;
      throwing_bubble->upperLimit = b_colision->upperLimit;

    }else if(b_colision->leftLimit<=LEFT_X_EDGE){
      throwing_bubble->leftLimit = b_colision->leftLimit + BUBBLE_WIDTH/2;
      throwing_bubble->upperLimit = b_colision->upperLimit + BUBBLE_WIDTH;


    }/*else if(b_colision->leftLimit+BUBBLE_WIDTH > RIGHT_X_EDGE) {
    	throwing_bubble->leftLimit = b_colision->leftLimit - BUBBLE_WIDTH/2;
      throwing_bubble->upperLimit = b_colision->upperLimit + BUBBLE_WIDTH;
    }*/

    else{     ////place lower left
      throwing_bubble->leftLimit = b_colision->leftLimit - BUBBLE_WIDTH/2;
      throwing_bubble->upperLimit = b_colision->upperLimit + BUBBLE_WIDTH;
    }
  }


    i = (throwing_bubble->leftLimit-LEFT_X_EDGE)/BUBBLE_WIDTH;
    j = (throwing_bubble->upperLimit-UPPER_Y_EDGE)/BUBBLE_WIDTH;
    m[j][i] = throwing_bubble;
    if(checkIfRowAdded(ColourPop))
    ColourPop->rows++;

    addToBubblesToExplode(ColourPop->throwingBubble);


    unsigned int k = 0;
    for(;k<50; k++ ){
	  if(bubblesToExplode[k] != NULL){
		  i = (bubblesToExplode[k]->leftLimit-LEFT_X_EDGE)/BUBBLE_WIDTH;
		  j = (bubblesToExplode[k]->upperLimit-UPPER_Y_EDGE)/BUBBLE_WIDTH;
		  checkNeighbours(ColourPop,bubblesToExplode[k], j, i);
	  }
  }
}


void initializeBubblesToExplode(){
  unsigned int i = 0;

  for (i = 0; i < 50; i++) {
    bubblesToExplode[i] = NULL;
  }
}


void addToBubblesToExplode(Bubble * b){
	unsigned int i = 0;

	if(findInBubblesToEXplode(b))return;

  for ( i = 0; i < 50; i++) {

    if(bubblesToExplode[i]==NULL ){
      bubblesToExplode[i] = b;
      return;
    }
  }

}


int findInBubblesToEXplode(Bubble * b){
	unsigned int i = 0;

		for ( i = 0; i < 50; i++) {

		   if(bubblesToExplode[i]==b ){
		     return 1;
		    }
		}
		return 0;
}


void explodeBubbles(Game *ColourPop){

  unsigned int size = 0;
  unsigned int i;
  unsigned int i_temp;
  unsigned int j_temp;
  int deleted = 0;

  for (i = 0; i < 50; i++) {
    if(bubblesToExplode[i]!= NULL){
      size++;
    }
  }


  if(size >= 3){
    for ( i = 0; i < 50; i++) {
      if(bubblesToExplode[i] != NULL){
        i_temp = (bubblesToExplode[i]->upperLimit-UPPER_Y_EDGE)/BUBBLE_WIDTH;
        j_temp = (bubblesToExplode[i]->leftLimit-LEFT_X_EDGE)/BUBBLE_WIDTH;
        if(explodeBubble(bubblesToExplode[i])){
          getStateMachine()->throwingBubbleEvent = CHANGE;
          ColourPop->score++;
          m[i_temp][j_temp] = NULL;
          checkIfRowDeleted(ColourPop);
          deleted = 1;
        }
      }
    }
  }else {getStateMachine()->throwingBubbleEvent = CHANGE;initializeBubblesToExplode();}

  if(deleted) {initializeBubblesToExplode();}

}


void checkNeighbours(Game *ColourPop, Bubble * b, unsigned int i, unsigned int j){

  unsigned int xoffset = 0;

  if((b->leftLimit-LEFT_X_EDGE)%BUBBLE_WIDTH != 0) xoffset = 1;

  if(i>0){
    if(j>0 && j <10){

      if(m[i][j-1]!=NULL && m[i][j-1]->type == b->type)
    	  addToBubblesToExplode(m[i][j-1]);

      if(m[i][j+1]!= NULL && m[i][j+1]->type == b->type)
    	  addToBubblesToExplode(m[i][j+1]); //add to array*/


      if(xoffset){
        if(m[i-1][j]!= NULL && m[i-1][j]->type == b->type) addToBubblesToExplode(m[i-1][j]);// add to array
        if(m[i-1][j+1]!= NULL && m[i-1][j+1]->type == b->type) addToBubblesToExplode(m[i-1][j+1]); //add to array
        if(m[i+1][j]!= NULL && m[i+1][j]->type == b->type) addToBubblesToExplode(m[i+1][j]);// add to array
        if(m[i+1][j+1]!= NULL && m[i+1][j+1]->type == b->type) addToBubblesToExplode(m[i+1][j+1]); //add to array
      }else{
        if(m[i-1][j-1]!= NULL && m[i-1][j-1]->type == b->type) addToBubblesToExplode(m[i-1][j-1]); // add to array
        if(m[i-1][j]!= NULL && m[i-1][j]->type == b->type) addToBubblesToExplode(m[i-1][j]); //add to array
        if(m[i+1][j-1]!= NULL && m[i+1][j-1]->type == b->type) addToBubblesToExplode(m[i+1][j-1]); // add to array
        if(m[i+1][j]!= NULL && m[i+1][j]->type == b->type) addToBubblesToExplode(m[i+1][j]); //add to array
      }


    }else if(j==0){
      if(m[i][j+1]!= NULL && m[i][j+1]->type == b->type) addToBubblesToExplode(m[i][j+1]); //add to array

      if(xoffset){
        if(m[i-1][j]!= NULL && m[i-1][j]->type == b->type) addToBubblesToExplode(m[i-1][j]); // add to array
        if(m[i-1][j+1]!= NULL && m[i-1][j+1]->type == b->type) addToBubblesToExplode(m[i-1][j+1]); //add to array
        if(m[i+1][j]!= NULL && m[i+1][j]->type == b->type) addToBubblesToExplode(m[i+1][j]);// add to array
        if(m[i+1][j+1]!= NULL && m[i+1][j+1]->type == b->type) addToBubblesToExplode(m[i+1][j+1]); //add to array
      }else{
        if(m[i-1][j]!= NULL && m[i-1][j]->type == b->type) addToBubblesToExplode(m[i-1][j]); //add to array
        if(m[i+1][j]!= NULL && m[i+1][j]->type == b->type) addToBubblesToExplode(m[i+1][j]); //add to array
      }

    }else if(j==10){
      if(m[i][j+1]!= NULL && m[i][j+1]->type == b->type) addToBubblesToExplode(m[i][j+1]);//add to array

      if(xoffset){
        if(m[i-1][j]!= NULL && m[i-1][j]->type == b->type) addToBubblesToExplode(m[i-1][j-1]); // add to array
        if(m[i-1][j+1]!= NULL && m[i-1][j+1]->type == b->type) addToBubblesToExplode(m[i-1][j-1]);//add to array
        if(m[i+1][j]!= NULL && m[i+1][j]->type == b->type) addToBubblesToExplode(m[i+1][j]);// add to array
        if(m[i+1][j+1]!= NULL && m[i+1][j+1]->type == b->type) addToBubblesToExplode(m[i+1][j+1]); //add to array
      }else{
        if(m[i-1][j-1]!= NULL && m[i-1][j-1]->type == b->type) addToBubblesToExplode(m[i-1][j-1]);//add to array
        if(m[i+1][j-1]!= NULL && m[i+1][j-1]->type == b->type) addToBubblesToExplode(m[i+1][j-1]); // add to array
      }
    }

  }else{
    if(j>0 && j <10){
      if(m[i][j-1]!= NULL && m[i][j-1]->type == b->type) addToBubblesToExplode(m[i][j-1]); //add to array
      if(m[i][j+1]!= NULL && m[i][j+1]->type == b->type) addToBubblesToExplode(m[i][j+1]);//add to array

    }else if(j==0){
      if(m[i][j+1]!= NULL && m[i][j+1]->type == b->type) addToBubblesToExplode(m[i][j+1]);//add to array

    }else if(j==10){
      if(m[i][j+1]!= NULL && m[i][j+1]->type == b->type) addToBubblesToExplode(m[i][j+1]);//add to array

    }
  }



}


void checkFloatingBubbles(){
  unsigned int i, j;
  unsigned int xoffset = 0;

  for (i = 0; i <= 12; i++) {
    for (j = 0; j < MAX_BUBBLES_LINE; j++) {

      if(m[i][j]!= NULL){
        if((m[i][j]->leftLimit-LEFT_X_EDGE)%BUBBLE_WIDTH != 0) xoffset = 1;

        if(xoffset){
          if(j> 0 && j< 10){
            if(m[i][j-1] == NULL && m[i][j+1] == NULL && m[i-1][j] == NULL && m[i-1][j+1] ){
          m[i][j] = NULL;}
        }else if(j == 0){
            if(m[i][j+1] == NULL && m[i-1][j] == NULL && m[i-1][j+1] ){
              free(m[i][j]);
              m[i][j] = NULL;
            }
        }else if(j==10){
          if(m[i][j-1] == NULL && m[i-1][j] == NULL && m[i-1][j+1] ){
            free(m[i][j]);
            m[i][j] = NULL;
          }
        }
        }else{
          if(j> 0 && j< 11 && m[i][j-1] == NULL && m[i][j+1] == NULL && m[i-1][j-1] == NULL && m[i-1][j]){
          free(m[i][j]);
          m[i][j] = NULL;}
        }
      }
    }
  }
}




void freeMatrix(Game * ColourPop){
  unsigned int i = 0;
  unsigned int j = 0;

  for (; i < 50; i++) {
    for (; j < MAX_BUBBLES_LINE; j++) {
      if(m[i][j] != NULL){
        deleteBubble(m[i][j]);
        m[i][j] = NULL;
      }
    }
  }
}
