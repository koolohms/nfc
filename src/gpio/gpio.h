/* gpio.h
*/

#define LOW     0
#define HIGH    1

#define GPIO_IRQ_PIN        6
#define GPIO_VEN_PIN        7       

#define GPIO_VEN_PIN_MASK   0b1000000   // GPIO VEN pin for GPIO pin 7
#define GPIO_IRQ_PIN_MASK   0b10000000  // GPIO IRQ pin for GPIO pin 6


void gpio_init(void);