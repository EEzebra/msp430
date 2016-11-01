/*********************************************
File name:      三相电断电报警主机模块单片机程序
    <author>:X         <version>:2.0        <date>:2016.10.21
Description:    使用msp430f1232单片机，32.768KHz晶振，串口波特率1200，
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
* 名    称：main
* 功    能：主程序
* 入口参数：
* 出口参数：
* 说    明：
****************************************************************************/
void main(void)
{
    u8 WEEK[1]={0x00};

/*看门狗禁止*/   
//WDTCTL = WDTPW + WDTCNTCL;//启动看门狗
    WDTCTL = WDTPW + WDTHOLD;

/*关中断*/
    _DINT();
/*单片机寄存器初始化*/
    mcu_init();
/*串口0初始化RXD1&TXD1*/
//    Uart0_init();
/*串口1初始化RXD2&TXD2*/
    Uart1_init();
/*IO口初始化*/
    Port_init();
/*SIM800A启动*/
//    PWRkey();
/*CC1120初始化程序*/
//    Init_CC1120();
/*开中断*/
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
                TxBuff[0]=RxBuff[2];//从机地址 RxBuff[2]
                halRfSendPacket(TxBuff,4);
            }
            if(RxBuff[3]==1)//从机error位 RxBuff[2]
            {
                error[RxBuff[2]]=0;   //有错不变
            }
            else
            {
                error[RxBuff[2]]=1;  //无错置位
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
* 名    称：mcu_init()
* 功    能：单片机相关寄存器初始化
* 入口参数：
* 出口参数：
* 说    明：
****************************************************************************/
void mcu_init()
{
    PJSEL0 |= BIT4 + BIT5;                // XT1 Setup

    CSCTL0_H = 0xA5;                      //must be written as 0XA5 when writing 
    CSCTL1 |= DCOFSEL0 + DCOFSEL1;        // Set max. DCO setting   DCO frequency 8
    CSCTL2 = SELA_0 + SELS_3 + SELM_3;    // set ACLK = XT1;   MCLK = DCO
    CSCTL3 = DIVA_0 + DIVS_3 + DIVM_3;    // set all dividers  1 / 8 / 8
    
    CSCTL4 |= XT1DRIVE_0 + XTS;           // low-freq模式
    CSCTL4 &= ~XT1BYPASS;
    CSCTL4 &= ~XT1OFF;
    
    do
    {
        CSCTL5 &= ~XT1OFFG;
        SFRIFG1 &= ~OFIFG;
    }while (SFRIFG1&OFIFG);               //wait XT1 Setup
}

/****************************************************************************
* 名    称：port_init()
* 功    能：IO口初始化
* 入口参数：
* 出口参数：
* 说    明：
****************************************************************************/

void Port_init()
{
/*1     1      0     0     0     0     1     1
  SCL  SDA    8INT  KEY2  BINT KEY1   D2   D1  */
    P1DIR |= 0xC3;//0为输入 1为输出 
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
    P3OUT |= BIT4;//P3.6输出高电平
    P3OUT |= BIT6;

/* ******当前版本先采用软件模拟I2C*****  */ 
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
* 名    称：BOOT_check()
* 功    能：开机检测初始化
* 入口参数：
* 出口参数：
* 说    明：正常开机LED1闪烁3次
****************************************************************************/
void BOOT_check(void)
{
//    u8 data_test[1]={0xaa};
//    u8 data_rs[1]={0x00};
//    
//    /*CC1120发送一次数据*/
//    halRfSendPacket(TxBufXX,2);
    
//    /*SIM800A等待SIM卡注册成功*/
//    Wait_CREG();
//    
//    /*I2C读写一次*/
//    MI2C_WriteRX8025(1,data_test,1);
//    MI2C_ReadRX8025(1,data_rs,1);
//    data_test[0]={0xbb};
//    data_rs[0]={0x00};
//    MI2C_Write24C32(0x00,0x01,data_test,1);
//    MI2C_Read24C32(0x00,0x01,data_rs,1);
    
    /*闪烁3次*/
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

