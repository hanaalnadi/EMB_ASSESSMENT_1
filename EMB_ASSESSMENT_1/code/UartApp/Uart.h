#ifndef __UART__
#define __UART__

#if !defined(__AVR_ATmega328P__)
  #include <avr/iom328p.h>
#endif

#include <avr/io.h>
#include <stdint.h>


void Uart_Init(void);

void Uart_Set_BaudRate(uint16_t BaudRate);

void Uart_Send_Char(uint8_t DataByte);

unsigned char Uart_Read_Data(void);

unsigned char Uart_Data_Availablity(void);

void Uart_Send_String(char DataString[], unsigned char Size);

static void Send_String(const char* s);

#endif
