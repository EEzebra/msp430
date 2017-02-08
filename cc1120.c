#include "cc1120.h"
//******************************SPI״̬��ʼ��***********************************
void Init_CC1120(void)
{
    RES_N_0;
    RES_N_1;
    POWER_UP_RESET_CC1120();
    halRfWriteRfSettings();
}
//==============================================================================
//******************************************************************************
//��������delaycc(unsigned int s)
//���룺ʱ��
//�������
//������������ͨ͢ʱ,�ڲ���
//******************************************************************************

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
//��������SpiTxByte(INT8U dat)
//���룺���͵�����
//�������
//����������SPI����һ���ֽ�
//******************************************************************************
void SpiTxByte(INT8U dat)
{
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
//��������SpisendByte(INT8U dat)
//���룺���͵�����
//�������
//����������SPI��һ���ֽ�
//******************************************************************************
INT8U SpiRxByte(void)
{
    INT8U i,temp;
    temp = 0;
    for(i=0; i<8; i++)
    {
        SCK_0;
        SCK_1;
        temp <<= 1;
        if(P3IN & 0x20) temp|=0x01;
        SCK_0 ;
    }
    return temp;
}


//******************************************************************************
//��������
//���룺���͵�����
//�������
//����������дһ���ֽ�
//******************************************************************************
INT8U SpiTxRxByte(INT8U dat)
{
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
        if(P3IN & 0x20) temp++;
        SCK_0 ;
    }
    return temp;
}
//******************************************************************************
//��������void RESET_CC1100(void)
//���룺��
//�������
//������������λCC1120
//******************************************************************************
unsigned char RESET_CC1120(void)
{
    unsigned char j = 0;
    CSN_0 ;
    do{
        j++;
        if(j == 200) {j = 0; return MISO_ERROR;}
    }while(P3IN & 0x20);
    SpiTxRxByte(CC112X_SRES); //д�븴λ����
    do
    {
        j++;
        if(200 == j)
        {
            j = 0; return MISO_ERROR;
        }
    }while(P3IN & 0x20);
    CSN_1;
    return 0;
}
//******************************************************************************
//��������void POWER_UP_RESET_CC1100(void)
//���룺��
//�������
//�����������ϵ縴λCC1100
//******************************************************************************
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
    RESET_CC1120(); //��λCC1120
}
//******************************************************************************
//��������void halSpiWriteReg(INT8U addr, INT8U value)
//���룺��ַ��������
//�������
//����������SPIд�Ĵ���
//******************************************************************************
void halSpiWriteReg(INT8U addr, INT8U value)
{
    unsigned char j = 0;
    CSN_0;
     do
    {
        j++;
        if(200 == j) return;
    }while(P3IN & 0x20);  
    
    SpiTxRxByte(addr);
    SpiTxRxByte(value); //д������
    CSN_1;
}



void halSpiWrite16bitReg(INT16U addr, INT8U value)
{
  INT8U tempExt  = (INT8U)(addr>>8);
  INT8U tempAddr = (INT8U)(addr & 0x00FF); 
  INT8U j=0;
  
    CSN_0;
     do
    {
        j++;
        if(200 == j) return;
    }while(P3IN & 0x20);
    SpiTxRxByte(tempExt);
    
    SpiTxRxByte(tempAddr);
    
    SpiTxRxByte(value); //д������
    
    CSN_1;
  
}

//******************************************************************************
//��������void halSpiWriteBurstReg(INT8U addr, INT8U *buffer, INT8U count)
//���룺��ַ��д�뻺������д�����
//�������
//����������SPI����д���üĴ���
//******************************************************************************
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
    }while(P3IN & 0x20);
    SpiTxRxByte(temp);
    for (k = 0; k < count; k++)
    {
        SpiTxRxByte(buffer[k]);
        //delaycc(1);
    }
    
    CSN_1;
    return;
}

//******************************************************************************
//��������void halSpiStrobe(INT8U strobe)
//���룺����
//�������
//����������SPIд����
//******************************************************************************
unsigned char halSpiStrobe(INT8U strobe)
{
  unsigned char j = 0;
    CSN_0 ;
    do{
        j++;
        if(j == 200) {j = 0; return MISO_ERROR;}
    }while(P3IN & 0x20);
    SpiTxRxByte(strobe); //д�븴λ����
    CSN_1;
    return 1;
}

//******************************************************************************
//��������INT8U halSpiReadReg(INT8U addr)
//���룺��ַ
//������üĴ�����������
//����������SPI���Ĵ���
//******************************************************************************
INT8U halSpiReadReg(INT8U addr)
{
    unsigned char j = 0;
    INT8U temp, value;
    temp = addr|READ_SINGLE;//���Ĵ�������
    
    CSN_0;

    do
    {
        j++;
        if(j == 200) return MISO_ERROR;
    }while(P3IN & 0x20);
    SpiTxRxByte(temp);
    
    value = SpiTxRxByte(0);

    CSN_1;
    return value;
}

