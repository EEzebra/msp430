#include "cc1120.h"
//******************************SPI状态初始化***********************************

void Init_CC1120(void)
{
    RES_N_0;
    RES_N_1;
    POWER_UP_RESET_CC1120();
    halRfWriteRfSettings();
}
//==============================================================================
//******************************************************************************
//函数名：delaycc(unsigned int s)
//输入：时间
//输出：无
//功能描述：普通廷时,内部用
//*****************************************************************************

void delaycc(unsigned int s)
{
    unsigned int i;
    for(i=0; i<s; i++);
    for(i=0; i<s; i++);
}
//******************************************************************************
void halWait(INT16U timeout)
{
    unsigned char m;
    do
    {
        for(m=0;m<20;m++);
    } while (timeout--);
}
//******************************************************************************
//函数名：SpiTxByte(INT8U dat)
//输入：发送的数据
//输出：无
//功能描述：SPI发送一个字节
//******************************************************************************
void SpiTxByte(INT8U dat)
{
//----------------------以下是模拟SPI时序方式-----------------------------------
    INT8U i;
    for(i=0; i<8; i++)
    {
        SCK_0;
        SCK_1;
        if(dat & 0x80)
        {
            MOSI_1;
        }
        else
        {
            MOSI_0;
        }
        dat <<= 1;
        SCK_0 ;
    }
}


//******************************************************************************
//函数名：SpisendByte(INT8U dat)
//输入：发送的数据
//输出：无
//功能描述：SPI读一个字节
//******************************************************************************
INT8U SpiRxByte(void)
{
//----------------------以下是模拟SPI时序方式-----------------------------------
    INT8U i,temp;
    temp = 0;
    for(i=0; i<8; i++)
    {
        SCK_0;
        SCK_1;
        temp <<= 1;
        if(P2IN & 0x08) temp|=0x01;
        SCK_0 ;
    }
    return temp;
}


//******************************************************************************
//函数名：
//输入：发送的数据
//输出：无
//功能描述：写一个字节
//******************************************************************************
INT8U SpiTxRxByte(INT8U dat)
{
//----------------------以下是模拟SPI时序方式-----------------------------------
    INT8U i,temp;
    temp = 0;
    SCK_0 ;
    for(i=0; i<8; i++)
    {
        if(dat & 0x80)
        {
            MOSI_1;
        }
        else
        {
            MOSI_0;
        }
        dat <<= 1;
        SCK_1;
        temp <<= 1;
        if(P2IN & 0x08) temp++;
        SCK_0 ;
    }
    return temp;
}
//*******************************************************************************
//函数名：void RESET_CC1100(void)
//输入：无
//输出：无
//功能描述：复位CC1120
//*****************************************************************************************
unsigned char RESET_CC1120(void)
{
    unsigned char j = 0;
    CSN_0 ;
    do{
        j++;
        if(j == 200) {j = 0; return MISO_ERROR;}
    }while(P2IN & 0x08);
    SpiTxRxByte(CC112X_SRES); //写入复位命令
    do
    {
        j++;
        if(200 == j)
        {
            j = 0; return MISO_ERROR;
        }
    }while(P2IN & 0x08);
    CSN_1;
    return 0;
}
//*****************************************************************************************
//函数名：void POWER_UP_RESET_CC1100(void)
//输入：无
//输出：无
//功能描述：上电复位CC1100
//*****************************************************************************************
void POWER_UP_RESET_CC1120(void)
{
    SCK_1;
    MOSI_0;
    
    CSN_1;
    halWait(3);
    CSN_0 ;
    halWait(3);
    CSN_1;
    halWait(3);
    RESET_CC1120(); //复位CC1120
}
//*****************************************************************************************
//函数名：void halSpiWriteReg(INT8U addr, INT8U value)
//输入：地址和配置字
//输出：无
//功能描述：SPI写寄存器
//*****************************************************************************************
void halSpiWriteReg(INT8U addr, INT8U value)
{
    unsigned char j = 0;
    CSN_0;
     do
    {
        j++;
        if(200 == j) return;
    }while(P2IN & 0x08);  
    
    SpiTxRxByte(addr);
    SpiTxRxByte(value); //写入配置
    CSN_1;
}



