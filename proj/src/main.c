#include <limits.h>
#include <string.h>
#include <errno.h>
#include <minix/drivers.h>

#include "video_gr.h"
#include "game.h"
#include "time.h"
#include "gamestates.h"


#include <stdio.h>


int main() {

  sef_startup();

  sys_enable_iop(SELF);

  vg_init(0x117);

  srand(time(NULL));

  startStateMachine();

  Game * ColourPop = (Game*) startGame();

  interrupt_h(ColourPop);

  vg_exit();

  return 0;
}
