#include "Uart.h"

#ifndef F_CPU
  #define F_CPU 16000000UL
#endif

/* insuring union baudrate */
#ifdef baud
  #undef baud
#endif


static void _uart_set_ubrr(uint32_t BaudRate)
{
    UCSR0A &= ~(1 << U2X0);

    uint32_t ubrr = (F_CPU / (16UL * BaudRate)) - 1UL;
    UBRR0H = (uint8_t)((ubrr >> 8) & 0xFF);
    UBRR0L = (uint8_t)(ubrr & 0xFF);

    /* 8 data bits, 1 stop bit, no parity (8N1) */
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void Uart_Init(void)
{
    Uart_Set_BaudRate(9600);
    /* Enable RX TX */
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);
}

void Uart_Set_BaudRate(uint16_t BaudRate)
{
    if (BaudRate == 0) BaudRate = 9600;
    _uart_set_ubrr((uint32_t)BaudRate);
}

void Uart_Send_Char(uint8_t DataByte)
{
    /* Wait until data register empty */
    while ((UCSR0A & (1 << UDRE0)) == 0) { }
    UDR0 = DataByte;
}

unsigned char Uart_Read_Data(void)
{
    /* Wait until data received */
    while ((UCSR0A & (1 << RXC0)) == 0) { }
    return UDR0;
}

unsigned char Uart_Data_Availablity(void)
{
    return (UCSR0A & (1 << RXC0)) ? 1u : 0u;
}

void Uart_Send_String(char DataString[], unsigned char Size)
{
    /* Send either Size bytes or until NUL terminator, whichever comes first */
    unsigned char i = 0;
    while (i < Size && DataString[i] != '\0')
    {
        Uart_Send_Char((uint8_t)DataString[i]);
        ++i;
    }
}

static void Send_String(const char* s)
{
    while (*s) { Uart_Send_Char((uint8_t)*s++); }
}
