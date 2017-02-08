#include<msp430FR5725.h>
#include"Delay.h"

#define u8 unsigned char
#define u16  unsigned int

/*I2C模拟延迟时间*/
#define DelayTime 5


/*I2C从机8025地址*/
#define Slave_Address_W 0x64
#define Slave_Address_R 0x65

/*    -
    R/W   */
/*I2C从机24C32地址*/
#define Slave_Address_W_AT 0xA0
#define Slave_Address_R_AT 0xA1

/*I2C模拟引脚高低电平定义*/
#define SDA_LOW P1OUT &= 0xBF
#define SDA_HIGH P1OUT |= 0x40
#define SCL_LOW P1OUT &= 0x7F
#define SCL_HIGH P1OUT |= 0x80
#define SDA_IN P1DIR &= 0xBF
#define SDA_OUT P1DIR |= 0x40

/*I2C起始信号*/
void MI2C_Start(void);
/*I2C停止信号*/
void MI2C_Stop(void);
/*I2CACK信号*/
void MI2C_SendAck(void);
/*I2CNACK信号*/
void MI2C_SendNAck(void);
/*I2C发字节*/
u8 MI2C_SendByte(u8 txd);
/*I2C等待ACK信号*/
u8 Wait_Ack(void);
/*I2C读字节*/
u8 MI2C_ReadByte(u8 ack);

/*8025写入*/
void MI2C_WriteRX8025(u8 addr,u8 *pData,u8 len);
/*8025读取*/
void MI2C_ReadRX8025(u8 addr,u8 *pData,u8 len);
/*启动8025定时器*/
void Set_Fixed_cycle(unsigned char min);
/*关闭8025定时器*/
void close_Fixed_cycle(void);

/*24C32写入单个字节*/
void MI2C_Write24C32(u8 addr_H,u8 addr_L,u8 *pData,u8 len);
/*24C32读取单个字节*/
void MI2C_Read24C32(u8 addr_H,u8 addr_L,u8 *pData,u8 len);

