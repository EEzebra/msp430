#include<msp430FR5725.h>
#include<string.h>
#include"AT24C32.h"
#include"Delay.h"
#include"i2c.h"
#include"cc1120.h"
#include"LED.h"

#define u8 unsigned char
#define u16  unsigned int
#define u32 unsigned long

#define null 0x00
#define true 0x55
#define false 0xaa

#define PWRSET_1 P2OUT |= BIT2;
#define PWRSET_0 P2OUT &=~BIT2;

#define Buf1_Max 80 
#define Buf2_Max 80

//串口1发送回车换行
#define UART1_SendLR() Send_serial_1byte(0X0D);




void Uart0_init();
void Uart1_init();
void Send_serial_1byte(u8);
void UART1_SendString(unsigned char *s);
void Send_seria2_1byte(u8);
void UART2_SendString(unsigned char *ss);

/*GSM部分通用声明*/
void CLR_Buf1(void);
unsigned char Find(u8 *a);
void Second_AT_Command(u8 *b,u8 *a,u8 wait_time);
void Set_Pdu_Mode(void);
void Send_Pdu_Sms(void);
void Wait_CREG(void);
void PWRkey(void);


/*上位机通讯部分*/

/*最多分机数量*/
#define SLAVE_MAX 50
/*数据最大长度*/
#define DATA_MAXBYTES 80
/*分机数量记录地址*/
#define SLAVE_NUMBER_ADD 0x0004
/*最多电话数量*/
#define PHONE_MAX 5
/*电话C数量记录地址*/
#define CPHONE_NUMBER_ADD 0X0003
/*电话H数量记录地址*/
#define HPHONE_NUMBER_ADD 0X0002
/*电话长度*/
#define PHONE_BYTES 12
/***************************************
EEPROM地址分配
 _______________________________________
|0x01       0x02        0x03       0x04|
|--------------------------------------|
|         电话H数量  电话C数量 分机数量|
|--------------------------------------|
|   5-85   |   主机名称EROM，长80字节  |
|--------------------------------------|
|  85-165  |  主机地址EROM，长80字节   |
|--------------------------------------|
| 165-325  |  60字节homeP，60字节custP |
|--------------------------------------|
|   325+   |  主机地址EROM，长80字节   |
|______________________________________|
****************************************/
/*数据起始地址*/
#define DATA_BASE_ADD 0x0005
#define DATA_M_ADD 0x0085
#define DATA_HOMEP 0x00A5
#define DATA_CUSTP 0x00F5
#define DATA_S_ADD 0X0145


void word_check(void);
void CLR_Buf2(void);
void reset_eerom(void);
void addphone_eerom(unsigned char *rs1);
void addphoneC_eerom(unsigned char *rs2);
void readdata_eerom(void);
void addslave_eerom(unsigned char *rs0);
void delslave_eerom(void);
void writeadd_eerom(unsigned char *rs);
void writename_eerom(unsigned char *rsn);
void send_sms(void);
void call_slav(unsigned char *code);
void time_syn(unsigned char *time);