INT8U halSpiRead16bitReg(INT16U addr)
{
    INT8U tempExt  = (INT8U)(addr>>8);
    INT8U tempAddr = (INT8U)(addr & 0x00FF);
    INT8U temp,value,k=0;
    
    temp = tempExt|READ_SINGLE;//���Ĵ�������

    CSN_0;

    do
    {
        k++;
        if(k == 200) return MISO_ERROR;
    }while(P3IN & 0x20);
    SpiTxRxByte(temp);
    SpiTxRxByte(tempAddr);
    
    value = SpiTxRxByte(0);

    CSN_1;
    return value;
}

//******************************************************************************
//��������void halSpiReadBurstReg(INT8U addr, INT8U *buffer, INT8U count)
//���룺��ַ���������ݺ��ݴ�Ļ��������������ø���
//�������
//����������SPI���������üĴ���
//******************************************************************************
void halSpiReadBurstReg(INT8U addr, INT8U *buffer, INT8U count)
{
    unsigned char j = 0;
    INT8U i,temp;
    temp = addr | READ_BURST; //д��Ҫ�������üĴ�����ַ�Ͷ�����
    CSN_0;
    //delaycc(1);
    do
    {
    j++;
    if(200 == j) return;
    }while(P3IN & 0x20);
    SpiTxRxByte(temp);
    for (i = 0; i < count; i++)
    {
        buffer[i] = SpiTxRxByte(0);
    }
    CSN_1;
}

//******************************************************************************
//��������INT8U halSpiReadReg(INT8U addr)
//���룺��ַ
//�������״̬�Ĵ�����ǰֵ
//����������SPI��״̬�Ĵ���
//******************************************************************************
INT8U halSpiReadStatus(INT8U addr)
{
    unsigned char j = 0;
    INT8U value,temp;
    temp = addr | READ_BURST; //д��Ҫ����״̬�Ĵ����ĵ�ַͬʱд�������
    
    CSN_0;
    do
    {
        j++;
        if(200 == j) return MISO_ERROR;
    }while(P3IN & 0x20);
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
    temp = tempExt | READ_BURST; //д��Ҫ����״̬�Ĵ����ĵ�ַͬʱд�������
    
    CSN_0;
    do
    {
        j++;
        if(200 == j) return MISO_ERROR;
    }while(P3IN & 0x20);
    SpiTxRxByte(temp);
    SpiTxRxByte(tempAddr);
    value = SpiTxRxByte(0);
    CSN_1;
    return value;
}