void halSpiWrite16bitReg(INT16U addr, INT8U value)
{
  INT8U tempExt  = (INT8U)(addr>>8);
  INT8U tempAddr = (INT8U)(addr & 0x00FF); 
  INT8U j=0;
  
    CSN_0;
//    halWait(3);
     do
    {
        j++;
        if(200 == j) return;
    }while(P2IN & 0x08);
    SpiTxRxByte(tempExt);
    
    SpiTxRxByte(tempAddr);
    
    SpiTxRxByte(value); //写入配置
    
    CSN_1;
  
}

//*****************************************************************************
//函数名：void halSpiWriteBurstReg(INT8U addr, INT8U *buffer, INT8U count)
//输入：地址，写入缓冲区，写入个数
//输出：无
//功能描述：SPI连续写配置寄存器
//****************************************************************************
void halSpiWriteBurstReg(INT8U addr,INT8U *buffer,INT8U count)
{
    unsigned char j = 0;
    unsigned char k,temp;
    temp = addr | WRITE_BURST;
    CSN_0;
    do
    {
        j++;
        if(200 == j) return;
    }while(P2IN & 0x08);
    SpiTxRxByte(temp);
    for (k = 0; k < count; k++)
    {
        SpiTxRxByte(buffer[k]);
        //delaycc(1);
    }
    
    CSN_1;
    return;
}
//*****************************************************************************************
//函数名：void halSpiStrobe(INT8U strobe)
//输入：命令
//输出：无
//功能描述：SPI写命令
//*****************************************************************************************
unsigned char halSpiStrobe(INT8U strobe)
{
  unsigned char j = 0;
    CSN_0 ;
    do{
        j++;
        if(j == 200) {j = 0; return MISO_ERROR;}
    }while(P2IN & 0x08);
    SpiTxRxByte(strobe); //写入复位命令
    CSN_1;
    return 1;
}
//*****************************************************************************************
//函数名：INT8U halSpiReadReg(INT8U addr)
//输入：地址
//输出：该寄存器的配置字
//功能描述：SPI读寄存器
//*****************************************************************************************
INT8U halSpiReadReg(INT8U addr)
{
    unsigned char j = 0;
    INT8U temp, value;
    temp = addr|READ_SINGLE;//读寄存器命令
 //   CSN_1;

//    SCK_0;
 //   MOSI_1;
    
    CSN_0;

    do
    {
        j++;
        if(j == 200) return MISO_ERROR;
    }while(P2IN & 0x08);
    SpiTxRxByte(temp);
    
    value = SpiTxRxByte(0);

  //  SCK_0;
 //   MOSI_1;
    CSN_1;
    return value;
}

