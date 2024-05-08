#include <stdio.h>
#include "../../../Headers/MCAL/GPIO/GPIO.h"
#include "../../../Services/Bit_Utilities.h"
#include "../../../Services/STD_TYPES.h"
#include "../../../Headers/HAL/LCD/LCD.h"
#include "../../../Headers/MCAL/SYSTICK/Systick.h"
#include <string.h>
#include <stdint.h>

/*
 * Array of characters that stores the string to be printed on the LCD
 */
 
u8 str_distance[16];

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
	Systick_Wait(16000000);
	LCD_SendCommand(LCD_8_BIT_MODE_CMND);
	Systick_Wait(16000000);
	LCD_SendCommand(LCD_CLEAR_CMND);
	Systick_Wait(16000000);
	LCD_SendCommand(LCD_CURSOR_OFF_CMND);
	Systick_Wait(16000000);
	LCD_SendCommand(LCD_ENTRY_MODE_SET_CMND);
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
void LCD_SendCommand(char Data_Value)
{
	Set_vPinValue(CTRL_PORT, LCD_RS_PIN, PIN_LOW);
	Set_vPinValue(CTRL_PORT, LCD_RW_PIN, PIN_LOW);
	Set_vPortValue(CTRL_PORT, Data_Value);
	Set_vPinValue(CTRL_PORT, LCD_RS_PIN, PIN_HIGH);
	Systick_Wait(32000000);
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
void LCD_voidSendData(char character)
{
	Set_vPinValue(CTRL_PORT, LCD_RS_PIN, PIN_HIGH);
	Set_vPinValue(CTRL_PORT, LCD_RW_PIN, PIN_LOW);
	Set_vPortValue(CTRL_PORT, character);
	Set_vPinValue(CTRL_PORT, LCD_RS_PIN, PIN_HIGH);
	Systick_Wait(32000000);
	Set_vPinValue(CTRL_PORT, LCD_EN_PIN, PIN_LOW);
}


/* 
 * Description : 
 * Sends each character in the string to be printed on the LCD 
 */
void LCD_voidSendString(char *str)
{
	while(*str)
	{
		LCD_voidSendData(*str);
		str++;
	}
}


/* 
 * Description : 
 * Converts the floating distance into a string and stores it in str_distance
 */
void ConvertFloatToStr(f32 distance,char *str)
{
	distance = sprintf(str, "Distance = %f", distance);
}


/* 
 * Description : 
 * Prints to the LCD the distance travelled from the starting point 
 * of the trajectory in the following format : 
 * "Distance = %f"
 */
void Print_Distance_To_LCD(f32 distance)
{
	char str_distance[20]={0};
	ConvertFloatToStr(distance, str_distance);
	LCD_voidSendString(str_distance);
}



//	move cursor to desired position
void LCD_voidGoToXYPos(u8 copy_u8XPos,u8 copy_u8YPos)
{
    u8 Local_u8Address = 0;
    if((copy_u8XPos== 0 || copy_u8XPos== 1) && (copy_u8YPos >= 0 && copy_u8YPos<=15))
    {
        switch(copy_u8XPos)
        {
        case 0:
            Local_u8Address = copy_u8YPos;
            break;
        case 1:
            Local_u8Address = copy_u8YPos+0x40;
            break;
        default: /**< Return Error state */break;
        }
        /**
         *  To move the LCD to the calculated address you should SET_BIT(DDRAM,DB7)
         *  There are many way to do this :
         *      1)Local_u8Address + 128
         *      2)Local_u8Address|(1<<8)
         *      3)SET_BIT(Local_u8Address,8)
         *  */
        LCD_SendCommand(Local_u8Address+128);
    }
    else
    {
        /**< Return Error state */
    }
}





