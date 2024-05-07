#include "../../../Services/Bit_Utilities.h"
#include "../../../Services/STD_TYPES.h"
#include  "../../../Services/tm4c123gh6pm.h"
#include  "../../../Headers/MCAL/SYSTICK/Systick.h"




int EEPROM_Start(void){
    SYSCTL_RCGCEEPROM_R = 0x01; //enable eeprom clock 
    delay(6); // delay 6 cycles
    while(EEPROM_EEDONE_R & EEPROM_EEDONE_WORKING); // wait for eeprom to finish its power-on initialization
    if((EEPROM_EESUPP_R & EEPROM_EESUPP_ERETRY) | (EEPROM_EESUPP_R & EEPROM_EESUPP_PRETRY))
		{
			return -1;
		} // return an error if any of these two bits (erase retry or program retry) are set which means that theEEPROM was unable to recover its state

        SYSCTL_SREEPROM_R = SYSCTL_SREEPROM_R0; // Reset the EEPROM_0 module DOES IT CLEAR THE DATA ???
        SYSCTL_SREEPROM_R = 0; // This step ensures that the EEPROM module is no longer in a reset state.
        delay(6);

        while(EEPROM_EEDONE_R & EEPROM_EEDONE_WORKING); // when working=0 continue

        if((EEPROM_EESUPP_R & EEPROM_EESUPP_ERETRY) | (EEPROM_EESUPP_R & EEPROM_EESUPP_PRETRY))
		{
			return -1;
		} // return an error if any of these two bits are set which means that theEEPROM was unable to recover its state
		
		return 1; // initialization is completed without any errors
}

void eeprom_error_recovery(void) // NEEDS MORE INVESTIGATION
{
	EEPROM_EESUPP_R = EEPROM_EESUPP_START; // start erase
	while(EEPROM_EEDONE_R & EEPROM_EEDONE_WORKING);
}

int EEPROM_Init(void) // if init fails should we reinit or not ????
{
	int flag=0;
	flag = EEPROM_Start();
	if(flag)
		; // no errors initialzation was successful
	else
		eeprom_error_recovery(); // error

return flag;
}

void eeprom_write(f32 data,u32 addr) // ???? uinnt8_t mkan kol u8 ?????
{
	while(EEPROM_EEDONE_R & EEPROM_EEDONE_WORKING); //	checking not busy
	EEPROM_EEBLOCK_R = addr >>4;										//	shifting for keeping in the same block number
	EEPROM_EEOFFSET_R = (addr& 0xF);				 //offset within the block
	EEPROM_EERDWR_R = data; 									//data written 
	while(EEPROM_EEDONE_R & EEPROM_EEDONE_WORKING);
}

f32 eeprom_read(u32 addr) // hl el data htb2a saved mn mara l mara ??
{
	while(EEPROM_EEDONE_R & EEPROM_EEDONE_WORKING);
	f32 data;
	EEPROM_EEBLOCK_R = addr >>4;//Block number
	EEPROM_EEOFFSET_R = (addr& 0xF); //offset within the block
	data = EEPROM_EERDWR_R;
	return data;
}





