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

#endif  // GPIOS_H