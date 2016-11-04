#include<msp430FR5725.h>
#include"RS232.h"
#include"string.h"
#include"Delay.h"
#include"i2c.h"
#include"AT24C32.h"

unsigned char Times=0;
unsigned char Uart1_Buf[Buf1_Max];
unsigned char PoP = 0;
unsigned char Uart2_Buf[Buf2_Max];
unsigned char PoP2 = 0;
/*RXD1 RESIVE DATA*/
unsigned char RXData = 0;
/*RXD2 RESIVE DATA*/
unsigned char RX2Data = 0;


//    unsigned char TXTData=0;
//    unsigned char check=0;
static unsigned char *content="0891683108501705F011000D9168\
                               5127866143F00008AA0C6D4B8BD5\
                               5DF27ECF5B8C6210";



/****************************************************************************
* ��    �ƣ�Uart1_init()
* ��    �ܣ����ڳ�ʼ������
* ��ڲ�����
* ���ڲ�����
* ˵    ����
****************************************************************************/
void Uart0_init()
{
/*RXD1&TXD1 IO�ڳ�ʼ��*/
    P2SEL1 |= BIT0 + BIT1;
    P2SEL0 &= ~(BIT0 + BIT1);

/*RXD2&TXD2 ����������*/
// UART mode is selected when the UCSYNC bit is cleared
    UCA0CTL1 |= UCSWRST;
    
// Set ACLK = 8M as UCBRCLK    
    UCA0CTL1 = UCSSEL_1;
    
// 9600 baud see pdf 491  Table 18-5
    UCA0BR0 = 52;
    UCA0BR1 = 0;
    
// UCBRSx value = 0x53 (See UG)
    UCA0MCTLW |= 0x4933;
    
// release from reset                      
    UCA0CTL1 &= ~UCSWRST;
    
// Enable RX interrupt
    UCA0IE |= UCRXIE;
  
}



/****************************************************************************
* ��    �ƣ�Uart2_init()
* ��    �ܣ����ڳ�ʼ������
* ��ڲ�����
* ���ڲ�����
* ˵    ����
****************************************************************************/
void Uart1_init()
{    
/*RXD2&TXD2 IO�ڳ�ʼ��*/
    P2SEL1 |= BIT5 + BIT6;
    P2SEL0 &= ~(BIT5 + BIT6);

/*RXD2&TXD2 ����������*/
// UART mode is selected when the UCSYNC bit is cleared
    UCA1CTL1 |= UCSWRST;
    
// Set ACLK = 8M as UCBRCLK    
    UCA1CTL1 = UCSSEL_1;
    
// 9600 baud see pdf 491 Table 18-5
    UCA1BR0 = 52;                
    UCA1BR1 = 0;
    
// UCBRSx value = 0x53 (See UG)
    UCA1MCTLW |= 0x4933;
    
// release from reset                      
    UCA1CTL1 &= ~UCSWRST;
    
// Enable RX interrupt
    UCA1IE |= UCRXIE;  
}

/****************************************************************************
* ��    �ƣ�
* ��    �ܣ�USART0�����жϺ���
* ��ڲ�����
* ���ڲ�����
* ˵    ��������800AGSMģ��
***************************************************************************/
#pragma vector = USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
// Clear interrupt
    UCA0IFG &=~ UCRXIFG;
  
// Clear buffer
    RXData = UCA0RXBUF;

//    UCA1TXBUF = RXData;
//�����յ����ַ����浽������
    Uart1_Buf[PoP] = RXData;
//����ָ������ƶ�
    PoP++;
//���������,������ָ��ָ�򻺴���׵�ַ  
    if(PoP > Buf1_Max)
    {
        PoP = 0;
    }
}


/****************************************************************************
* ��    �ƣ�
* ��    �ܣ�USART1�����жϺ���
* ��ڲ�����
* ���ڲ�����
* ˵    ����������һ�ֽڣ�����һ���ж�
***************************************************************************/
#pragma vector = USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void)
{
    UCA1IFG &=~ UCRXIFG;
    RX2Data = UCA1RXBUF;
    //    UCA1TXBUF = RXData;
//�����յ����ַ����浽������
    Uart2_Buf[PoP2] = RX2Data;
//����ָ������ƶ�
    PoP2++;
    if(RX2Data==0x0a)
    {
        word_check();
    }
//���������,������ָ��ָ�򻺴���׵�ַ  
    if(PoP2 > Buf2_Max)
    {
        PoP2 = 0;
    }
}


