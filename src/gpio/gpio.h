/* gpio.h
*/

#define LOW     0
#define HIGH    1

#define GPIO_IRQ_PIN        6
#define GPIO_VEN_PIN        7       

#define GPIO_VEN_PIN_MASK   0x80  // GPIO VEN pin for GPIO pin 7
#define GPIO_IRQ_PIN_MASK   0x81  // GPIO IRQ pin for GPIO pin 6


void gpios_init(void);