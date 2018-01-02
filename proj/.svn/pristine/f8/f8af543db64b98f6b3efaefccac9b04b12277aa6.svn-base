#ifndef RTC_H
#define RTC_H

/**defgroup rtc rtc
*@{
*  Functions that operate the rtc
*/

/**
*@struct Date
*@brief Struct that represents the Date
*/
typedef struct{
int seconds;
int minutes;
int hours;
int dayOfMonth;
int month;
int year;
}Date;

extern int hook_id_rtc;

//Constants used in the RTC_H
#define BIT(n) (0x01<<(n))

#define RTC_ADDR_REG	     0x70
#define RTC_DATA_REG       0x71

#define REG_A              10
#define REG_B              11
#define REG_C					     12
#define REG_D					     13

#define RTC_UIP	           BIT(7) //REG A - update in progress
#define RTC_DM				     BIT(2)//REG B - 1 - binary/ 0 - BCD (mode)
#define RTC_24_12          BIT(1)//set to 1 hours range 0 to 23 and to 0 1 to 12
#define RTC_UIE            BIT(4) //set to 1 to enable corresponding interrupt source
#define RTC_IRQ             8 // interrupt in rtc



#define RTC_SECONDS         0
#define RTC_MINUTES         2
#define RTC_HOURS           4
#define RTC_DAY_OF_MONTH    7
#define RTC_MONTH           8
#define RTC_YEAR            9


/**
 * @brief Creates a new date
 *
 * @return pointer to the Date struct
 */

Date * newDate();

/**
 * @brief Frees the memory allocated by the date
 *
 * @param date pointer to an object of the Date struct
 */

void freeDate(Date * date);

/**
 * @brief Allows the rtc interrupts
 *
 * @return 0 upon success, non-zero otherwise
 */

int SetInterrupts();

/**
 * @brief Subscribes rtc interrupts
 *
 * @param  hook_id_rtc hook id of the rtc
 *
 * @return BIT(h_tmp) bit of the saved hook_id_rtc
 */

int subscribe_rtc(int *hook_id_rtc);

/**
 * @brief Unsubscribes the rtc interrupts
 *
 * @return 0 upon success, non-zero otherwise
 */

int unsubscribe_rtc();

/**
 * @brief Checks if the rtc is updating by checking in register A the UIP
 *
 * @return 1 if rtc is updating, 0 if not
 */

int updatingRTC();

/**
 * @brief Confirms if the values given by the rtc are in bcd by checking in register B the DM
 *
 * @return 0 if bcd, non-zero if binary
 */

int checkIfBCD();

/**
 * @brief Converts from bcd to binary
 *
 * @param  bcd bcd number to convert to binary
 *
 * @return number in binary
 */

unsigned long BCD_to_Binary(unsigned long bcd);

/**
 * @brief Reads and updates the current date (day, month and year)
 *
 * @param date pointer to an object of the Date struct
 */

void updateDate(Date * date);

/**
 * @brief Reads and updates the current hour of the day (hours, minutes and seconds)
 *
 * @param date pointer to an object of the Date struct
 */
void updateHour(Date * date);

/** @} end of rtc */
#endif/*RTC_H */
