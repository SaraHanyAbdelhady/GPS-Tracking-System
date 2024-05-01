#ifndef GPIO.H
#define GPIO.H


#define PIN_LOW 0
#define PIN_INPUT 0
#define PIN_HIGH 1
#define PIN_OUTPUT 1
#define Port_INPUT 0x00
#define Port_OUTPUT 0xFF

void PortF_Init();
void PortA_Init();
void PortB_Init();
void PortD_Init();
void PortE_Init();
#endif