/****************************************************************************
* ��    �ƣ�U1
* ��    �ܣ�����һ��byte�ֽ�
* ��ڲ�����
* ���ڲ�����
* ˵    ����
***************************************************************************/

void Send_serial_1byte(unsigned char TXData)
{ 

//���������ݷ���U1������
    UCA0TXBUF = TXData;
//�ȴ����ݷ������
    while(!(UCA0IFG & UCTXIFG));
    UCA0IFG &= ~UCTXIFG;
}


/****************************************************************************
* ��    �ƣ�U2
* ��    �ܣ�����һ��byte�ֽ�
* ��ڲ�����
* ���ڲ�����
* ˵    ����
***************************************************************************/

void Send_seria2_1byte(unsigned char TXData)
{ 

//���������ݷ���U1������
    UCA1TXBUF = TXData;
//�ȴ����ݷ������
    while(!(UCA1IFG & UCTXIFG));
    UCA1IFG &= ~UCTXIFG;
}

/****************************************************************************
* ��    �ƣ�U1
* ��    �ܣ�����һ���ַ���
* ��ڲ�����
* ���ڲ�����
* ˵    ����
***************************************************************************/
void UART1_SendString(unsigned char *s)
{
//����ַ���������
    while(*s)
    {
        Send_serial_1byte(*s++);//���͵�ǰ�ַ�
    }
}

/****************************************************************************
* ��    �ƣ�U2
* ��    �ܣ�����һ���ַ���
* ��ڲ�����
* ���ڲ�����
* ˵    ����
***************************************************************************/
void UART2_SendString(unsigned char *ss)
{
//����ַ���������
    while(*ss)
    {
        Send_seria2_1byte(*ss++);//���͵�ǰ�ַ�
    }
}


/****************************************************************************
* ��    �ƣ�
* ��    �ܣ�GSMģ���������
* ��ڲ�����
* ���ڲ�����
* ˵    ����
***************************************************************************/
void CLR_Buf1(void)
{
    u16 k;
    for(k=0;k<Buf1_Max;k++)      //��������������
    {
        Uart1_Buf[k] = 0x00;
    }
    PoP = 0;              //�����ַ�������ʼ�洢λ��
}


