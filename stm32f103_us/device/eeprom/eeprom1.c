#include "eeprom1.h"
//#include "para.h"

void Eeprom_WriteByte(uint16_t pWriteAddr, uint8_t *pData, uint16_t plen)
{
    uint32_t WriteAddr;
    uint32_t TimeOut = 0xffffff;
    if(pWriteAddr > EEPROM_BYTE_SIZE)
    {
        return;
    }
    WriteAddr = EEPROM_BASE_ADDR + pWriteAddr;
    HAL_FLASH_Unlock();
    //DIS_INT;
//    *(uint8_t *)WriteAddr = pData;
	while(plen--)
    {
        *(uint8_t *)WriteAddr++ = *pData++;
        while(__HAL_FLASH_GET_FLAG(FLASH_FLAG_BSY) && TimeOut > 0)
        {
            TimeOut--;
        }
    }
    
    HAL_FLASH_Lock();
    //EN_INT;       
}


void Eeprom_ReadByte(uint16_t pReadAddr, uint8_t *pReadData, uint16_t plen)
{
    uint32_t ReadAddr;
    if(pReadAddr > EEPROM_BYTE_SIZE)
    {
        return;
    }
    ReadAddr = EEPROM_BASE_ADDR + pReadAddr;
    //DIS_INT;
//    *pReadData = *(uint8_t *)ReadAddr;
	while(plen--)
    {
        *pReadData++ = *(uint8_t *)ReadAddr++;
    }
    //EN_INT;
}
