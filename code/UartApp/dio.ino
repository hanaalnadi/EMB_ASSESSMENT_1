#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "dio.h"

/* Debounce params */
#define DEBOUNCE_MS   20
#define SAMPLE_COUNT  3

void DIO_Init(void)
{
    /* LED as output, start OFF */
    LED_DDR  |=  (1 << LED_PINN);
    LED_PORT &= ~(1 << LED_PINN);

    /* Button as input, enable internal pull-up */
    BTN_DDR  &= ~(1 << BTN_PINN);
    BTN_PORT |=  (1 << BTN_PINN);
}

void DIO_Set_LED(uint8_t on)
{
    if (on)  LED_PORT |=  (1 << LED_PINN);
    else     LED_PORT &= ~(1 << LED_PINN);
}

void DIO_ToggleLED(void)
{
    LED_PORT ^= (1 << LED_PINN);
}

static uint8_t Raw_Button(void)
{
    /* Active-LOW: pressed -> 0 on the pin */
    return ((BTN_PINR & (1 << BTN_PINN)) == 0) ? 1u : 0u;
}

uint8_t DIO_Read_Button(void)
{
    uint8_t stable = Raw_Button();
    uint8_t count  = 0;

    while (count < SAMPLE_COUNT)
    {
        _delay_ms(DEBOUNCE_MS);
        uint8_t s = Raw_Button();
        if (s == stable) count++;
        else { stable = s; count = 0; }
    }
    return stable;
}
