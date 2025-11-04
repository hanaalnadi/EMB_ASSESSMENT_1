#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include "dio.h"
#include "Uart.h"   

#define POLL_MS 50


int main(void)
{
    DIO_Init();
    Uart_Init();

    /* INSURE RATE IS CORRECT */
    Uart_Set_BaudRate(9600);  

    uint8_t last = DIO_Read_Button();

    for (;;)
    {
        /* Button state change detection */
        uint8_t now = DIO_Read_Button();
        if (now != last)
        {
        /* Button logic */
            last = now;
            if (now) Send_String("button_pressed\r\n");
            else     Send_String("button_released\r\n");
        }

        /* input data detection */
        while (Uart_Data_Availablity())
        {
          /* LED logic */
            uint8_t c = Uart_Read_Data();

            if (c == '1') {
                DIO_Set_LED(1);
                Send_String("OK\r\n");
            } else if (c == '0') {
                DIO_Set_LED(0);
                Send_String("OK\r\n");
            } else if (c == '\r' || c == '\n' || c == ' ' || c == '\t') {
                /* ignore */
            } else {
                Send_String("ERR\r\n");
            }
        }

        /* idle break for smoothing out */
        _delay_ms(POLL_MS);
    }
}
