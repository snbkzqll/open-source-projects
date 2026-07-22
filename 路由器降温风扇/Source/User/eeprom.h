#ifndef HK32_EEPROM_H_
#define HK32_EEPROM_H_

/*
HK32F030MF4P6 EEPROM 读写操作
*/

#include "main.h"

// EEPROM开始地址
#define  HK32F030M_EE_BEGIN    (0x0C000000ul)     
// EEPROM结束地址
#define  HK32F030M_EE_END      (0x0C0001C0ul)     
// EEPROM空间大小
#define  HK32F030M_EE_SIZE     (448)      


/**************************************************************************************************
* @functioin     EEPROM_WriteByte
* @brief         根据指定的偏移地址将数据写入EEPROM
* @param         offset:   要写入数据的目标地址,是基于EEPROM起始地址的偏移量 0<=address< HK32F030M_EE_SIZE
* @param         data_in:   要写入的数据
* @return        0 写入失败      1 写入成功
* @example       ALR_WriteByte(2,0x45);  是将数据写入到HK32F030M_EE_BEGIN+5的地址,如果写入成功则返
*                回1, 否则返回0
**************************************************************************************************/
void EEPROM_WriteByte(uint32_t offset, uint8_t data_in)
{
    FLASH_Unlock();
    EEPROM_EraseByte(offset+HK32F030M_EE_BEGIN);
    EEPROM_ProgramByte(offset+HK32F030M_EE_BEGIN, data_in);
    FLASH_Lock();
    
}

/**************************************************************************************************
* @functioin     EERPOM_ReadByte
* @brief         根据指定的偏移地址将数据从EEPROM读出
* @param         offset:   要读取数据的目标地址,是基于EEPROM起始地址的偏移量0<=address< HK32F030M_EE_SIZE
* @param         data_out:  读出数据的缓存变量指针
* @return        0 读取失败      1 读取成功
* @example       uint8_t dataR; 
*                ALR_ReadByte(2,&dataR);  
*                是将数据从地址HK32F030M_EE_BEGIN+5读出,如果读出成功则返
*                回1, 否则返回0
**************************************************************************************************/
void EERPOM_ReadByte(uint32_t offset,uint8_t *data_out)
{
    *data_out = (*((uint8_t *)(offset + HK32F030M_EE_BEGIN)));
}

#endif