/****************************************************************************
* ��    �ƣ�
* ��    �ܣ����ֶ�
* ��ڲ�����
* ���ڲ�����
* ˵    ����
***************************************************************************/
unsigned char Find(unsigned char *a)
{
//����string.hͷ�ļ�
    if(strstr(Uart1_Buf,a)!=NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/****************************************************************************
* ��    �ƣ�
* ��    �ܣ�ͨ�����ڷ���ATָ��
* ��ڲ�����
* ���ڲ�����
* ˵    ����
***************************************************************************/
void Second_AT_Command(u8 *b,u8 *a,u8 wait_time)         
{
    u8 i;
    u8 *c;
    c = b;										//�����ַ�����ַ��c
    CLR_Buf1(); 
    i = 0;
    while(i == 0)
    {
//��Ӧ����ַ�
        if(!Find(a))
        {
//��ʱ���·�������
            if(Times > (50*wait_time))
            {
                b = c;						 //���ַ�����ַ��b
                while(*b!='\0')
                {
                    Send_serial_1byte(*b);
                    //  delay(250);
                    b++;
                }
                UART1_SendLR();	
                delay(250);
                //Times = 0;
                //shijian = wait_time;
                Times =0;  //��ʼ��ʱ
            }//End of if(Times > (50*wait_time))
            else
            {
                Times++;
            }
        }//End of if(!Find(a))
        else
        {
            i = 1;
            Times =0;  
        }
    }//End of while(i == 0)
    CLR_Buf1(); 
}

/****************************************************************************
* ��    �ƣ�
* ��    �ܣ�����ͨ��ģ���ʽ
* ��ڲ�����
* ���ڲ�����
* ˵    ����
***************************************************************************/
void Set_Pdu_Mode(void)
{
	Second_AT_Command("ATE0","OK",3);			//�رջ��Թ���							  //ȡ������	
	Second_AT_Command("AT+CMGF=0","OK",3);								//����PDUģʽ	
	Second_AT_Command("AT+CPMS=\"SM\",\"SM\",\"SM\"","OK",3);//���в�������SIM���н���
}

/****************************************************************************
* ��    �ƣ�
* ��    �ܣ����Ͷ���ǰ������
* ��ڲ�����
* ���ڲ�����
* ˵    ����
***************************************************************************/
void Send_Pdu_Sms(void)
{
//�������ݳ��ȣ�27������ļ��㷽�������ڵ��ԱȽϣ����յ���>���ŷ��Ͷ�������
    Second_AT_Command("AT+CMGS=31",">",3); 
    UART1_SendString(content);
    delay(50);
//���ͽ�����
    Send_serial_1byte(0X1A);          
    delay(50);
}

/****************************************************************************
* ��    �ƣ�
* ��    �ܣ��ȴ�У��
* ��ڲ�����
* ���ڲ�����
* ˵    ����
***************************************************************************/
void Wait_CREG(void)
{
    u8 i;
    u8 k;
    i = 0;
    CLR_Buf1();                 
    while(i == 0)        			
    {    
//��ѯģ������ע��״̬
        CLR_Buf1();
        UART1_SendString("AT+CREG?");
        UART1_SendLR();
        delay_ms(250);
        for(k=0;k<Buf1_Max;k++)
        {
            if(Uart1_Buf[k] == ':')
            {
                //��������ע��ɹ�
                if((Uart1_Buf[k+4] == '1')||(Uart1_Buf[k+4] == '5'))
                {
                    i = 1;
                    break;
                }
            }
        }
    }
}


/****************************************************************************
* ��    �ƣ�PWRkey(void)
* ��    �ܣ����ŷ���ģ��SIM800A����
* ��ڲ�����
* ���ڲ�����
* ˵    ��������PWRKEY����1��Ȼ���ͷſ�ʹģ�鿪��
***************************************************************************/
void PWRkey(void)
{
/*�ȸߵ�ƽ���ο��ⲿ��·IO�ڵ͵�ƽʱ��SIM800A PWRKEY���ڸߵ�ƽ*/
    PWRSET_0
/*Ȼ������*/
    PWRSET_1;
    delay_s(2);
/*�ȴ�SIM��ע����ɴ��5������*/
    PWRSET_0
    delay_s(10);
}



/****************************************************************************
* ��    �ƣ�
* ��    �ܣ��������
* ��ڲ�����
* ���ڲ�����
* ˵    ����
***************************************************************************/
void CLR_Buf2(void)
{
    u16 k;
    for(k=0;k<Buf2_Max;k++)      //��������������
    {
        Uart2_Buf[k] = 0x00;
    }
    PoP2 = 0;              //�����ַ�������ʼ�洢λ��
}

/****************************************************************************
* ��    �ƣ�
* ��    �ܣ������ַ����ܼ��
* ��ڲ�����Uart1_Buf
* ���ڲ�����
* ˵    ����
***************************************************************************/
void word_check(void)
{
    unsigned int v;
    unsigned char str1[Buf2_Max];

    if(Uart2_Buf[0] == '+')
    {
        if(Uart2_Buf[2] == ' ')
        {
            for(v=0;v<(Buf2_Max-3);v++)//��ȡʵ���ֶ�
            {
                str1[v]=Uart2_Buf[v+3];
            }
            switch(Uart2_Buf[1])
            {
                case 0x41:reset_eerom();break;
                case 0x42:break;
                case 0x43:readdata_eerom();break;
                case 0x44:addslave_eerom(str1);break;
                case 0x45:delslave_eerom();break;
                case 0x46:writeadd_eerom(str1);break;
                default:break;
            }
        }
    }
    
    /*�ֶμ�������ջ���*/
    CLR_Buf2();

}

/****************************************************************************
* ��    �ƣ�
* ��    �ܣ�EEPROM����ȫд0
* ��ڲ�����reset_eerom
* ���ڲ�����
* ˵    ����
***************************************************************************/
void reset_eerom(void)
{
    unsigned int v = 0;
    unsigned int C_A = 0;
    unsigned char clear[DATA_MAXBYTES] = {0};
    unsigned char slave_clear[1] = {0};//�ֻ�����
    unsigned char slave_num[1] = {0};//�ֻ�����
    
    for(v = 0;v < SLAVE_MAX;v++)
    {
        C_A = (v * DATA_MAXBYTES) + DATA_BASE_ADD;

        EepromWrite(clear,DATA_MAXBYTES,C_A);
    }
    
    EepromWrite(slave_clear,1,SLAVE_NUMBER_ADD);
    
    EepromRead(slave_num,1,SLAVE_NUMBER_ADD); //��ȡ�ֻ�����
    UART2_SendString(slave_num);
}

/****************************************************************************
* ��    �ƣ�
* ��    �ܣ���ȡ����
* ��ڲ�����Uart1_Buf
* ���ڲ�����
* ˵    ����
***************************************************************************/
void readdata_eerom(void)
{
    unsigned int v;
    unsigned int M_A;
    unsigned char M_H,M_L;
    //�������1λ//��ϵ��ʽ11λ//λ�õ�ַ20λ
    unsigned char Master[DATA_MAXBYTES];
    unsigned char rs1[DATA_MAXBYTES];
    unsigned char slave_num[1]={0x00};//�ֻ�����
    unsigned char slave_num0=0;

    EepromRead(Master,32,DATA_BASE_ADD);//��ȡ������Ϣ
    UART2_SendString(Master);//����������Ϣ  
    
    EepromRead(slave_num,1,SLAVE_NUMBER_ADD); //��ȡ�ֻ�����
    slave_num0=slave_num[0];
    Send_seria2_1byte(slave_num[0]);
    
    for(v=0;v<slave_num0;v++)//���ͷֻ���Ϣ
    {
        M_A=(v*40)+0x28+DATA_BASE_ADD;
        M_H=M_A>>8;
        M_L=M_A&0xFF;
        Send_seria2_1byte(M_H);
        Send_seria2_1byte(M_L);
        
        EepromRead(rs1,DATA_MAXBYTES,M_A);
        UART2_SendString(rs1);
    }
}

/****************************************************************************
* ��    �ƣ�
* ��    �ܣ���ӷֻ�
* ��ڲ�����rs0
* ���ڲ�����
* ˵    ����
***************************************************************************/
void addslave_eerom(unsigned char *rs0)
{
    unsigned int S_A;
    unsigned char slave_num[1]={0x00};//�ֻ�����
    unsigned char slave_num0=0;
    
    /*��ȡ�ֻ��������Ҽ�1*/
    EepromRead(slave_num,1,SLAVE_NUMBER_ADD);
    if(slave_num[0] <= SLAVE_MAX)          //����50̧
    {
        slave_num[0]++;
    }
    EepromWrite(slave_num,1,SLAVE_NUMBER_ADD);
    slave_num0=slave_num[0];
    
    /*���յ�ַд������*/
    S_A=(slave_num0 * DATA_MAXBYTES) + DATA_BASE_ADD;
    EepromWrite(rs0,strlen(rs0),S_A);
    
}

/****************************************************************************
* ��    �ƣ�
* ��    �ܣ�ɾ�����һ̨�ֻ���Ϣ
* ��ڲ�����
* ���ڲ�����
* ˵    ����
***************************************************************************/
void delslave_eerom(void)
{
    unsigned int S_A;
    unsigned char slave_num[1]={0x00};//�ֻ�����
    unsigned char slave_num0=0;
    unsigned char claer[DATA_MAXBYTES] = {0};
    
    /*��ȡ�ֻ��������Ҽ�1*/
    EepromRead(slave_num,1,SLAVE_NUMBER_ADD);
    if(slave_num[0] > 0)          //����50̧
    {
        slave_num0=slave_num[0];
        /*���յ�ַд������*/
        S_A=(slave_num0 * DATA_MAXBYTES) + DATA_BASE_ADD;
        EepromWrite(claer,DATA_MAXBYTES,S_A);
    
        slave_num[0]--;
        EepromWrite(slave_num,1,SLAVE_NUMBER_ADD);
    }
}

/****************************************************************************
* ��    �ƣ�
* ��    �ܣ�д����
* ��ڲ�����Uart1_Buf
* ���ڲ�����
* ˵    ����
***************************************************************************/
void writeadd_eerom(unsigned char *rs)
{
    //�������1λ//��ϵ��ʽ11λ//λ�õ�ַ20λ
    EepromWrite(rs,32,DATA_BASE_ADD);
}

