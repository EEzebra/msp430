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
//����1���ͻس�����
#define UART1_SendLR() Send_serial_1byte(0X0D);


void Uart0_init();
void Uart1_init();
void Send_serial_1byte(u8);
void UART1_SendString(char *s);
void Send_seria2_1byte(u8);
void UART2_SendString(char *s);

/*GSM����ͨ������*/
void CLR_Buf1(void);
unsigned char Find(u8 *a);
void Second_AT_Command(u8 *b,u8 *a,u8 wait_time);
void Set_Pdu_Mode(void);
void Send_Pdu_Sms(void);
void Wait_CREG(void);
void PWRkey(void);


/*��λ��ͨѶ����*/
void word_check(void);
void CLR_Buf2(void);
void reset_eerom(void);
void readdata_eerom(void);
void addslave_eerom(unsigned char *rs);
void writeadd_eerom(unsigned char *rs);
