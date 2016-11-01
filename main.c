/*********************************************
File name:      �����ϵ籨������ģ�鵥Ƭ������
    <author>:X         <version>:2.0        <date>:2016.10.21
Description:    ʹ��msp430f1232��Ƭ����32.768KHz���񣬴��ڲ�����1200��
                //
                //
Others:         //
Fuction List    //
    1. ......
    2. ......
History:        //
    <author>  |  <time>  |  <version>  |  <desc>
    X         | 16.7-9   |     1.0     |  build this moudle
**********************************************/
#include<msp430FR5725.h>
#include"main.h"
#include"Delay.h"
#include"key.h"
#include"RS232.h"
#include"cc1120.h"
#include "i2c.h"
#include"LED.h"

/****************************************************************************
* ��    �ƣ�main
* ��    �ܣ�������
* ��ڲ�����
* ���ڲ�����
* ˵    ����
****************************************************************************/
void main(void)
{
    u8 WEEK[1]={0x00};

/*���Ź���ֹ*/   
//WDTCTL = WDTPW + WDTCNTCL;//�������Ź�
    WDTCTL = WDTPW + WDTHOLD;

/*���ж�*/
    _DINT();
/*��Ƭ���Ĵ�����ʼ��*/
    mcu_init();
/*����0��ʼ��RXD1&TXD1*/
//    Uart0_init();
/*����1��ʼ��RXD2&TXD2*/
    Uart1_init();
/*IO�ڳ�ʼ��*/
    Port_init();
/*SIM800A����*/
//    PWRkey();
/*CC1120��ʼ������*/
//    Init_CC1120();
/*���ж�*/
    _EINT(); 

    
//    BOOT_check();
    while(1)
    {
        __bis_SR_register(LPM0_bits + GIE);
        MI2C_Read24C32(0x05,num,1);
        for(i=0;i<num*6,i++)
        {
            while(!(halRfReceivePacket(RxBuff,4)))
            {
                TxBuff[0]=RxBuff[2];//�ӻ���ַ RxBuff[2]
                halRfSendPacket(TxBuff,4);
            }
            if(RxBuff[3]==1)//�ӻ�errorλ RxBuff[2]
            {
                error[RxBuff[2]]=0;   //�д���
            }
            else
            {
                error[RxBuff[2]]=1;  //�޴���λ
            }
        }
        for(i=0;i<num,i++)
        {
             if(!(error[num]))
            {
                constent=constent+data;
                flag=1;
            }
        }
        if(flag)
        {
            Wait_CREG();
            flag=0;
        }
        
    }//end of while(1)
}


/****************************************************************************
* ��    �ƣ�mcu_init()
* ��    �ܣ���Ƭ����ؼĴ�����ʼ��
* ��ڲ�����
* ���ڲ�����
* ˵    ����
****************************************************************************/
void mcu_init()
{
    PJSEL0 |= BIT4 + BIT5;                // XT1 Setup

    CSCTL0_H = 0xA5;                      //must be written as 0XA5 when writing 
    CSCTL1 |= DCOFSEL0 + DCOFSEL1;        // Set max. DCO setting   DCO frequency 8
    CSCTL2 = SELA_0 + SELS_3 + SELM_3;    // set ACLK = XT1;   MCLK = DCO
    CSCTL3 = DIVA_0 + DIVS_3 + DIVM_3;    // set all dividers  1 / 8 / 8
    
    CSCTL4 |= XT1DRIVE_0 + XTS;           // low-freqģʽ
    CSCTL4 &= ~XT1BYPASS;
    CSCTL4 &= ~XT1OFF;
    
    do
    {
        CSCTL5 &= ~XT1OFFG;
        SFRIFG1 &= ~OFIFG;
    }while (SFRIFG1&OFIFG);               //wait XT1 Setup
}

/****************************************************************************
* ��    �ƣ�port_init()
* ��    �ܣ�IO�ڳ�ʼ��
* ��ڲ�����
* ���ڲ�����
* ˵    ����
****************************************************************************/

void Port_init()
{
/*1     1      0     0     0     0     1     1
  SCL  SDA    8INT  KEY2  BINT KEY1   D2   D1  */
    P1DIR |= 0xC3;//0Ϊ���� 1Ϊ��� 
/*0     0      0     1    0     1     0     0
 7INT   RX2   TX2  REST GPIO2  PWKEY  RX   TX   */    
    P2DIR |= 0x14;
/*1     1      0     1    0     0     0      0
  SI   SCLK   SO  CSN    NONE  NONE  NONE   NONE   */    
    P3DIR |= 0xD0;

    P1OUT |= BIT0 + BIT1;
    P1OUT &= ~BIT2;
    P1OUT &= ~BIT4; 
    P2OUT &= ~BIT2;
    P2OUT &= ~BIT4;
    P3OUT |= BIT4;//P3.6����ߵ�ƽ
    P3OUT |= BIT6;

/* ******��ǰ�汾�Ȳ������ģ��I2C*****  */ 
//  P1SEL1 |= BIT6 + BIT7;  set the i2c   

///*1=HIGH TO LOW
//  0=LOW  TO HIGH*/
//    P1IES &= ~BIT2;
//    P1IES &= ~BIT4;
//    P1IES |= BIT3 + BIT5;
//    P2IES |= BIT7;
//    
///*enable the IE*/
//    P1IE |= BIT2 + BIT3 + BIT4 + BIT5;
//    P2IE |= BIT7;

/*1=ENABLED*/
    P1IFG &= ~BIT2;
    P1IFG &= ~BIT3;
    P1IFG &= ~BIT4;
    P1IFG &= ~BIT5;
    P2IFG &= ~BIT7;
}
/****************************************************************************
* ��    �ƣ�BOOT_check()
* ��    �ܣ���������ʼ��
* ��ڲ�����
* ���ڲ�����
* ˵    ������������LED1��˸3��
****************************************************************************/
void BOOT_check(void)
{
//    u8 data_test[1]={0xaa};
//    u8 data_rs[1]={0x00};
//    
//    /*CC1120����һ������*/
//    halRfSendPacket(TxBufXX,2);
    
//    /*SIM800A�ȴ�SIM��ע��ɹ�*/
//    Wait_CREG();
//    
//    /*I2C��дһ��*/
//    MI2C_WriteRX8025(1,data_test,1);
//    MI2C_ReadRX8025(1,data_rs,1);
//    data_test[0]={0xbb};
//    data_rs[0]={0x00};
//    MI2C_Write24C32(0x00,0x01,data_test,1);
//    MI2C_Read24C32(0x00,0x01,data_rs,1);
    
    /*��˸3��*/
    LED_red_on;
    delay_s(1);
    LED_red_off;
    delay_s(1);
    
    LED_red_on;
    delay_s(1);
    LED_red_off;
    delay_s(1);
    
    LED_red_on;
    delay_s(1);
    LED_red_off;
    delay_s(1);
}

