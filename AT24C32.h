#define u8 unsigned char
#define u16  unsigned int
#define u32 unsigned long

#define EEP_MAX_PAGE_SIZE  32           //���ҳд�ֽ���
#define EEP_MAX_ROM_SIZE   32768     // EEROM����
#define EEP_ADDR_SIZE      2            // EEROM��ַ�ֽ���


#define EEP_WRITE_DELAY_TIME   delay_ms(10)

void EepromRead(u8 *buf , u16 len , u16 ptr);
u8 EepromWrite(u8 *buf , u16 len , u16 ptr);
