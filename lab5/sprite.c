#include "sprite.h"
#include "read_xpm.h"
#include "video_gr.h"
#include <minix/drivers.h>

#define BCK_COLOUR       0x0



/** Creates a new sprite with pixmap "pic", with specified
* position (within the screen limits) and speed;
* Does not draw the sprite on the screen
* Returns NULL on invalid pixmap.
*/

Sprite *create_sprite(char *pic[], int x, int y,int xspeed, int yspeed) {
//allocate space for the "object"
  Sprite *sp = (Sprite *) malloc ( sizeof(Sprite));
if( sp == NULL )
  return NULL;
// read the sprite pixmap
sp->map = read_xpm(pic, &(sp->width), &(sp->height));
if( sp->map == NULL ) {
free(sp);
return NULL;
}

return sp;
}

void destroy_sprite(Sprite *sp) {
  if( sp == NULL )
    return;
if( sp ->map )
    free(sp->map);
    free(sp);
    sp = NULL; // XXX: pointer is passed by value
// should do this @ the caller
}


void animate_sprite(Sprite *sp){

vg_xpm(sp->map, sp->x, sp->y);
video_dump_fb();


}

void remove_sprite(Sprite *sp){

  int wd = sp->width;
  int ht = sp->height;
  unsigned int i, j;



    for(i = 0; i < ht; i++){

      for(j = 0; j < wd; j++){
            set_pixel(j+ sp->x, i + sp->y, BCK_COLOUR); //to obtain better modularity we define a macro for the background colour

      }
    }

}
