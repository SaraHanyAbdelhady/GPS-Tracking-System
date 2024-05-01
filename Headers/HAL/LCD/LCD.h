#include "../../MCAL/GPIO/GPIO.h"
#include "../../../Services/STD_TYPES.h"

#define LCD_INITIALIZATION_8_BIT_MODE			8


/*************************************** CONTROL PINS MACROS ***************************************/
#define CTRL_PORT					'B'	
#define CTRL_PORT_DIR				0xFF
#define LCD_RS_PIN					1
#define LCD_RW_PIN					2
#define LCD_EN_PIN					3
/*************************************** DATA PINS MACROS ******************************************/
#define DATA_PORT					'E'
#define DATA_PORT_DIR				0xFF
#define LCD_D0_PIN					0
#define LCD_D1_PIN					1
#define LCD_D2_PIN					2
#define LCD_D3_PIN					3
#define LCD_D4_PIN					4
#define LCD_D5_PIN					5
#define LCD_D6_PIN					6
#define LCD_D7_PIN					7
/************************************** LCD COMMANDS MACROS *****************************************/
#define LCD_8_BIT_MODE_CMND 			0x38
#define LCD_CLEAR_CMND					0x01
#define LCD_CURSOR_OFF_CMND				0x0C
#define LCD_ENTRY_MODE_SET_CMND			0x06
/*********************************** LCD FUNCTIONS PROTOTYPES **************************************/
void LCD_voidInit();
void LCD_voidSendData(u8 character);
void LCD_voidSendString(u8 str[]);
void LCD_SendCommand(u8 Data_Value);
void ConvertFloatToStr(f32 distance);
void Print_Distance_To_LCD(f32 distance);