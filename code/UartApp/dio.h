#ifndef __DIO__
#define __DIO__

#include <avr/io.h>
#include <stdint.h>

/* ATmega328P / Arduino Uno
 * LED : PB5 (D13)
 * BTN : PB3 (D11) — input with INTERNAL PULL-UP (active LOW)
 */
#define LED_PORT   PORTB
#define LED_DDR    DDRB
#define LED_PINR   PINB
#define LED_PINN   PB5

#define BTN_PORT   PORTB
#define BTN_DDR    DDRB
#define BTN_PINR   PINB
#define BTN_PINN   PB3

void DIO_Init(void);
void DIO_Set_LED(uint8_t on);
void DIO_ToggleLED(void);
/* Returns 1 when PRESSED (active-LOW, debounced), else 0 */
uint8_t DIO_Read_Button(void);

#endif
