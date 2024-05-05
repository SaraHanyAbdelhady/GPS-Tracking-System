#ifndef EEPROM_H
#define EEPROM_H

#include "../../../Services/STD_TYPES.h"

void EEPROM_Init(void);
void eeprom_write(int data,u8 addr,u8 blk);
int eeprom_read(u8 addr,u8 blk);




#endif