#include<msp430FR5725.h>
#include"Delay.h"

#define u8 unsigned char
#define u16  unsigned int

/*I2Cģ���ӳ�ʱ��*/
#define DelayTime 5


/*I2C�ӻ�8025��ַ*/
#define Slave_Address_W 0x64
#define Slave_Address_R 0x65

/*    -
    R/W   */
/*I2C�ӻ�24C32��ַ*/
#define Slave_Address_W_AT 0xA0
#define Slave_Address_R_AT 0xA1

/*I2Cģ�����Ÿߵ͵�ƽ����*/
#define SDA_LOW P1OUT &= 0xBF
#define SDA_HIGH P1OUT |= 0x40
#define SCL_LOW P1OUT &= 0x7F
#define SCL_HIGH P1OUT |= 0x80
#define SDA_IN P1DIR &= 0xBF
#define SDA_OUT P1DIR |= 0x40

/*I2C��ʼ�ź�*/
void MI2C_Start(void);
/*I2Cֹͣ�ź�*/
void MI2C_Stop(void);
/*I2CACK�ź�*/
void MI2C_SendAck(void);
/*I2CNACK�ź�*/
void MI2C_SendNAck(void);
/*I2C���ֽ�*/
u8 MI2C_SendByte(u8 txd);
/*I2C�ȴ�ACK�ź�*/
u8 Wait_Ack(void);
/*I2C���ֽ�*/
u8 MI2C_ReadByte(u8 ack);

/*8025д��*/
void MI2C_WriteRX8025(u8 addr,u8 *pData,u8 len);
/*8025��ȡ*/
void MI2C_ReadRX8025(u8 addr,u8 *pData,u8 len);
/*����8025��ʱ��*/
void Set_Fixed_cycle(unsigned char min);
/*�ر�8025��ʱ��*/
void close_Fixed_cycle(void);

/*24C32д�뵥���ֽ�*/
void MI2C_Write24C32(u8 addr_H,u8 addr_L,u8 *pData,u8 len);
/*24C32��ȡ�����ֽ�*/
void MI2C_Read24C32(u8 addr_H,u8 addr_L,u8 *pData,u8 len);

