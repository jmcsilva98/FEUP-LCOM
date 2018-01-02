
#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

/** @defgroup i8042 i8042
 * @{
 *
 * Constants for programming the i8042
 */

#define BIT(n)										(0x01<<(n))

#define KEYBOARD_IRQ								1
#define MOUSE_IRQ                   12
#define DELAY_US   									20000

#define STAT_REG									 	0x64	//status register
#define KBC_CMD_REG									0x64
#define IN_BUF										  0x60
#define OUT_BUF									    0x60
#define CMD											    0x20

#define IBF											    BIT(1) //input buffer is full if bit 1
#define OBF											    BIT(0) //output buffer is full
#define PAR_ERR										  BIT(7)
#define TO_ERR  										BIT(6)

#define TWO_BYTE_SCANCODES 				 	0xE0



#define ESC_KEY										  0x81
#define A_KEY_MAKECODE							0x1E
#define D_KEY_MAKECODE					    0x20

//KEY BREAKCODES
#define A_KEY										    0x9E
#define B_KEY										    0xB0
#define C_KEY										    0xAE
#define D_KEY										    0xA0
#define E_KEY										    0x92
#define F_KEY										    0xA1
#define G_KEY										    0xA2
#define H_KEY										    0xA3
#define I_KEY										    0x97
#define J_KEY										    0xA4
#define K_KEY										    0xA5
#define L_KEY										    0xA6
#define M_KEY										    0xB2
#define N_KEY										    0xB1
#define O_KEY										    0x98
#define P_KEY                       0x99
#define Q_KEY										    0x90
#define R_KEY                       0x93
#define S_KEY										    0x9F
#define T_KEY                       0x94
#define U_KEY                       0x96
#define W_KEY                       0x91
#define V_KEY                       0xAF
#define Y_KEY                       0x95
#define X_KEY                       0xAD
#define Z_KEY                       0xAC
#define SPACE_KEY                   0x39
#define ENTER_KEY                   0x9C



/*working with assembly, rest of the macros already created*/

#define OUT_BUF_FULL                0x01

#define DISABLE_MOUSE               0xA7
#define ENABLE_MOUSE                0xA8
#define WRITE_BYTE_TO_MOUSE         0xD4

#define ACK                         0xFA //if everything is ok
#define NACK                        0xFE
#define ERROR                       0xFC
#define READ_DATA                   0xEB

//commands passed as arguments of command 0xD4
#define MOUSE_RESET                 0xFF
#define SET_STREAM_MODE             0xEA
#define DISABLE_STREAM_MODE         0xF5
#define ENABLE_SENDING_DATA         0xF4
#define SET_REMOTE_MODE             0xF0


//graphics
#define LEFT_X_EDGE                 266
#define UPPER_Y_EDGE                115
#define LOWER_Y_EDGE                639
#define RIGHT_X_EDGE                752

#define N_ROWS_I                    5
#define N_ROWS_MAX                  10
#define MAX_BUBBLES_LINE            11
#define BUBBLE_WIDTH                44
#define BUBBLE_HIGHT                44

#define NMBS_WIDTH                  20

/**@}*/

#endif /* LCOM_I8042_H */
