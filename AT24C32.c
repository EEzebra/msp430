#include<msp430FR5725.h>
#include"AT24C32.h"
#include"Delay.h"
#include "i2c.h"


/****************************************************************************
* ��    �ƣ�EepromRead
* ��    �ܣ���ȡ����
* ��ڲ�����buf:��ȡ���ݴ�ŵĵ�ַ
            len:Ҫ��ȡ�ĳ���
            ptr:EEPROM�洢λ��
* ���ڲ�����
* ˵    ������EEPROM����������ʹ��ǰ�����붨�����ҳд�ֽ��������Ҷ���EEPROM������
***************************************************************************/
void EepromRead(u8 *buf , u16 len , u16 ptr)
{
    u8 EeromAddr[2];
    EeromAddr[0] = ptr >> 8;    //��ַ��λ
    EeromAddr[1] = ptr & 0xff;  //��ַ��λ
    MI2C_Read24C32(EeromAddr[0] , EeromAddr[1] , buf , len);
}

/****************************************************************************
* ��    �ƣ�EepromWrite
* ��    �ܣ�д������
* ��ڲ�����buf:Ҫ���͵�����
            len:Ҫ���͵ĳ���
            ptr:EEPROM�洢λ��
* ���ڲ�����
* ˵    ����дEEPROM����������ʹ��ǰ�����붨�����ҳд�ֽ��������Ҷ���EEPROM������
***************************************************************************/
u8 EepromWrite(u8 *buf , u16 len , u16 ptr)
{
    u8 addTemp[EEP_ADDR_SIZE];
    u8 bufTemp[EEP_MAX_PAGE_SIZE] , i , j=0;
    u8 flowSize , flowLen;
    u16 sizeTemp , lenTemp = 0;
    
    if((ptr + len) > (EEP_MAX_ROM_SIZE - 1))   //EEPOM�������
        return 0;
    
    flowSize = ptr % EEP_MAX_PAGE_SIZE;
    if(flowSize)    // �������ҳ�����
    {
        flowLen = EEP_MAX_PAGE_SIZE - flowSize; //��ǰҳ��д����
        if(flowLen < len)//��д�����ݿ�ҳ
        {
            addTemp[0] = ptr >> 8;    //��ַ��λ
            addTemp[1] = ptr & 0xff;  //��ַ��λ
            for(i = 0;i < flowLen;i++)
            {
                bufTemp[i] = buf[i];
            }
            ptr += flowLen;         //�´ν�д��ĵ�ַ
            len -= flowLen;         //ʣ��δд�����ݵĳ���
            MI2C_Write24C32(addTemp[0] , addTemp[1] , bufTemp , flowLen);//����д�������
            sizeTemp = flowLen;
            EEP_WRITE_DELAY_TIME;
            lenTemp = lenTemp + sizeTemp;
        }
        else//��Ҫд������δ��ҳ
        {
            addTemp[0] = ptr >> 8;    //��ַ��λ
            addTemp[1] = ptr & 0xff;  //��ַ��λ
            for(i = 0;i < len;i++)
            {
                bufTemp[i] = buf[i];
            }
            MI2C_Write24C32(addTemp[0] , addTemp[1] , bufTemp , len);//����д�������
            sizeTemp = len;
            EEP_WRITE_DELAY_TIME;
            return (sizeTemp); //��Ϸ���
        }
    }
    while(len / EEP_MAX_PAGE_SIZE)   //ʣ��δд���ݳ����Դ�����ҳ����
    {
        addTemp[0] = ptr >> 8;    //��ַ��λ
        addTemp[1] = ptr & 0xff;  //��ַ��λ
        j = lenTemp;
        for(i = 0;i < EEP_MAX_PAGE_SIZE;i++)
        {
            bufTemp[i] = buf[j + i];
        }
        ptr += EEP_MAX_PAGE_SIZE;
        j += EEP_MAX_PAGE_SIZE;
        len -= EEP_MAX_PAGE_SIZE;
        MI2C_Write24C32(addTemp[0] , addTemp[1] , bufTemp , EEP_MAX_PAGE_SIZE );//����д�������
        sizeTemp = EEP_MAX_PAGE_SIZE;
        EEP_WRITE_DELAY_TIME;
        lenTemp = lenTemp + sizeTemp;
    }
    if(len)  //ʣ��δд���ݳ��Ȳ�����ҳ
    {
        addTemp[0] = ptr >> 8;    //��ַ��λ
        addTemp[1] = ptr & 0xff;  //��ַ��λ
        j = lenTemp;
        for(i = 0;i < len;i++)
        {
            bufTemp[i] = buf[j + i];
        }
        MI2C_Write24C32(addTemp[0] , addTemp[1] , bufTemp , len);//����д�������
        sizeTemp = len;
        EEP_WRITE_DELAY_TIME;
        lenTemp = lenTemp + sizeTemp;
    }
    return lenTemp;  //����д�����ݵ���Ŀ
    
}

