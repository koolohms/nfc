/* gpio.c
*/

#include <stdlib.h>
#include <stdio.h>
#include "gpio.h"
#include "pico/stdlib.h"


void gpios_init(void){
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

    // NFC VEN PIN
    gpio_set_dir(GPIO_VEN_PIN, true);   // Set to output

    // NFC IRQ PIN
    gpio_set_dir(GPIO_IRQ_PIN, false);  // Set to input
} 
