#include"RS232.h"

unsigned char Uart1_Buf[Buf1_Max];
unsigned char Uart2_Buf[Buf2_Max];
/*RXD1 RESIVE DATA*/
unsigned char RXData = 0;
/*RXD2 RESIVE DATA*/
unsigned char RX2Data = 0;
unsigned char PoP = 0;
unsigned char PoP2 = 0;
unsigned char Times = 0;

/****************************************************************************
* 名    称：Uart1_init()
* 功    能：串口初始化程序
* 入口参数：
* 出口参数：
* 说    明：
****************************************************************************/
void Uart0_init()
{
/*RXD1&TXD1 IO口初始化*/
    P2SEL1 |= BIT0 + BIT1;
    P2SEL0 &= ~(BIT0 + BIT1);

/*RXD2&TXD2 波特率设置*/
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
* 名    称：Uart2_init()
* 功    能：串口初始化程序
* 入口参数：
* 出口参数：
* 说    明：
****************************************************************************/
void Uart1_init()
{    
/*RXD2&TXD2 IO口初始化*/
    P2SEL1 |= BIT5 + BIT6;
    P2SEL0 &= ~(BIT5 + BIT6);

/*RXD2&TXD2 波特率设置*/
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
* 名    称：
* 功    能：USART0接收中断函数
* 入口参数：
* 出口参数：
* 说    明：用于800AGSM模块
***************************************************************************/
#pragma vector = USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
// Clear interrupt
    UCA0IFG &=~ UCRXIFG;
  
// Clear buffer
    RXData = UCA0RXBUF;

//    UCA1TXBUF = RXData;
//将接收到的字符串存到缓存中
    Uart1_Buf[PoP] = RXData;
//缓存指针向后移动
    PoP++;
//如果缓存满,将缓存指针指向缓存的首地址  
    if(PoP > Buf1_Max)
    {
        PoP = 0;
    }
}


/****************************************************************************
* 名    称：
* 功    能：USART1接收中断函数
* 入口参数：
* 出口参数：
* 说    明：接收完一字节，产生一次中断
***************************************************************************/
#pragma vector = USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void)
{
    UCA1IFG &=~ UCRXIFG;
    RX2Data = UCA1RXBUF;
    //    UCA1TXBUF = RXData;
//将接收到的字符串存到缓存中
    Uart2_Buf[PoP2] = RX2Data;
//缓存指针向后移动
    PoP2++;
    if(RX2Data==0x0a)
    {
        word_check();
    }
//如果缓存满,将缓存指针指向缓存的首地址  
    if(PoP2 > Buf2_Max)
    {
        PoP2 = 0;
    }
}


/****************************************************************************
* 名    称：U1
* 功    能：发送一个byte字节
* 入口参数：
* 出口参数：
* 说    明：
***************************************************************************/

void Send_serial_1byte(unsigned char TXData)
{ 

//将发送数据放入U1缓存中
    UCA0TXBUF = TXData;
//等待数据发送完成
    while(!(UCA0IFG & UCTXIFG));
    UCA0IFG &= ~UCTXIFG;
}


/****************************************************************************
* 名    称：U2
* 功    能：发送一个byte字节
* 入口参数：
* 出口参数：
* 说    明：
***************************************************************************/

void Send_seria2_1byte(unsigned char TXData)
{ 

//将发送数据放入U1缓存中
    UCA1TXBUF = TXData;
//等待数据发送完成
    while(!(UCA1IFG & UCTXIFG));
    UCA1IFG &= ~UCTXIFG;
}

/****************************************************************************
* 名    称：U1
* 功    能：发送一个字符串
* 入口参数：
* 出口参数：
* 说    明：
***************************************************************************/
void UART1_SendString(unsigned char *s)
{
//检测字符串结束符
    while(*s)
    {
        Send_serial_1byte(*s++);//发送当前字符
    }
}

/****************************************************************************
* 名    称：U2
* 功    能：发送一个字符串
* 入口参数：
* 出口参数：
* 说    明：
***************************************************************************/
void UART2_SendString(unsigned char *ss)
{
//检测字符串结束符
    while(*ss)
    {
        Send_seria2_1byte(*ss++);//发送当前字符
    }
}


/****************************************************************************
* 名    称：
* 功    能：GSM模块清除缓存
* 入口参数：
* 出口参数：
* 说    明：
***************************************************************************/
void CLR_Buf1(void)
{
    u16 k;
    for(k=0;k<Buf1_Max;k++)      //将缓存内容清零
    {
        Uart1_Buf[k] = 0x00;
    }
    PoP = 0;              //接收字符串的起始存储位置
}


/****************************************************************************
* 名    称：
* 功    能：找字段
* 入口参数：
* 出口参数：
* 说    明：
***************************************************************************/
unsigned char Find(unsigned char *a)
{
//调用string.h头文件
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
* 名    称：
* 功    能：通过串口发送AT指令
* 入口参数：
* 出口参数：
* 说    明：
***************************************************************************/
void Second_AT_Command(u8 *b,u8 *a,u8 wait_time)         
{
    u8 i;
    u8 *c;
    c = b;										//保存字符串地址到c
    CLR_Buf1(); 
    i = 0;
    while(i == 0)
    {
//无应答的字符
        if(!Find(a))
        {
//超时重新发送命令
            if(Times > (50*wait_time))
            {
                b = c;						 //将字符串地址给b
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
                Times =0;  //开始计时
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
* 名    称：
* 功    能：设置通用模块格式
* 入口参数：
* 出口参数：
* 说    明：
***************************************************************************/
void Set_Pdu_Mode(void)
{
	Second_AT_Command("ATE0","OK",3);			//关闭回显功能							  //取消回显	
	Second_AT_Command("AT+CMGF=0","OK",3);								//设置PDU模式	
	Second_AT_Command("AT+CPMS=\"SM\",\"SM\",\"SM\"","OK",3);//所有操作都在SIM卡中进行
}

/****************************************************************************
* 名    称：
* 功    能：发送短信前置配置
* 入口参数：
* 出口参数：
* 说    明：
***************************************************************************/
void Send_Pdu_Sms(void)
{
    unsigned char *content="0891683108501705F011000D91685127866143F00008AA0C6D4B8BD55DF27ECF5B8C6210";
//发送数据长度：27（具体的计算方法看串口调试比较）接收到“>”才发送短信内容
    Second_AT_Command("AT+CMGS=27",">",3); 
    UART1_SendString(content);
    delay(50);
//发送结束符
    Send_serial_1byte(0X1A);          
    delay(50);
}

/****************************************************************************
* 名    称：
* 功    能：等待校验
* 入口参数：
* 出口参数：
* 说    明：
***************************************************************************/
void Wait_CREG(void)
{
    u8 i;
    u8 k;
    u8 v;
    v = 0;
    i = 0;
    CLR_Buf1();                 
    while(i == 0)        			
    {    
//查询模块网络注册状态
        CLR_Buf1();
        UART1_SendString("AT+CREG?");
        UART1_SendLR();
        delay_ms(250);
        for(k=0;k<Buf1_Max;k++)
        {
            if(Uart1_Buf[k] == ':')
            {
                //表明网络注册成功
                if((Uart1_Buf[k+4] == '1')||(Uart1_Buf[k+4] == '5'))
                {
                    i = 1;
                    break;
                }
            }
        }
        v++;
        if(v>10)
        {
            PWRkey();
        }
    }
}


/****************************************************************************
* 名    称：PWRkey(void)
* 功    能：短信发射模块SIM800A重置
* 入口参数：
* 出口参数：
* 说    明：拉低PWRKEY超过1秒然后释放可使模块开机
***************************************************************************/
void PWRkey(void)
{
/*先高电平，参考外部电路IO口低电平时，SIM800A PWRKEY处于高电平*/
    PWRSET_0
/*然后拉低*/
    PWRSET_1;
    delay_s(2);
/*等待SIM卡注册完成大概5秒左右*/
    PWRSET_0
    delay_s(10);
}



/****************************************************************************
* 名    称：
* 功    能：清除缓存
* 入口参数：
* 出口参数：
* 说    明：
***************************************************************************/
void CLR_Buf2(void)
{
    u16 k;
    for(k=0;k<Buf2_Max;k++)      //将缓存内容清零
    {
        Uart2_Buf[k] = 0x00;
    }
    PoP2 = 0;              //接收字符串的起始存储位置
}

/****************************************************************************
* 名    称：
* 功    能：串口字符功能检测
* 入口参数：Uart1_Buf
* 出口参数：
* 说    明：
***************************************************************************/
void word_check(void)
{
    unsigned int v;
    unsigned char str1[Buf2_Max];

    if(Uart2_Buf[0] == '+')
    {
        if(Uart2_Buf[2] == ' ')
        {
            for(v=0;v<(Buf2_Max-3);v++)//截取实际字段
            {
                str1[v]=Uart2_Buf[v+3];
            }
            switch(Uart2_Buf[1])
            {
                case 0x41:reset_eerom();break;              //+Aspace
                case 0x42:addphone_eerom(str1);break;       //+Bspace
                case 0x43:readdata_eerom();break;           //+Cspace
                case 0x44:addslave_eerom(str1);break;       //+Dspace
                case 0x45:delslave_eerom();break;           //+Espace
                case 0x46:writeadd_eerom(str1);break;       //+Fspace
                case 0x47:send_sms();break;                 //+Gspace
                case 0x48:call_slav(str1);break;            //+Hspace
                case 0x49:time_syn(str1);break;             //+Ispace
                case 0x4A:writename_eerom(str1);break;      //+Jspace
                case 0x4B:addphoneC_eerom(str1);break;      //+Kspace
                default:break;
            }
        }
    }
    
    /*字段检测完成清空缓存*/
    CLR_Buf2();

}

/****************************************************************************
* 名    称：
* 功    能：EEPROM擦出全写0
* 入口参数：reset_eerom
* 出口参数：
* 说    明：
***************************************************************************/
void reset_eerom(void)
{
    unsigned int v = 0;
    unsigned int C_A = 0;
    unsigned char clear[DATA_MAXBYTES] = {0};
    unsigned char slave_clear[1] = {0};//分机数量
    
    for(v = 0;v < (SLAVE_MAX + 4);v++)
    {
        C_A = (v * DATA_MAXBYTES) + DATA_BASE_ADD;
        EepromWrite(clear,DATA_MAXBYTES,C_A);
    }
    
    EepromWrite(slave_clear,1,SLAVE_NUMBER_ADD);
    EepromWrite(slave_clear,1,HPHONE_NUMBER_ADD);
    EepromWrite(slave_clear,1,CPHONE_NUMBER_ADD);
    
    LEDY_Flash();
}

/****************************************************************************
* 名    称：
* 功    能：添加高优先级电话号
* 入口参数：rs1
* 出口参数：
* 说    明：
***************************************************************************/
void addphone_eerom(unsigned char *rs1)
{
    unsigned int S_A;
    unsigned char phone_num[1]={0x00};//数量
    unsigned char phone_num0=0;
    
    /*读取分机数量并且加1*/
    EepromRead(phone_num,1,HPHONE_NUMBER_ADD);
    if(phone_num[0] <= PHONE_MAX)          //少于5抬
    {
        phone_num[0]++;
    }
    EepromWrite(phone_num,1,HPHONE_NUMBER_ADD);
    phone_num0=phone_num[0];
    
    /*按照地址写入数据*/
    S_A=((phone_num0-1) * PHONE_BYTES) + DATA_HOMEP;
    EepromWrite(rs1,strlen(rs1),S_A);
    
}

/****************************************************************************
* 名    称：
* 功    能：添加低优先级电话号
* 入口参数：rs2
* 出口参数：
* 说    明：
***************************************************************************/
void addphoneC_eerom(unsigned char *rs2)
{
    unsigned int S_A;
    unsigned char phone_num[1]={0x00};//数量
    unsigned char phone_num0=0;
    
    /*读取分机数量并且加1*/
    EepromRead(phone_num,1,CPHONE_NUMBER_ADD);
    if(phone_num[0] <= PHONE_MAX)          //少于5抬
    {
        phone_num[0]++;
    }
    EepromWrite(phone_num,1,CPHONE_NUMBER_ADD);
    phone_num0=phone_num[0];
    
    /*按照地址写入数据*/
    S_A=((phone_num0-1) * PHONE_BYTES) + DATA_CUSTP;
    EepromWrite(rs2,strlen(rs2),S_A);
}

/****************************************************************************
* 名    称：
* 功    能：读取数据
* 入口参数：void
* 出口参数：
* 说    明：
***************************************************************************/
void readdata_eerom(void)
{
    unsigned int v;
    unsigned int M_A;
    unsigned char Master[DATA_MAXBYTES];
    unsigned char reg[PHONE_BYTES];
    unsigned char slave_num[1]={0x00};//分机数量
    unsigned char slave_num0=0;

    /*读取主机信息*/
    EepromRead(Master,DATA_MAXBYTES,DATA_BASE_ADD);
    UART2_SendString(Master);//发送主机信息
    /*读取主机信息*/
    EepromRead(Master,DATA_MAXBYTES,DATA_M_ADD);
    UART2_SendString(Master);//发送主机信息
    
    /*读取H电话数量*/
    EepromRead(slave_num,1,HPHONE_NUMBER_ADD);
    slave_num0=slave_num[0];
    Send_seria2_1byte(slave_num[0]);  
    for(v=0;v<slave_num0;v++)//发送电话信息
    {
        M_A=(v*PHONE_BYTES)+DATA_HOMEP;  
        EepromRead(reg,PHONE_BYTES,M_A);
        UART2_SendString(reg);
    }
    
    /*读取C电话数量*/
    EepromRead(slave_num,1,CPHONE_NUMBER_ADD);
    slave_num0=slave_num[0];
    Send_seria2_1byte(slave_num[0]);
    for(v=0;v<slave_num0;v++)//发送电话信息
    {
        M_A=(v*PHONE_BYTES)+DATA_CUSTP;
        EepromRead(reg,PHONE_BYTES,M_A);
        UART2_SendString(reg);
    }
    
    /*读取分机数量*/
    EepromRead(slave_num,1,SLAVE_NUMBER_ADD);
    slave_num0=slave_num[0];
    Send_seria2_1byte(slave_num[0]);
    for(v=0;v<slave_num0;v++)//发送分机信息
    {
        M_A=(v*DATA_MAXBYTES)+DATA_S_ADD;
        EepromRead(Master,DATA_MAXBYTES,M_A);
        UART2_SendString(Master);
    }
}

/****************************************************************************
* 名    称：
* 功    能：添加分机
* 入口参数：rs0
* 出口参数：
* 说    明：
***************************************************************************/
void addslave_eerom(unsigned char *rs0)
{
    unsigned int S_A;
    unsigned char slave_num[1]={0x00};//分机数量
    unsigned char slave_num0=0;
    
    /*读取分机数量并且加1*/
    EepromRead(slave_num,1,SLAVE_NUMBER_ADD);
    if(slave_num[0] <= SLAVE_MAX)          //少于50抬
    {
        slave_num[0]++;
    }
    EepromWrite(slave_num,1,SLAVE_NUMBER_ADD);
    slave_num0=slave_num[0];
    
    /*按照地址写入数据*/
    S_A=((slave_num0 - 1) * DATA_MAXBYTES) + DATA_S_ADD;
    EepromWrite(rs0,strlen(rs0),S_A);
    
}

/****************************************************************************
* 名    称：
* 功    能：删除最近一台分机信息
* 入口参数：
* 出口参数：
* 说    明：
***************************************************************************/
void delslave_eerom(void)
{
    unsigned int S_A;
    unsigned char slave_num[1]={0x00};//分机数量
    unsigned char slave_num0=0;
    unsigned char claer[DATA_MAXBYTES] = {0};
    
    /*读取分机数量并且加1*/
    EepromRead(slave_num,1,SLAVE_NUMBER_ADD);
    if(slave_num[0] > 0)          //少于50抬
    {
        slave_num0=slave_num[0];
        /*按照地址写入数据*/
        S_A=((slave_num0 - 1) * DATA_MAXBYTES) + DATA_S_ADD;
        EepromWrite(claer,DATA_MAXBYTES,S_A);
        /*写入分机数量*/
        slave_num[0]--;
        EepromWrite(slave_num,1,SLAVE_NUMBER_ADD);
    }
}

/****************************************************************************
* 名    称：
* 功    能：写主机
* 入口参数：Uart1_Buf
* 出口参数：
* 说    明：
***************************************************************************/
void writeadd_eerom(unsigned char *rs)
{
    //主机编号1位//公司名称39位//位置地址40位
    EepromWrite(rs,DATA_MAXBYTES,DATA_BASE_ADD);
}
void writename_eerom(unsigned char *rsn)
{
    EepromWrite(rsn,DATA_MAXBYTES,DATA_M_ADD);
}

/****************************************************************************
* 名    称：
* 功    能：写主机
* 入口参数：Uart1_Buf
* 出口参数：
* 说    明：
***************************************************************************/
void send_sms(void)
{
    unsigned char *content="0891683108501705F011000D91685127866143F00008AA0C6D4B8BD55DF27ECF5B8C6210";
    Wait_CREG();          //确认注册成功
    Set_Pdu_Mode();       //设置Pdu模式
    Second_AT_Command("AT+CMGS=27",">",3);
    UART1_SendString(content);
    Send_serial_1byte(0X1A);;
}

/****************************************************************************
* 名    称：call_slav
* 功    能：访问从机
* 入口参数：code string类型
* 出口参数：
* 说    明：当从机处于
***************************************************************************/
void call_slav(unsigned char *code)
{
    unsigned char Txcode[4]={0x0b,0x0a,0xff,0xff};
    P2IE &= ~BIT3;                                      //有发送短信响应时，关闭中断
    P2IFG &= ~BIT3;
    close_Fixed_cycle();
    
    Txcode[3]=code[0];
    halRfSendPacket(Txcode,4);
    
    P2IE |= BIT3;                      //打开中断
    P2IFG &= ~BIT3;
    StartSRX();
    Set_Fixed_cycle(0x01);
}

/****************************************************************************
* 名    称：time_syn
* 功    能：同步时间
* 入口参数：time string类型
* 出口参数：
* 说    明：对8025进行写操作
***************************************************************************/
void time_syn(unsigned char *time)
{
    
    unsigned char time0[1];
    UART2_SendString(time);
    
    time0[0]=((time[10]-0x30)<<4)+(time[11]-0x30);
    MI2C_WriteRX8025(0x00,time0,1);
    time0[0]=((time[8]-0x30)<<4)+(time[9]-0x30);
    MI2C_WriteRX8025(0x01,time0,1);  //1
    time0[0]=((time[6]-0x30)<<4)+(time[7]-0x30);
    MI2C_WriteRX8025(0x02,time0,1);  //2
    time0[0]=0x02;
    MI2C_WriteRX8025(0x03,time0,1);
    time0[0]=((time[4]-0x30)<<4)+(time[5]-0x30);
    MI2C_WriteRX8025(0x04,time0,1);
    time0[0]=((time[2]-0x30)<<4)+(time[3]-0x30);
    MI2C_WriteRX8025(0x05,time0,1);
    time0[0]=((time[0]-0x30)<<4)+(time[1]-0x30);
    MI2C_WriteRX8025(0x06,time0,1);
    
    LEDY_Flash();
}