INT8U halSpiRead16bitReg(INT16U addr)
{
    INT8U tempExt  = (INT8U)(addr>>8);
    INT8U tempAddr = (INT8U)(addr & 0x00FF);
    INT8U temp,value,k=0;
    
    temp = tempExt|READ_SINGLE;//读寄存器命令

    CSN_0;

    do
    {
        k++;
        if(k == 200) return MISO_ERROR;
    }while(P2IN & 0x08);
    SpiTxRxByte(temp);
    SpiTxRxByte(tempAddr);
    
    value = SpiTxRxByte(0);

    CSN_1;
    return value;
}
//*****************************************************************************************
//函数名：void halSpiReadBurstReg(INT8U addr, INT8U *buffer, INT8U count)
//输入：地址，读出数据后暂存的缓冲区，读出配置个数
//输出：无
//功能描述：SPI连续读配置寄存器
//*****************************************************************************************
void halSpiReadBurstReg(INT8U addr, INT8U *buffer, INT8U count)
{
    unsigned char j = 0;
    INT8U i,temp;
    temp = addr | READ_BURST; //写入要读的配置寄存器地址和读命令
    CSN_0;
    //delaycc(1);
    do
    {
    j++;
    if(200 == j) return;
    }while(P2IN & 0x08);
    //SpiTxRxByte(0x3F);
  //  while(P2IN & 0x08);
    SpiTxRxByte(temp);
    for (i = 0; i < count; i++)
    {
        buffer[i] = SpiTxRxByte(0);
    }
    CSN_1;
}
//*****************************************************************************************
//函数名：INT8U halSpiReadReg(INT8U addr)
//输入：地址
//输出：该状态寄存器当前值
//功能描述：SPI读状态寄存器
//*****************************************************************************************
INT8U halSpiReadStatus(INT8U addr)
{
    unsigned char j = 0;
    INT8U value,temp;
    temp = addr | READ_BURST; //写入要读的状态寄存器的地址同时写入读命令
    
    CSN_0;
    do
    {
        j++;
        if(200 == j) return MISO_ERROR;
    }while(P2IN & 0x08);
    SpiTxRxByte(temp);
    value = SpiTxRxByte(0);
    CSN_1;
    return value;
}

