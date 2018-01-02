#include <stdio.h>
#include <stdlib.h>

#include "highscores.h"


void writeHighscores(Game * ColourPop){

  FILE * highscores_file;

  highscores_file = fopen("/home/lcom/proj/src/highscores.txt","w");

  fprintf(highscores_file,"%d ", ColourPop->high_score_1->score);
  fprintf(highscores_file,"%d ", ColourPop->high_score_1->date->dayOfMonth);
  fprintf(highscores_file,"%d ", ColourPop->high_score_1->date->month);
  fprintf(highscores_file,"%d ", ColourPop->high_score_1->date->year);
  fprintf(highscores_file, "%s\n",ColourPop->high_score_1->name);

  fprintf(highscores_file,"%d ", ColourPop->high_score_2->score);
  fprintf(highscores_file,"%d ", ColourPop->high_score_2->date->dayOfMonth);
  fprintf(highscores_file,"%d ", ColourPop->high_score_2->date->month);
  fprintf(highscores_file,"%d ", ColourPop->high_score_2->date->year);
  fprintf(highscores_file, "%s\n",ColourPop->high_score_2->name);

  fprintf(highscores_file,"%d ", ColourPop->high_score_3->score);
  fprintf(highscores_file,"%d ", ColourPop->high_score_3->date->dayOfMonth);
  fprintf(highscores_file,"%d ", ColourPop->high_score_3->date->month);
  fprintf(highscores_file,"%d ", ColourPop->high_score_3->date->year);
  fprintf(highscores_file, "%s",ColourPop->high_score_3->name);

  fclose(highscores_file);
}

void readHighscores(Game * ColourPop){
  FILE * highscores_file;
  char space;

  highscores_file = fopen("/home/lcom/proj/src/highscores.txt","r");
  fscanf(highscores_file, "%d", &ColourPop->high_score_1->score);
  fscanf(highscores_file, "%d", &ColourPop->high_score_1->date->dayOfMonth);
  fscanf(highscores_file, "%d", &ColourPop->high_score_1->date->month);
  fscanf(highscores_file, "%d", &ColourPop->high_score_1->date->year);
  fscanf(highscores_file, "%c", &space);
  fgets(ColourPop->high_score_1->name, 5, highscores_file);

  fscanf(highscores_file, "%d", &ColourPop->high_score_2->score);
  fscanf(highscores_file, "%d", &ColourPop->high_score_2->date->dayOfMonth);
  fscanf(highscores_file, "%d", &ColourPop->high_score_2->date->month);
  fscanf(highscores_file, "%d", &ColourPop->high_score_2->date->year);
  fscanf(highscores_file, "%c", &space);
  fgets(ColourPop->high_score_2->name, 5, highscores_file);

  fscanf(highscores_file, "%d", &ColourPop->high_score_3->score);
  fscanf(highscores_file, "%d", &ColourPop->high_score_3->date->dayOfMonth);
  fscanf(highscores_file, "%d", &ColourPop->high_score_3->date->month);
  fscanf(highscores_file, "%d", &ColourPop->high_score_3->date->year);
  fscanf(highscores_file, "%c", &space);
  fgets(ColourPop->high_score_3->name, 5, highscores_file);
  fclose(highscores_file);
}
