#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <sys/mman.h>
#include <sys/types.h>
#include "vbe.h"
#include "keyboard.h"
#include "read_xpm.h"
#include <math.h>
#include "read_xpm.h"

/* Constants for VBE 0x105 mode */

/* The physical address may vary from VM to VM.
 * At one time it was 0xD0000000
 *  #define VRAM_PHYS_ADDR    0xD0000000
 * Currently on lab B107 is 0xF0000000
 * Better run my version of lab5 as follows:
 *     service run `pwd`/lab5 -args "mode 0x105"
 */
#define VRAM_PHYS_ADDR	0xF0000000
#define H_RES             1024
#define V_RES		          768
#define BITS_PER_PIXEL	  8

/* Private global variables */

static char *video_mem;		/* Process (virtual) address to which VRAM is mapped */

static unsigned h_res;		/* Horizontal screen resolution in pixels */
static unsigned v_res;		/* Vertical screen resolution in pixels */
static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */

int vg_exit() {
  struct reg86u reg86;

  reg86.u.b.intno = 0x10; /* BIOS video services */

  reg86.u.b.ah = 0x00;    /* Set Video Mode function */
  reg86.u.b.al = 0x03;    /* 80x25 text mode*/

  if( sys_int86(&reg86) != OK ) {
      printf("\tvg_exit(): sys_int86() failed \n");
      return 1;
  } else
      return 0;
}



void *vg_init(unsigned short mode){
  struct reg86u r;
  vbe_mode_info_t vbe_mode_info;

  unsigned int vram_base;  /* VRAM's physical addresss */
  unsigned int vram_size;  /* VRAM's size, but you can use
                              the frame-buffer size, instead */

  r.u.w.ax = 0x4F02; // VBE call, function 02 -- set VBE mode
  r.u.w.bx = 1<<14|mode; // set bit 14: linear framebuffer
  r.u.b.intno = 0x10;
  if( sys_int86(&r) != OK ) {
  printf("set_vbe_mode: sys_int86() failed \n");
  return  NULL;
  }

  if(vbe_get_mode_info(mode, &vbe_mode_info) == 1)
  {
      printf("Error in vbe_get_mode_info\n");
      return NULL;
  }

    if(vbe_get_mode_info(mode, &vbe_mode_info) == 1)
      {
          printf("Error in vbe_get_mode_info\n");
          return NULL;
     }

  h_res = vbe_mode_info.XResolution;
  v_res = vbe_mode_info.YResolution;
  bits_per_pixel = vbe_mode_info.BitsPerPixel;

  vram_base = vbe_mode_info.PhysBasePtr;
  vram_size = v_res * h_res * ceil(bits_per_pixel/8); // If the division of the number of bits by 8 isn't an int, it rounds up to the next int


  int r2;
  struct mem_range mr;

  /* Allow memory mapping */

  mr.mr_base = (phys_bytes) vram_base;
  mr.mr_limit = mr.mr_base + vram_size;

  if( OK != (r2 = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
     panic("sys_privctl (ADD_MEM) failed: %d\n", r2);

  /* Map memory */

  video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);

  if(video_mem == MAP_FAILED)
     panic("couldn't map video memory");


return (void *)video_mem;
}


void set_pixel( short x,  short y, unsigned long color){
  char *ptr = video_mem;

  ptr  += x + h_res * y * (bits_per_pixel/8);

  if( (x < h_res) && (y < v_res)) {
      *ptr = color;

    }
}


int vg_draw_square(short x, short y, unsigned short size, unsigned long color){

  int i, j;

  for( i = 0; i < size; i++){
    for(j = 0; j < size; j++)
    {
      set_pixel(x + j, y + i, color);
    }
  }
  return 0;
}


int vg_draw_line(unsigned short xi, unsigned short yi,unsigned short xf, unsigned short yf, unsigned long color){
//baseado neste método:
//https://www.tutorialspoint.com/computer_graphics/line_generation_algorithm.htm

  float x;
  float y;
  int dx, dy;
  float xinc, yinc;
  int steps;

  dx = xf - xi;
  dy = yf - yi;

   if (abs(dx) > abs(dy))
    steps = abs(dx);
   else
    steps = abs(dy);

   xinc = dx / (float) steps;
   yinc = dy / (float) steps;

   x = xi;
   y = yi;

   int j;
   for(j=0; j < steps; j++)
   {
     x = x + xinc;
     y = y + yinc;


    if(x<h_res && y < v_res){
       set_pixel(x, y, color);
     }
   }

  return 0;
}



int vg_xpm(char *xpm[], unsigned short xi, unsigned short yi){

  int wd,ht; //names given by the read_xpm function
  unsigned int i, j;
  char *pix = read_xpm(xpm, &wd, &ht); //converts an xpm into a pixmap
  unsigned long color;
  int pixIndex=0;


  for(i = 0; i < ht; i++){

    for(j = 0; j < wd; j++){
          color = pix[pixIndex];
          set_pixel(j+ xi, i + yi, color);
          pixIndex++;
    }
  }
  return 0;
}