INT8U halSpiRead16bitStatus(INT16U addr)
{
    INT8U tempExt  = (INT8U)(addr>>8);
    INT8U tempAddr = (INT8U)(addr & 0x00FF);
    unsigned char j = 0;
    INT8U value,temp;
    temp = tempExt | READ_BURST; //写入要读的状态寄存器的地址同时写入读命令
    
    CSN_0;
    do
    {
        j++;
        if(200 == j) return MISO_ERROR;
    }while(P2IN & 0x08);
    SpiTxRxByte(temp);
    SpiTxRxByte(tempAddr);
    value = SpiTxRxByte(0);
    CSN_1;
    return value;
}
//*****************************************************************************************
//函数名：void halRfWriteRfSettings(RF_SETTINGS *pRfSettings)
//输入：无
//输出：无
//功能描述：配置CC1120的寄存器
//*****************************************************************************************
void halRfWriteRfSettings(void)
{
//
// Rf settings for CC1120
//
halSpiWriteReg(CC112X_IOCFG3,0xB0); //GPIO3 IO Pin Configuration
halSpiWriteReg(CC112X_IOCFG2,0x06); //GPIO2 IO Pin Configuration
halSpiWriteReg(CC112X_IOCFG1,0xB0); //GPIO1 IO Pin Configuration
halSpiWriteReg(CC112X_IOCFG0,0x40); //GPIO0 IO Pin Configuration
halSpiWriteReg(CC112X_SYNC_CFG1,0x0B); //Sync Word Detection Configuration Reg. 1
halSpiWriteReg(CC112X_DCFILT_CFG,0x1C); //Digital DC Removal Configuration
halSpiWriteReg(CC112X_PREAMBLE_CFG1,0x18); //Preamble Length Configuration Reg. 1
halSpiWriteReg(CC112X_IQIC,0xC6); //Digital Image Channel Compensation Configuration
halSpiWriteReg(CC112X_CHAN_BW,0x08); //Channel Filter Configuration
halSpiWriteReg(CC112X_MDMCFG0,0x05); //General Modem Parameter Configuration Reg. 0
halSpiWriteReg(CC112X_AGC_REF,0x20); //AGC Reference Level Configuration
halSpiWriteReg(CC112X_AGC_CS_THR,0x19); //Carrier Sense Threshold Configuration
halSpiWriteReg(CC112X_AGC_CFG1,0xA9); //Automatic Gain Control Configuration Reg. 1
halSpiWriteReg(CC112X_AGC_CFG0,0xCF); //Automatic Gain Control Configuration Reg. 0
halSpiWriteReg(CC112X_FIFO_CFG,0x00); //FIFO Configuration
halSpiWriteReg(CC112X_FS_CFG,0x14); //Frequency Synthesizer Configuration
halSpiWriteReg(CC112X_PKT_CFG0,0x20); //Packet Configuration Reg. 0
halSpiWriteReg(CC112X_PKT_LEN,0xFF); //Packet Length Configuration
halSpiWrite16bitReg(CC112X_IF_MIX_CFG,0x00); //IF Mix Configuration
halSpiWrite16bitReg(CC112X_FREQOFF_CFG,0x22); //Frequency Offset Correction Configuration
halSpiWrite16bitReg(CC112X_FREQ2,0x6C); //Frequency Configuration [23:16]
halSpiWrite16bitReg(CC112X_FREQ1,0x80); //Frequency Configuration [15:8]
halSpiWrite16bitReg(CC112X_FS_DIG1,0x00); //Frequency Synthesizer Digital Reg. 1
halSpiWrite16bitReg(CC112X_FS_DIG0,0x5F); //Frequency Synthesizer Digital Reg. 0
halSpiWrite16bitReg(CC112X_FS_CAL1,0x40); //Frequency Synthesizer Calibration Reg. 1
halSpiWrite16bitReg(CC112X_FS_CAL0,0x0E); //Frequency Synthesizer Calibration Reg. 0
halSpiWrite16bitReg(CC112X_FS_DIVTWO,0x03); //Frequency Synthesizer Divide by 2
halSpiWrite16bitReg(CC112X_FS_DSM0,0x33); //FS Digital Synthesizer Module Configuration Reg. 0
halSpiWrite16bitReg(CC112X_FS_DVC0,0x17); //Frequency Synthesizer Divider Chain Configuration ..
halSpiWrite16bitReg(CC112X_FS_PFD,0x50); //Frequency Synthesizer Phase Frequency Detector Con..
halSpiWrite16bitReg(CC112X_FS_PRE,0x6E); //Frequency Synthesizer Prescaler Configuration
halSpiWrite16bitReg(CC112X_FS_REG_DIV_CML,0x14);//Frequency Synthesizer Divider Regulator Configurat..
halSpiWrite16bitReg(CC112X_FS_SPARE,0xAC); //Frequency Synthesizer Spare
halSpiWrite16bitReg(CC112X_FS_VCO0,0xB4); //FS Voltage Controlled Oscillator Configuration Reg..
halSpiWrite16bitReg(CC112X_XOSC5,0x0E); //Crystal Oscillator Configuration Reg. 5
halSpiWrite16bitReg(CC112X_XOSC1,0x03); //Crystal Oscillator Configuration Reg. 1
}
//*****************************************************************************************
//函数名：void halRfSendPacket(INT8U *txBuffer, INT8U size)
//输入：发送的缓冲区，发送数据个数
//输出：无
//功能描述：CC1100发送一组数据
//*****************************************************************************************
void halRfSendPacket(INT8U *txBuffer, INT8U size)
{
    halSpiStrobe(CC112X_SIDLE); //强制进入空闲状态
    //halSpiWrite16bitReg(CC112X_NUM_TXBYTES, size);//写入缓冲地址，发送数据个数
	//halSpiWriteReg(CCxxx0_TXFIFO, addr);//写地址
    halSpiWriteBurstReg(CC112X_BURST_TXFIFO,txBuffer,size); //写入要发送的数据
    halSpiStrobe(CC112X_STX); //进入发送模式发送数据  
    while(!(P1IN & 0X04));
    while(P1IN & 0X04);
    halSpiStrobe(CC112X_SFTX);//清空TXFIFO缓冲区
    halSpiStrobe(CC112X_SIDLE);//强制进入空闲状态
}

