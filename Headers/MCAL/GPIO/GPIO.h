#ifndef GPIO_H
#define GPIO_H

#include "../../../Services/STD_TYPES.h"

#define PIN_LOW 		0
#define PIN_INPUT 	0
#define PIN_HIGH 		1
#define PIN_OUTPUT 	1
#define Port_INPUT 	0x00
#define Port_OUTPUT 0xFF

void PortF_Init(void);
void PortA_Init(void);
void PortB_Init(void);
void PortD_Init(void);
void PortE_init(void);

u8 Set_vPinValue(u8 Port_ID,u8 Pin_Number,u8 Pin_Value);
u8 Set_vPortValue(u8 port_name, u8 PortValue);
u8 Get_u8PinValue(u8 port_name,u8 pin_number, u8 pin_direction);
u8 Get_Port_Value(u8 Port_ID);

#endif
