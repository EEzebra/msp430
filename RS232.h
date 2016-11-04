#define u8 unsigned char
#define u16  unsigned int
#define u32 unsigned long


#define null 0x00
#define true 0x55
#define false 0xaa

#define PWRSET_1 P2OUT |= BIT2;
#define PWRSET_0 P2OUT &=~BIT2;

#define Buf1_Max 50 
#define Buf2_Max 50
//串口1发送回车换行
#define UART1_SendLR() Send_serial_1byte(0X0D);



void Uart0_init();
void Uart1_init();
void Send_serial_1byte(u8);
void UART1_SendString(unsigned char *s);
void Send_seria2_1byte(u8);
void UART2_SendString(unsigned char *ss);

/*GSM部分通用声明*/
void CLR_Buf1(void);
unsigned char Find(u8 *a);
void Second_AT_Command(u8 *b,u8 *a,u8 wait_time);
void Set_Pdu_Mode(void);
void Send_Pdu_Sms(void);
void Wait_CREG(void);
void PWRkey(void);


/*上位机通讯部分*/

/*最多分机数量*/
#define SLAVE_MAX 50   
/*数据最大长度*/
#define DATA_MAXBYTES 40
/*数据起始地址*/
#define DATA_BASE_ADD 0x0005
/*分机数量记录地址*/
#define SLAVE_NUMBER_ADD 0x0004

void word_check(void);
void CLR_Buf2(void);
void reset_eerom(void);
void readdata_eerom(void);
void addslave_eerom(unsigned char *rs0);
void delslave_eerom(void);
void writeadd_eerom(unsigned char *rs);