INT8U halRfReceivePacket(INT8U *rxBuffer, INT8U *length)
{
    INT8U status[2];
    INT8U packetLength;
    INT8U m=(*length)*20; // 具体多少要根据datarate和length来决定
    //halSpiStrobe(CC112X_SIDLE);//强制进入空闲状态
    halSpiStrobe(CC112X_SRX); //进入接收状态
 //   while(!(P3IN & 0x80))
    if (halSpiRead16bitStatus(CC112X_NUM_RXBYTES)) //如果接的字节数不为0
    {
        packetLength = halSpiRead16bitReg(CC112X_NUM_RXBYTES);//读出第一个字节，此字节为该帧数据长度
		//halSpiReadReg(CC112X_RXFIFO);//读出地址
        if (packetLength <= *length) //如果所要的有效数据长度小于等于接收到的数据包的长度
        {
            halSpiReadBurstReg(CC112X_BURST_RXFIFO, rxBuffer, packetLength); //读出所有接收到的数据
            *length = packetLength; //把接收数据长度的修改为当前数据的长度
            // Read the 2 appended status bytes (status[0] = RSSI, status[1] = LQI)
            halSpiReadBurstReg(CC112X_BURST_RXFIFO, status, 2); //读出CRC校验位
            halSpiStrobe(CC112X_SFRX); //清洗接收缓冲区
            return 1; //如果校验成功返回接收成功
        }
        else
        {
            *length = packetLength;
            halSpiStrobe(CC112X_SFRX); //清洗接收缓冲区
            return 0;
        }
    }
    else
    return 0;
}
void CC1120_TxData(unsigned char addr,unsigned char *Temp,unsigned char num)
{
  unsigned char Tx[10]={0};
  unsigned char i;
  Tx[0] = addr;
  for(i=0;i<num;i++)
  {
    Tx[i+1] = Temp[i];
  }
  halRfSendPacket(Tx,num+1);
}





void trxReadWriteBurstSingle(unsigned char addr,unsigned char *ppData,unsigned char len)
{ 
	unsigned char k;
	/* Communicate len number of bytes: if RX - the procedure sends 0x00 to push bytes from slave*/
  if(addr&READ_SINGLE)
  {
    if(addr&READ_BURST)
    {
      for (k = 0; k < len; k++)
      {
          *ppData = SpiTxRxByte(0);     /* Store pData from last pData RX */
          ppData++;
      }
    }
    else
    { 
      *ppData = SpiTxRxByte(0);
    }
  }
  else
  {
    if(addr&WRITE_BURST)
    {
      /* Communicate len number of bytes: if TX - the procedure doesn't overwrite pData */
      for(k=0;k<len;k++)
      {
        SpiTxByte(*ppData);
        ppData++;
      }    
    }
    else
    {
      SpiTxByte(*ppData);
    }
  }
  return;
}


unsigned char trx8BitRegAccess(unsigned char accessType, unsigned char addrByte, unsigned char *pData,unsigned int len)
{
    unsigned char readValue;
  /* Pull CS_N low and wait for SO to go low before communication starts */
    CSN_0;
    while(P2IN & 0x08);
    readValue = SpiTxRxByte(accessType|addrByte); 
    trxReadWriteBurstSingle(WRITE_BURST|addrByte,pData,len);
    CSN_1;
    return(readValue);
}

unsigned char trx16BitRegAccess(unsigned char accessType, unsigned char extAddr, unsigned char regAddr, unsigned char *pData, unsigned char len)
{
    unsigned char readValue;
    unsigned char j;
    CSN_0;
    do
    {
        j++;
        if(200 == j) return MISO_ERROR;
    }while(P2IN & 0x08);
  /* send extended address byte with access type bits set */
    readValue =SpiTxRxByte(accessType|extAddr);
  /* Storing chip status */ 
    SpiTxRxByte(regAddr);
  /* Communicate len number of bytes */
    trxReadWriteBurstSingle(WRITE_BURST|extAddr,pData,len);
    CSN_1;
  /* return the status byte value */
    return(readValue);
}

