#ifndef EEPROM_H
#define EEPROM_H

#include "../../../Services/STD_TYPES.h"

#define EEPROM_START_ADDR 	0x2000  // Start address of EEPROM emulation in flash memory
#define EEPROM_SIZE       	1024    // EEPROM size in bytes (adjust according to your device)


void EEPROM_Init(void);
void eeprom_write(f32 data,u32 addr);
f32 eeprom_read(u32 addr);




#endif
