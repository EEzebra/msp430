#include"i2c.h"


void MI2C_Start(void)
{
  SDA_OUT;
  SDA_HIGH;
  delay(DelayTime);
  SCL_HIGH;
  delay(DelayTime);
  
  SDA_LOW;
  delay(DelayTime);
  
//  SCL_LOW;
//  delay(DelayTime);
  
  return;
}

void MI2C_Stop(void)
{
  SDA_OUT;
  SDA_LOW;
  delay(DelayTime);
  
  SCL_HIGH;
  delay(DelayTime);

  SDA_HIGH;
  delay(DelayTime);
  return;
}

void MI2C_SendAck(void)
{
  SCL_LOW;
  SDA_OUT;
  
  SDA_LOW;
  delay(DelayTime);
  SCL_HIGH;
  delay(DelayTime);
  SCL_LOW;
}

void MI2C_SendNAck(void)
{
  SCL_LOW;
  SDA_OUT;
  
  SDA_HIGH;
  delay(DelayTime);
  SCL_HIGH;
  delay(DelayTime);
  SCL_LOW;
}

u8 Wait_Ack(void)
{
  u8 ucErrTime=0;
  SDA_IN;
//  SDA_HIGH;
  SCL_HIGH;
  delay(DelayTime);
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
  delay(DelayTime);
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
      SDA_HIGH;
    else
      SDA_LOW;
    txd<<=1;
    delay(DelayTime);
    SCL_HIGH;
    delay(DelayTime);
    SCL_LOW;
    delay(DelayTime);
  }
  SDA_HIGH;
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
    delay(DelayTime);
    SCL_HIGH;
 
    readbyte<<=1;
  
    if(P1IN & BIT6)readbyte++;
    delay(DelayTime);
  }
  if(ack==0)
    MI2C_SendNAck();
  else
    MI2C_SendAck();
  return readbyte;
}


void MI2C_ReadRX8025(u8 addr,u8 *pData,u8 len)
{
  u8 i;
  MI2C_Start();
  if(MI2C_SendByte(Slave_Address_R)==1)
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
    pData[i]=MI2C_ReadByte(0);
    //MI2C_Ack
  }
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
  if(MI2C_SendByte(Slave_Address_R_AT)==1)
  {
    MI2C_Stop();
    return;
  }
  for(i=0;i<len;i++)
  {
    pData[i]=MI2C_ReadByte(0);
    //MI2C_Ack
  }
  //MI2C_NAck
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
