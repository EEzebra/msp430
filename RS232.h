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

//����1���ͻس�����
#define UART1_SendLR() Send_serial_1byte(0X0D);




void Uart0_init();
void Uart1_init();
void Send_serial_1byte(u8);
void UART1_SendString(unsigned char *s);
void Send_seria2_1byte(u8);
void UART2_SendString(unsigned char *ss);

/*GSM����ͨ������*/
void CLR_Buf1(void);
unsigned char Find(u8 *a);
void Second_AT_Command(u8 *b,u8 *a,u8 wait_time);
void Set_Pdu_Mode(void);
void Send_Pdu_Sms(void);
void Wait_CREG(void);
void PWRkey(void);


/*��λ��ͨѶ����*/

/*���ֻ�����*/
#define SLAVE_MAX 50
/*������󳤶�*/
#define DATA_MAXBYTES 80
/*�ֻ�������¼��ַ*/
#define SLAVE_NUMBER_ADD 0x0004
/*���绰����*/
#define PHONE_MAX 5
/*�绰C������¼��ַ*/
#define CPHONE_NUMBER_ADD 0X0003
/*�绰H������¼��ַ*/
#define HPHONE_NUMBER_ADD 0X0002
/*�绰����*/
#define PHONE_BYTES 12
/***************************************
EEPROM��ַ����
 _______________________________________
|0x01       0x02        0x03       0x04|
|--------------------------------------|
|         �绰H����  �绰C���� �ֻ�����|
|--------------------------------------|
|   5-85   |   ��������EROM����80�ֽ�  |
|--------------------------------------|
|  85-165  |  ������ַEROM����80�ֽ�   |
|--------------------------------------|
| 165-325  |  60�ֽ�homeP��60�ֽ�custP |
|--------------------------------------|
|   325+   |  ������ַEROM����80�ֽ�   |
|______________________________________|
****************************************/
/*������ʼ��ַ*/
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
