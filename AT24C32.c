#include<msp430FR5725.h>
#include"AT24C32.h"
#include"Delay.h"
#include "i2c.h"


/****************************************************************************
* 名    称：EepromRead
* 功    能：读取数据
* 入口参数：buf:读取数据存放的地址
            len:要读取的长度
            ptr:EEPROM存储位置
* 出口参数：
* 说    明：读EEPROM处理函数，在使用前，必须定义最大页写字节数，并且定义EEPROM的容量
***************************************************************************/
void EepromRead(u8 *buf , u16 len , u16 ptr)
{
    u8 EeromAddr[2];
    EeromAddr[0] = ptr >> 8;    //地址高位
    EeromAddr[1] = ptr & 0xff;  //地址地位
    MI2C_Read24C32(EeromAddr[0] , EeromAddr[1] , buf , len);
}

/****************************************************************************
* 名    称：EepromWrite
* 功    能：写入数据
* 入口参数：buf:要发送的数据
            len:要发送的长度
            ptr:EEPROM存储位置
* 出口参数：
* 说    明：写EEPROM处理函数，在使用前，必须定义最大页写字节数，并且定义EEPROM的容量
***************************************************************************/
u8 EepromWrite(u8 *buf , u16 len , u16 ptr)
{
    u8 addTemp[EEP_ADDR_SIZE];
    u8 bufTemp[EEP_MAX_PAGE_SIZE] , i , j=0;
    u8 flowSize , flowLen;
    u16 sizeTemp , lenTemp = 0;
    
    if((ptr + len) > (EEP_MAX_ROM_SIZE - 1))   //EEPOM溢出保护
        return 0;
    
    flowSize = ptr % EEP_MAX_PAGE_SIZE;
    if(flowSize)    // 如果不在页的起点
    {
        flowLen = EEP_MAX_PAGE_SIZE - flowSize; //当前页可写长度
        if(flowLen < len)//所写的数据跨页
        {
            addTemp[0] = ptr >> 8;    //地址高位
            addTemp[1] = ptr & 0xff;  //地址地位
            for(i = 0;i < flowLen;i++)
            {
                bufTemp[i] = buf[i];
            }
            ptr += flowLen;         //下次将写入的地址
            len -= flowLen;         //剩余未写入数据的长度
            MI2C_Write24C32(addTemp[0] , addTemp[1] , bufTemp , flowLen);//本次写入的数据
            sizeTemp = flowLen;
            EEP_WRITE_DELAY_TIME;
            lenTemp = lenTemp + sizeTemp;
        }
        else//所要写的数据未跨页
        {
            addTemp[0] = ptr >> 8;    //地址高位
            addTemp[1] = ptr & 0xff;  //地址地位
            for(i = 0;i < len;i++)
            {
                bufTemp[i] = buf[i];
            }
            MI2C_Write24C32(addTemp[0] , addTemp[1] , bufTemp , len);//本次写入的数据
            sizeTemp = len;
            EEP_WRITE_DELAY_TIME;
            return (sizeTemp); //完毕返回
        }
    }
    while(len / EEP_MAX_PAGE_SIZE)   //剩余未写数据长度仍大于整页长度
    {
        addTemp[0] = ptr >> 8;    //地址高位
        addTemp[1] = ptr & 0xff;  //地址地位
        j = lenTemp;
        for(i = 0;i < EEP_MAX_PAGE_SIZE;i++)
        {
            bufTemp[i] = buf[j + i];
        }
        ptr += EEP_MAX_PAGE_SIZE;
        j += EEP_MAX_PAGE_SIZE;
        len -= EEP_MAX_PAGE_SIZE;
        MI2C_Write24C32(addTemp[0] , addTemp[1] , bufTemp , EEP_MAX_PAGE_SIZE );//本次写入的数据
        sizeTemp = EEP_MAX_PAGE_SIZE;
        EEP_WRITE_DELAY_TIME;
        lenTemp = lenTemp + sizeTemp;
    }
    if(len)  //剩余未写数据长度不足整页
    {
        addTemp[0] = ptr >> 8;    //地址高位
        addTemp[1] = ptr & 0xff;  //地址地位
        j = lenTemp;
        for(i = 0;i < len;i++)
        {
            bufTemp[i] = buf[j + i];
        }
        MI2C_Write24C32(addTemp[0] , addTemp[1] , bufTemp , len);//本次写入的数据
        sizeTemp = len;
        EEP_WRITE_DELAY_TIME;
        lenTemp = lenTemp + sizeTemp;
    }
    return lenTemp;  //返回写入数据的数目
    
}

