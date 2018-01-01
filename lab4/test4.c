#include "test4.h"
#include "mouse.h"
#include "timer.h"
#include "keyboard.h"

unsigned int m_counter = 0;

int mouse_test_packet(unsigned short cnt){
  message msg;
  int ipc_status, r;
  unsigned long data;
  unsigned int irq_set = subscribe_mouse(&hook_id_mouse);

  if (irq_set == -1) {
    printf("Error subscribing the mouse.\n");
    return 1;
  }

enable_sMode();
enable_packets();
while (cnt > 0) { //get a request message

  r = driver_receive(ANY, &msg, &ipc_status);

  if (r != 0) {
    printf("driver_receive failed with: %d", r);
    continue;
  }

  if (is_ipc_notify(ipc_status)) {
    switch (_ENDPOINT_P(msg.m_source)) {

    case HARDWARE:    //hardware interrupt notification
      if (msg.NOTIFY_ARG & irq_set) {

        data = mouse_handler();


        if (data == -1) {
          printf("Error in reading data\n");
          return -1;
        }


if (m_counter == 0)
    {
      if((data & BIT(3)) == BIT(3))
        packet[0] = data;
        m_counter++;
    }


        else if(m_counter == 1)
            {
              packet[1] = data;
              m_counter++;
            }
            else{
              packet[2] = data;
              m_counter++;
              print_packets();
              printf("\n");
              m_counter = 0;
              cnt--;
            }

          }

        }
      }
    }



  printf("Done!\n");

  //disable_sMode();

  if (unsubscribe_mouse(&hook_id_mouse) != OK) {
		printf("Error unsubscribing the mouse\n");
		return 1;
	}
  sys_inb(OUT_BUF , &data);

  return 0;
}



int mouse_test_async(unsigned short idle_time){
  message msg;
  int second_counter = 0;
  int ipc_status, r;
  unsigned long data;
  unsigned int pcounter = 0;
  unsigned int irq_set = subscribe_mouse(&hook_id_mouse);
  unsigned int irq_set_timer = timer_subscribe_int();

  if (timer_subscribe_int() == -1) {
		printf("Error in timer_subscribe_int!\n");
		return 1;
	}

  if (irq_set == -1) {
    printf("Error subscribing the mouse.\n");
    return 1;
  }

  enable_sMode();
  enable_packets();

  while (second_counter < idle_time) { //get a request message

    r = driver_receive(ANY, &msg, &ipc_status);

    if (r != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }

    if (is_ipc_notify(ipc_status)) {

      switch (_ENDPOINT_P(msg.m_source)) {

      case HARDWARE:
      if (msg.NOTIFY_ARG & irq_set_timer) {
        pcounter++;
        if ((pcounter % 60) == 0)
        second_counter++;
      }

         //hardware interrupt notification
        if (msg.NOTIFY_ARG & irq_set) {
          second_counter = 0;
          data = mouse_handler();


          if (data == -1) {
            printf("Error in reading data\n");
            return -1;
          }


  if (m_counter == 0)
      {
        if((data & BIT(3)) == BIT(3))
          packet[0] = data;
          m_counter++;
      }


          else if(m_counter == 1)
              {
                packet[1] = data;
                m_counter++;
              }
              else{
                packet[2] = data;
                m_counter++;
                print_packets();
                printf("\n");
                m_counter = 0;
              }
          }
        }
      }
    }

    printf("Done!\n");


    if (unsubscribe_mouse(&hook_id_mouse) != OK) {
  		printf("Error unsubscribing the mouse\n");
  		return 1;
  	}

    if (timer_unsubscribe_int() == 1) {
  		printf("Error in timer_unsubscribe_int!\n");
  		return 1;
  	}

return 0;}


int mouse_test_remote(unsigned long period, unsigned short cnt){
unsigned long data;
//unsigned long config;
enable_packets();
//Disable 0xF5
disable_sMode();
//Setting remote mode
if(write_mouse(SET_REMOTE_MODE) == -1)
{
  printf("Error in setting remote mode\n");
  return -1;
}

send_cmd_kbc(CMD, KBC_CMD_REG);
sys_inb(OUT_BUF, &data);

send_cmd_kbc(0x60, KBC_CMD_REG);
send_cmd_kbc((data & 0xFC) | BIT(4), IN_BUF);
//^ To prevent minix from stealing contents of outbuffer we disable the keyboard and the interruptions of the mouse


while(cnt > 0)
{
  write_mouse(READ_DATA);

  if (sys_inb(OUT_BUF, &data) != OK) {
    printf("Error in sys_inb\n");
    return -1;
  }

	if( data == ACK){
    if (sys_inb(OUT_BUF, &data) != OK) {
      printf("Error in sys_inb\n");
      return -1;
    }

    packet[0] = data;

    if (sys_inb(OUT_BUF, &data) != OK) {
      printf("Error in sys_inb\n");
      return -1;
    }

    packet[1] = data;

    if (sys_inb(OUT_BUF, &data) != OK) {
      printf("Error in sys_inb\n");
      return -1;
    }

    packet[2] = data;

    print_packets();
    printf("\n");
    cnt--;

  }
    tickdelay(micros_to_ticks(period * 1000));
}


enable_sMode();

send_cmd_kbc(0x60, KBC_CMD_REG);
send_cmd_kbc(data | BIT(1) | ~BIT(4), OUT_BUF);

    return 0;
}



static state_t state = INIT;  // initial state; keep state

  void check_line(ev_type_t evt, short length, long x, long y) {
        switch (state) {
          case INIT:
            if( evt == RDOWN )
              state = DRAW;
                break;
          case DRAW:
            if( evt == MOVE ) {
              if( ((x >= length) && (length > 0) && (y > 0)) ||  ((x <= length) && (length < 0) && (y < 0)))
                state = COMP;
                break;
          } else if( evt == RUP )
            state = INIT;
            break;
            default:
            break;
            }
}



int mouse_test_gesture(short length){

  message msg;
  int ipc_status, r;
  unsigned long data;


  unsigned int irq_set = subscribe_mouse(&hook_id_mouse);

  if (irq_set == -1) {
    printf("Error subscribing the mouse.\n");
    return 1;
  }

  enable_sMode();
  enable_packets();
  while (state != COMP) { //get a request message

    r = driver_receive(ANY, &msg, &ipc_status);

    if (r != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }

    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {

      case HARDWARE:    //hardware interrupt notification
        if (msg.NOTIFY_ARG & irq_set) {

          data = mouse_handler();


          if (data == -1) {
            printf("Error in reading data\n");
            return -1;
          }


        if (m_counter == 0)
      {
        if((data & BIT(3)) == BIT(3))
          packet[0] = data;
          m_counter++;
      }


          else if(m_counter == 1)
              {
                packet[1] = data;
                m_counter++;
              }
              else{
                packet[2] = data;
                m_counter++;
                print_packets();
                printf("\n");

                if((packet[0] & BIT(1)) == 0)
                check_line(RUP, length,  (packet[1] ^= MOUSE_RESET) + 1,  (packet[2] ^= MOUSE_RESET) +1);
                else
                check_line(RDOWN, length, (packet[1] ^= MOUSE_RESET) + 1, (packet[2] ^= MOUSE_RESET) +1);

                m_counter = 0;
              }

            }

          }
        }
      }



    printf("Done!\n");

    //disable_sMode();

    if (unsubscribe_mouse(&hook_id_mouse) != OK) {
  		printf("Error unsubscribing the mouse\n");
  		return 1;
  	}
    sys_inb(OUT_BUF , &data);

    return 0;
  }
