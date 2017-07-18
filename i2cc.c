#include"i2c.h"

void MI2C_Start(void)
{
    SDA_OUT;
    SDA_HIGH;
    SCL_HIGH;
    delay(32);
  
    SDA_LOW;
    delay(32);
  
    SCL_LOW;
    delay(32);
  
    return;
}

void MI2C_Stop(void)
{
    SDA_OUT;
    SCL_LOW;
    SDA_LOW;
    delay(32);
  
    SCL_HIGH;
    delay(32);
  
    SDA_HIGH;
    delay(32);
     return;
}

void MI2C_SendAck(void)
{
     SCL_LOW;
     SDA_OUT;
  
     SDA_LOW;
     delay(16);
    SCL_HIGH;
    delay(16);
    SCL_LOW;
}

void MI2C_SendNAck(void)
{
    SCL_LOW;
    SDA_OUT;
  
    SDA_HIGH;
    delay(16);
    SCL_HIGH;
    delay(16);
    SCL_LOW;
}

u8 Wait_Ack(void)
{
    u8 ucErrTime=0;
    
    SDA_IN;
    delay(8);
    SCL_HIGH;
    delay(8);
    while(P1IN & BIT6)
    {
        ucErrTime++;
        
        if(ucErrTime>250)
        {
            MI2C_Stop();
            return 1;
        }
    }

    SCL_LOW;
    delay(8);
    return 0;
}

u8 MI2C_SendByte(u8 txd)
{
    u8 i;
    SDA_OUT;
    SCL_LOW;
    delay(DelayTime);
    for(i=0;i<8;i++)
    {
        if(txd&0x80)
        {
            SDA_HIGH;
        }
        else
        {
            SDA_LOW;
        }
        txd<<=1;
        delay(16);
        SCL_HIGH;
        delay(16);
        SCL_LOW;
        delay(16);
  }
  
//    if(txd&0x80)
//      SDA_HIGH;
//    else
//      SDA_LOW;
//    delay(16);
//    SCL_HIGH;
//    delay(16);  
//    SCL_LOW;
//    delay(16);

    i=Wait_Ack();
    return (i);
}

u8 MI2C_ReadByte(u8 ack)
{
    u8 readbyte = 0;
    u8 i;
    SDA_IN;
    for(i=0;i<8;i++)
    {
        SCL_LOW;
        delay(16);
        SCL_HIGH;
 
        readbyte<<=1;
  
        if(P1IN & BIT6)readbyte++;
        delay(8);
    }
    if(ack==0)
    {
        MI2C_SendNAck();
    }
    else
    {
        MI2C_SendAck();
    }
    return readbyte;
}


void MI2C_ReadRX8025(u8 addr,u8 *pData,u8 len)
{
    u8 i;
    MI2C_Start();
    if(MI2C_SendByte(Slave_Address_W)==1)
    {
        MI2C_Stop();
        return;
    }
    if(MI2C_SendByte(addr)==1)
    {
        MI2C_Stop();
        return;
    }
    MI2C_Start();
    if(MI2C_SendByte(Slave_Address_R)==1)
    {
        MI2C_Stop();
        return;
    }
    for(i=0;i<(len-1);i++)
    {
        pData[i]=MI2C_ReadByte(1);
        //MI2C_Ack
    }
    pData[i]=MI2C_ReadByte(0);
    //MI2C_NAck
    MI2C_Stop();
}

void MI2C_WriteRX8025(u8 addr,u8 *pData,u8 len)
{
    u8 i;
    MI2C_Start();
    if(MI2C_SendByte(Slave_Address_W)==1)
    {
        MI2C_Stop();
        return;
    }
    if(MI2C_SendByte(addr)==1)
    {
        MI2C_Stop();
        return;
    }
    for(i=0;i<len;i++)
    {
        if(MI2C_SendByte(pData[i])==1)
        {
            MI2C_Stop();
            return;
        }
    }
    MI2C_Stop();
    delay(500);
}


void MI2C_Read24C32(u8 addr_H,u8 addr_L,u8 *pData,u8 len)
{
    u8 i;
    MI2C_Start();
    if(MI2C_SendByte(Slave_Address_W_AT)==1)
    {
        MI2C_Stop();
        return;
    }
    if(MI2C_SendByte(addr_H)==1)
    {
        MI2C_Stop();
        return;
    }
    if(MI2C_SendByte(addr_L)==1)
    {
        MI2C_Stop();
        return;
    }
    MI2C_Start();
    if(MI2C_SendByte(Slave_Address_R_AT)==1)
    {
        MI2C_Stop();
        return;
    }
    for(i=0;i<(len-1);i++)
    {
        pData[i]=MI2C_ReadByte(1);
        //MI2C_Ack
    }
    pData[i]=MI2C_ReadByte(0);
//  MI2C_SendNAck();
    MI2C_Stop();
}

void MI2C_Write24C32(u8 addr_H,u8 addr_L,u8 *pData,u8 len)
{
    u8 i;
    MI2C_Start();
    if(MI2C_SendByte(Slave_Address_W_AT)==1)
    {
        MI2C_Stop();
        return;
    }
    if(MI2C_SendByte(addr_H)==1)
    {
        MI2C_Stop();
        return;
    }
    if(MI2C_SendByte(addr_L)==1)
    {
        MI2C_Stop();
        return;
    }
    for(i=0;i<len;i++)
    {
        if(MI2C_SendByte(pData[i])==1)
        {
            MI2C_Stop();
            return;
        }
    }
    MI2C_Stop();
}

void Set_Fixed_cycle(unsigned char min)
{
    unsigned char data[1];
    
    data[0]=0x00;
    MI2C_WriteRX8025(0x0C,data,1);   //TC
    data[0]=min;
    MI2C_WriteRX8025(0x0B,data,1);   //TB
    
    data[0]=0x50;
    MI2C_WriteRX8025(0x0F,data,1);   //TIE
    
    data[0]=0x00;
    MI2C_WriteRX8025(0x0E,data,1);   //TF
  
    data[0]=0x13;
    MI2C_WriteRX8025(0x0D,data,1);   //TE
}



void close_Fixed_cycle(void)
{
    unsigned char data[1];
    
    data[0]=0x40;
    MI2C_WriteRX8025(0x0F,data,1);   //TIE
    
    data[0]=0x00;
    MI2C_WriteRX8025(0x0E,data,1);   //TF
  
    data[0]=0x03;
    MI2C_WriteRX8025(0x0D,data,1);   //TE
}
