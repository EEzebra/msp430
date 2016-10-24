#include<msp430FR5725.h>
#include"Delay.h"

#define u8 unsigned char

#define DelayTime 5

#define Slave_Address_W 0x64
#define Slave_Address_R 0x65

/*    -
    R/W   */
#define Slave_Address_W_AT 0xA0
#define Slave_Address_R_AT 0xA1

#define SDA_LOW P1OUT &= 0xBF
#define SDA_HIGH P1OUT |= 0x40

#define SCL_HIGH P1OUT &= 0x7F
#define SCL_LOW P1OUT |= 0x80

#define SDA_IN P1DIR &= 0xBF
#define SDA_OUT P1DIR |= 0x40

void MI2C_Start(void);
void MI2C_Stop(void);
void MI2C_SendAck(void);
void MI2C_SendNAck(void);
u8 MI2C_SendByte(u8 txd);
u8 Wait_Ack(void);
u8 MI2C_ReadByte(u8 ack);
void MI2C_WriteRX8025(u8 addr,u8 *pData,u8 len);
void MI2C_ReadRX8025(u8 addr,u8 *pData,u8 len);
void MI2C_Write24C32(u8 addr_H,u8 addr_L,u8 *pData,u8 len);
void MI2C_Read24C32(u8 addr_H,u8 addr_L,u8 *pData,u8 len);
