
#ifndef _SPRITE_H_
#define _SPRITE_H_

typedef struct {
int x, y; // current position
int width, height; // dimensions
int xspeed, yspeed; // current speed
char *map; // the pixmap
} Sprite;




Sprite *create_sprite(char *pic[], int x, int y,int xspeed, int yspeed);
void destroy_sprite(Sprite *sp);
void remove_sprite(Sprite *sp);
void animate_sprite(Sprite *sp);






#endif
