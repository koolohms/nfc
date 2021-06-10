/* gpio.c
*/

#include <stdlib.h>
#include <stdio.h>
#include "gpio.h"
#include "pico/stdlib.h"


void gpios_init(void){

    // Enable pins
    gpio_init(PICO_DEFAULT_I2C_SCL_PIN);
    gpio_init(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_init(GPIO_VEN_PIN);
    gpio_init(GPIO_IRQ_PIN);

    /***      I2C     ***/
    gpio_set_input_enabled(PICO_DEFAULT_I2C_SCL_PIN, true);     // Enable input
    gpio_set_input_enabled(PICO_DEFAULT_I2C_SCL_PIN, true);     // Enable input
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C); // Set pin 6 (GPIO4) to I2C SDA
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C); // Set pin 7 (GPIO5) to I2C SCL
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);     // Enable pull-up on SDA pin
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);     // Enable pull-up on SCL pin
    

    /***      NFC     ***/
    // NFC VEN PIN
    gpio_set_dir(GPIO_VEN_PIN, true);   // Set to output

    // NFC IRQ PIN --> NOT REQUIRED
/*     gpio_set_input_enabled(GPIO_IRQ_PIN, true);     // Enable input
    gpio_set_dir(GPIO_IRQ_PIN, false);              // Set to input
    gpio_set_irq_enabled(GPIO_IRQ_PIN, true);       // Enable IRQ */
} 
