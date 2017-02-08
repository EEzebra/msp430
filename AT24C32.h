#define u8 unsigned char
#define u16  unsigned int
#define u32 unsigned long

#define EEP_MAX_PAGE_SIZE  32           //最大页写字节数
#define EEP_MAX_ROM_SIZE   32768        //EEROM容量
#define EEP_ADDR_SIZE      2            //EEROM地址字节数

/*24C32擦写时间*/
#define EEP_WRITE_DELAY_TIME   delay_ms(10)

/*24C32读*/
void EepromRead(u8 *buf , u16 len , u16 ptr);
/*24C32写*/
u8 EepromWrite(u8 *buf , u16 len , u16 ptr);