//******************************************************************************
//��������void halRfWriteRfSettings(RF_SETTINGS *pRfSettings)
//���룺��
//�������
//��������������CC1120�ļĴ���
//******************************************************************************
void halRfWriteRfSettings(void)
{
halSpiWriteReg(CC112X_IOCFG3,0xB0); //GPIO3 IO Pin Configuration
halSpiWriteReg(CC112X_IOCFG2,0x06); //GPIO2 IO Pin Configuration
halSpiWriteReg(CC112X_IOCFG1,0xB0); //GPIO1 IO Pin Configuration
halSpiWriteReg(CC112X_IOCFG0,0x40); //GPIO0 IO Pin Configuration
halSpiWriteReg(CC112X_SYNC_CFG1,0x0B); //Sync Word Detection Configuration Reg. 1

//halSpiWriteReg(CC112X_SYNC_CFG0,0x15); //Sync Word Detection Configuration Reg. 0

halSpiWriteReg(CC112X_DCFILT_CFG,0x1C); //Digital DC Removal Configuration
halSpiWriteReg(CC112X_PREAMBLE_CFG1,0x18); //Preamble Length Configuration Reg. 1
halSpiWriteReg(CC112X_IQIC,0xC6); //Digital Image Channel Compensation Configuration
halSpiWriteReg(CC112X_CHAN_BW,0x08); //Channel Filter Configuration
halSpiWriteReg(CC112X_MDMCFG0,0x05); //General Modem Parameter Configuration Reg. 0

halSpiWriteReg(CC112X_DRATE2,0x73);//9600 Bit rate & Symbol rate

halSpiWriteReg(CC112X_AGC_REF,0x20); //AGC Reference Level Configuration
halSpiWriteReg(CC112X_AGC_CS_THR,0x19); //Carrier Sense Threshold Configuration
halSpiWriteReg(CC112X_AGC_CFG1,0xA9); //Automatic Gain Control Configuration Reg. 1
halSpiWriteReg(CC112X_AGC_CFG0,0xCF); //Automatic Gain Control Configuration Reg. 0

halSpiWriteReg(CC112X_FIFO_CFG,0x80); //FIFO Configuration

halSpiWriteReg(CC112X_FS_CFG,0x14); //Frequency Synthesizer Configuration
halSpiWriteReg(CC112X_PKT_CFG0,0x20); //Packet Configuration Reg. 0

halSpiWriteReg(CC112X_DEV_ADDR,0x0a);
halSpiWriteReg(CC112X_PKT_CFG1,0x25); //Packet Configuration Reg. 1

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

//******************************************************************************
//��������void halRfSendPacket(INT8U *txBuffer, INT8U size)
//���룺���͵Ļ��������������ݸ���
//�������
//����������CC1100����һ������
//******************************************************************************
void halRfSendPacket(INT8U *txBuffer, INT8U size)
{
  
  halSpiStrobe(CC112X_SIDLE); //ǿ�ƽ������״̬
  halSpiWriteReg(CC112X_SINGLE_TXFIFO, size);
  halSpiWriteBurstReg(CC112X_BURST_TXFIFO,txBuffer,size); //д��Ҫ���͵�����
  
  halSpiStrobe(CC112X_STX); //���뷢��ģʽ��������  
  while(!(P2IN & 0X08));
  while(P2IN & 0X08);
  halSpiStrobe(CC112X_SFTX);//���TXFIFO������
  delaycc(2);
  halSpiStrobe(CC112X_SIDLE);//ǿ�ƽ������״̬
  delaycc(10);

}

INT8U halRfReceivePacket(INT8U *rxBuffer, INT8U *length)
{
    INT8U packetLength;
    INT8U m=(*length)*10; // �������Ҫ����datarate��length������
    //halSpiStrobe(CC112X_SIDLE);//ǿ�ƽ������״̬
  //  halSpiStrobe(CC112X_SFRX);
    halSpiStrobe(CC112X_SRX); //�������״̬
    while(!(P2IN & 0X08))
    {
        delaycc(2);
        --m;
        if(m<1)
        {
            return 0;
        }
    }
    while(P2IN & 0X08);
    
    if (halSpiRead16bitReg(CC112X_NUM_RXBYTES)!=0) //����ӵ��ֽ�����Ϊ0
    {
        if((halSpiRead16bitReg(CC112X_MARCSTATE)&0x1F)==0x11)
        {
            halSpiStrobe(CC112X_SRX);
            return 0;
        }
        else
        {
            packetLength = halSpiRead16bitReg(CC112X_NUM_RXBYTES);//������һ���ֽڣ����ֽ�Ϊ��֡���ݳ���
		//halSpiReadReg(CC112X_RXFIFO);//������ַ
            halSpiReadBurstReg(CC112X_BURST_RXFIFO, rxBuffer, packetLength); //�������н��յ�������
            // Read the 2 appended status bytes (status[0] = RSSI, status[1] = LQI)
            //halSpiReadBurstReg(CC112X_BURST_RXFIFO, status, 2); //����CRCУ��λ
        
            halSpiStrobe(CC112X_SFRX); //��ϴ���ջ�����
        
            return 1; //���У��ɹ����ؽ��ճɹ�
        }
    }
    else
    {
        halSpiStrobe(CC112X_SFRX);
        halSpiStrobe(CC112X_SRX);
    }

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

INT8U halRfReceivePacketInt(INT8U *rxBufferi)
{
    INT8U packetLength;
    while(P2IN & 0X08);
    if (halSpiRead16bitReg(CC112X_NUM_RXBYTES)!=0) //����ӵ��ֽ�����Ϊ0
    {
        if((halSpiRead16bitReg(CC112X_MARCSTATE)&0x1F)==0x11)
        {
            halSpiStrobe(CC112X_SRX);
            return 0;
        }
        else
        {
            packetLength = halSpiRead16bitReg(CC112X_NUM_RXBYTES);//������һ���ֽڣ����ֽ�Ϊ��֡���ݳ���
		//halSpiReadReg(CC112X_RXFIFO);//������ַ
            halSpiReadBurstReg(CC112X_BURST_RXFIFO, rxBufferi, packetLength); //�������н��յ�������
            // Read the 2 appended status bytes (status[0] = RSSI, status[1] = LQI)
            //halSpiReadBurstReg(CC112X_BURST_RXFIFO, status, 2); //����CRCУ��λ
        
            halSpiStrobe(CC112X_SFRX); //��ϴ���ջ�����
        
            return 1; //���У��ɹ����ؽ��ճɹ�
        }
    }
    else
    {
        halSpiStrobe(CC112X_SFRX);
        halSpiStrobe(CC112X_SRX);
    }

    return 0;
}

void StartSRX(void)
{
    halSpiStrobe(CC112X_SRX); //�������״̬
}

void CC1120INTinit(void)
{
    P2DIR &= ~(BIT3);  
    
    P2REN |= (BIT3);
    P2OUT &= ~(BIT3);
    
    P2IES &= ~(BIT3); // LOW TO HIGH
    P2IE |= BIT3;
   // P2IFG =0;
    P2IFG &= ~BIT3;
    
}
