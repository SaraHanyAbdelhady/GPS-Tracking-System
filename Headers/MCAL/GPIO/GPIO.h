#ifndef GPIO.H
#define GPIO.H


#define PIN_LOW 0
#define PIN_INPUT 0
#define PIN_HIGH 1
#define PIN_OUTPUT 1
#define Port_INPUT 0x00
#define Port_OUTPUT 0xFF

u8 Init_Port(u8 Port_ID);
u8 Write_PIN_value(u8 Port_ID,u8 Pin_Number,u8 Pin_Value);
u8 Set_Port_Direction(u8 Port_ID,u8 Port_Direction);
u8 Get_Port_Value(u8 Port_ID);
u8 Set_vPinDirection(u8 port_name,u8 pin_number, u8 pin_direction);
u8 Get_u8PinValue(u8 port_name,u8 pin_number, u8 pin_direction);
u8 Set_vPortValue(u8 port_name, u8 PortValue);
u8 Toggle_vPinValue(u8 port_name,u8 pin_number);

#endif