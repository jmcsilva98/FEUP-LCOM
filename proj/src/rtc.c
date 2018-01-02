#include <minix/drivers.h>
#include <minix/syslib.h>
#include <machine/int86.h>
#include <minix/driver.h>


#include "rtc.h"

int hook_id_rtc = 15;

Date * newDate(){

Date * date = (Date*) malloc(sizeof(Date));


date->seconds = 0;
date->minutes = 0;
date->hours = 0;
date->dayOfMonth = 0;
date->month = 0;
date->year = 0;



  return date;
}

void freeDate(Date * date){
  free(date);
}


int SetInterrupts(){
unsigned long reg;
reg = BIT(4) | RTC_24_12;

if(sys_outb(RTC_ADDR_REG, REG_B) != OK) return 1;
if(sys_outb(RTC_DATA_REG, reg) != OK) return 1;

  return 0;
}


int subscribe_rtc(int *hook_id_rtc){
int h_tmp = *hook_id_rtc;


int kernelCall = sys_irqsetpolicy(RTC_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, hook_id_rtc);

if (kernelCall != OK) {
  printf("RTC: Error in sys_irqsetpolicy()\n");
  return -1;
}


kernelCall = sys_irqenable(hook_id_rtc);

if (kernelCall != OK) {
  printf("RTC: Error in sys_irqenable()\n");
  return -1;
}

return BIT(h_tmp);
}



int unsubscribe_rtc(){
int kernelCall = sys_irqdisable(&hook_id_rtc);

if (kernelCall != OK) {
  printf("RTC: Error in sys_irqdisable()\n");
  return 1;
}

kernelCall = sys_irqrmpolicy(&hook_id_rtc);

if (kernelCall != OK) {
  printf("RTC: Error in sys_irqrmpolicy()\n");
  return 1;
}

  return 0;
}


int updatingRTC(){
unsigned long reg_a = 0;

sys_outb(RTC_ADDR_REG, REG_A);
sys_inb(RTC_DATA_REG, &reg_a);

	if ((reg_a & RTC_UIP) != 0)
		return 1;
	else
		return 0;

}


int checkIfBCD(){
unsigned long reg_b = 0;

    sys_outb(RTC_ADDR_REG, REG_B);
    sys_inb(RTC_DATA_REG, &reg_b);


    if(reg_b & RTC_DM) return 0;
    else return 1;


}


unsigned long BCD_to_Binary(unsigned long bcd){

return   (((bcd & 0xF0) >> 4) * 10 + (bcd & 0x0F));

}



void updateDate(Date * date){

unsigned long dayOfMonth, month, year, regc = 0;
updatingRTC();

sys_outb(RTC_ADDR_REG, REG_C);  //cleaning the buffer
sys_inb(RTC_DATA_REG, &regc);


sys_outb(RTC_ADDR_REG, RTC_DAY_OF_MONTH);
sys_inb(RTC_DATA_REG, &dayOfMonth);



sys_outb(RTC_ADDR_REG, RTC_MONTH);
sys_inb(RTC_DATA_REG, &month);


sys_outb(RTC_ADDR_REG, RTC_YEAR);
sys_inb(RTC_DATA_REG, &year);



//if bcf convert to binary
if(checkIfBCD()){

date->dayOfMonth = BCD_to_Binary(dayOfMonth);
date->month = BCD_to_Binary(month);
date->year = BCD_to_Binary(year);
}

}


void updateHour(Date * date){
  unsigned long seconds, minutes, hours, regc = 0;

  updatingRTC();


  sys_outb(RTC_ADDR_REG, REG_C);  //clearing the flags
  sys_inb(RTC_DATA_REG, &regc);


  sys_outb(RTC_ADDR_REG, RTC_SECONDS);
  sys_inb(RTC_DATA_REG, &seconds);

  sys_outb(RTC_ADDR_REG, RTC_MINUTES);
  sys_inb(RTC_DATA_REG, &minutes);

  sys_outb(RTC_ADDR_REG, RTC_HOURS);
  sys_inb(RTC_DATA_REG, &hours);



  //if bcd convert to binary
  if(checkIfBCD()){

  date->seconds = BCD_to_Binary(seconds);
  date->minutes = BCD_to_Binary(minutes);
  date->hours = BCD_to_Binary(hours);
}

}
