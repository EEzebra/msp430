#include<msp430FR5725.h>
#include"Delay.h"

#define u8 unsigned char
#define u16  unsigned int

#define DelayTime 5

#define Slave_Address_W 0x64
#define Slave_Address_R 0x65

/*    -
    R/W   */
#define Slave_Address_W_AT 0xA0
#define Slave_Address_R_AT 0xA1

#define SDA_LOW P1OUT &= 0xBF
#define SDA_HIGH P1OUT |= 0x40

#define SCL_LOW P1OUT &= 0x7F
#define SCL_HIGH P1OUT |= 0x80

#define SDA_IN P1DIR &= 0xBF
#define SDA_OUT P1DIR |= 0x40

void MI2C_Start(void);
void MI2C_Stop(void);
void MI2C_SendAck(void);
void MI2C_SendNAck(void);
u8 MI2C_SendByte(u8 txd);
u8 Wait_Ack(void);
u8 MI2C_ReadByte(u8 ack);

/*8025 test code*/
//    WEEK[0]=0x08;
    //MI2C_WriteRX8025(0,WEEK,1);
//    MI2C_ReadRX8025(0,R_WEEK,1);
//    UCA1TXBUF = R_WEEK[0];
void MI2C_WriteRX8025(u8 addr,u8 *pData,u8 len);
void MI2C_ReadRX8025(u8 addr,u8 *pData,u8 len);

/*24C32 test code*/
//        WEEK[0]=0xbb;
//    MI2C_Write24C32(0x04,0x01,WEEK,1);
//    delay_ms(10);
//    MI2C_Read24C32(0x04,0x01,R_WEEK,1);
//    UCA1TXBUF = R_WEEK[0];
void MI2C_Write24C32(u8 addr_H,u8 addr_L,u8 *pData,u8 len);
void MI2C_Read24C32(u8 addr_H,u8 addr_L,u8 *pData,u8 len);
void Set_Fixed_cycle(unsigned char min);
void close_Fixed_cycle(void);
