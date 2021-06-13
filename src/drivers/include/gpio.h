/* gpio.h
*/

#ifndef GPIOS_H
#define GPIOS_H

#define LOW     0
#define HIGH    1

#define LEVEL_LOW   0
#define LEVEL_HIGH  1
#define EDGE_LOW    2
#define EDGE_HIGH   3

#define GPIO_IRQ_PIN        6
#define GPIO_VEN_PIN        7       

void gpios_init(void);
extern void gpio_Init( void );
extern void gpio_SetValue( uint32_t bitPosi, uint32_t bitVal );
extern uint8_t gpio_GetValue( uint32_t bitPosi);
extern void gpio_SetDir( uint32_t bitPosi, uint32_t dir );

#endif  // GPIOS_H