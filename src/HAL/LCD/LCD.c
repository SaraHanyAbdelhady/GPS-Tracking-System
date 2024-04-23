#include <stdio.h>
#include "../../../Headers/MCAL/GPIO/GPIO.h"
#include "../../../Services/Bit_Utilities"
#include "../../../Services/STD_TYPES"
#include "../../../Headers/HAL/LCD/LCD.h"

/*
 * Array of characters that stores the string to be printed on the LCD
 */
char str_distance[16];

/* 
 * Description : 
 * Control Port Direction : OUTPUT
 * Data Port Direction : OUTPUT
 * Delay of 1 second 
 * Initializing 8-bit mode
 * Delay of 1 second
 * Clear Command
 * Delay of 1 second
 * Turning cursor of LCD off
 * Delay of 1 second
 * Sending Enty mode set command
 */
void LCD_voidInit()
{
	Set_vPortDirection(DATA_PORT, CTRL_PORT_DIR);
	Set_vPortDirection(DATA_PORT, DATA_PORT_DIR);
	SystickWait(16000000);
	LCD_SendCommand(LCD_8_BIT_MODE_CMND);
	SystickWait(16000000);
	LCD_SendCommand(LCD_CLEAR_CMND);
	SystickWait(16000000);
	LCD_SendCommand(LCD_CURSOR_OFF_CMND);
	SystickWait(16000000);
	LCD_SendCommand(ENTRY_MODE_SET_CMND);
}


/* 
 * Description : 
 * Clears the RS Pin because a command is being sent
 * Clears the RW Pin to write on the LCD
 * Sends the command to the LCD
 * Sets ENABLE Pin high
 * delay of 2 seconds
 * Clears the ENABLE pin so that data is sent at the falling edge
 */
void LCD_SendCommand(u8 Data_Value)
{
	Set_vPinValue(CTRL_PORT, LCD_RS_PIN, PIN_LOW);
	Set_vPinValue(CTRL_PORT, LCD_RW_PIN, PIN_LOW);
	Set_vPortValue(CTRL_PORT, Data_Value);
	Set_vPinValue(CTRL_PORT, LCD_RS_PIN, PIN_HIGH);
	SystickWait(32000000);
	Set_vPinValue(CTRL_PORT, LCD_EN_PIN, PIN_LOW);
}


/* 
 * Description : 
 * Sets the RS Pin because data is being sent
 * Clears the RW Pin to write on the LCD
 * Sends the character to be displayed on the LCD
 * Sets ENABLE Pin high
 * delay of 2 seconds
 * Clears the ENABLE pin so that data is sent at the falling edge
 */
void LCD_voidSendData(u8 character)
{
	Set_vPinValue(CTRL_PORT, LCD_RS_PIN, PIN_HIGH);
	Set_vPinValue(CTRL_PORT, LCD_RW_PIN, PIN_LOW);
	Set_vPortValue(CTRL_PORT, character);
	Set_vPinValue(CTRL_PORT, LCD_RS_PIN, PIN_HIGH);
	SystickWait(32000000);
	Set_vPinValue(CTRL_PORT, LCD_EN_PIN, PIN_LOW);
}


/* 
 * Description : 
 * Sends each character in the string to be printed on the LCD 
 */
void LCD_voidSendString(char str[])
{
	u8 i = 0;
	while(str[i]!='\0')
	{
		LCD_voidSendData(str[i++]);
	}
}


/* 
 * Description : 
 * Converts the floating distance into a string and stores it in str_distance
 */
void ConvertFloatToStr(f32 distance)
{
	sprintf(str_distance, "Distance = %f", distance);
}


/* 
 * Description : 
 * Prints to the LCD the distance travelled from the starting point 
 * of the trajectory in the following format : 
 * "Distance = %f"
 */
void Print_Distance_To_LCD(f32 distance)
{
	char str[20];
	ConvertFloatToStr(f32);
	LCD_voidSendString(str_string);
}