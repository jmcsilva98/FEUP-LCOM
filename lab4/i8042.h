
#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_




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

#define ESC_KEY										  0x81 //breakcode of esc key

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













































#endif
