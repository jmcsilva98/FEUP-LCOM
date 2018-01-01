#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>

#include "vbe.h"
#include "lmlib.h"

#define LINEAR_MODEL_BIT 14

#define PB2BASE(x) (((x) >> 4) & 0x0F000)
#define PB2OFF(x) ((x) & 0x0FFFF)

int vbe_get_mode_info(unsigned short mode, vbe_mode_info_t *vmi_p) {
  mmap_t buf;
  struct reg86u r;

  if(lm_init() == NULL)
  {
    printf("Error in vbe_get_mode_info : lm_init\n");
    return 1;
  }

  if(lm_alloc(sizeof(vbe_mode_info_t), &buf) == NULL){
    printf("Error in vbe_get_mode_info : lm_alloc\n");
    return 1;

  }

  r.u.w.ax = 0x4F01; /* VBE get mode info */
  /* translate the buffer linear address to a far pointer */
  r.u.w.es = PB2BASE(buf.phys); /* set a segment base */
  r.u.w.di = PB2OFF(buf.phys); /* set the offset accordingly */
  r.u.w.cx = mode;
  r.u.b.intno = 0x10;
  if( sys_int86(&r) != OK ) {
     /* call BIOS */
     printf("Error in vbe_get_mode_info : sys_int86\n");
     lm_free(&buf);
     return 1;
  }

*vmi_p = *((vbe_mode_info_t*)buf.virtual);
//memcpy(vmi_p, buf.virtual, buf.size);


  lm_free(&buf);

 return 0;
  }
