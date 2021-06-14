/* gpio.c
*/

#include <stdint.h>
#include "pico/stdlib.h"
#include "tool.h"
#include "driver_config.h"
#include "gpio.h"

void gpio_Init(void){
    gpios_init();
}

void gpios_init(void){

    // Enable pins
    gpio_init(PICO_DEFAULT_I2C_SCL_PIN);
    gpio_init(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_init(PIN_VEN);
    gpio_init(PIN_IRQ);

    /***      I2C     ***/
    gpio_set_input_enabled(PICO_DEFAULT_I2C_SCL_PIN, true);     // Enable input
    gpio_set_input_enabled(PICO_DEFAULT_I2C_SCL_PIN, true);     // Enable input
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C); // Set pin 6 (GPIO4) to I2C SDA
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C); // Set pin 7 (GPIO5) to I2C SCL
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);     // Enable pull-up on SDA pin
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);     // Enable pull-up on SCL pin
    

    /***      NFC     ***/
    // NFC VEN PIN
    gpio_set_dir(PIN_VEN, true);   // Set to output

    // NFC IRQ PIN
    gpio_set_input_enabled(PIN_IRQ, true);     // Enable input
    gpio_set_dir(PIN_IRQ, false);              // Set to input

    #ifdef  DEBUG
    printf("GPIO:   VEN pin direction = %d\n", gpio_get_dir(PIN_VEN));
    printf("GPIO:   IRQ status = %d", gpio_get(PIN_IRQ));
    #endif  // DEBUG
} 

void gpio_SetValue( uint32_t bitPosi, uint32_t bitVal )
{
	//Chip_GPIO_SetPinState(LPC_GPIO, portNum, bitPosi, bitVal);
    gpio_put(bitPosi, bitVal);
}

uint8_t gpio_GetValue( uint32_t bitPosi)
{
	//return Chip_GPIO_GetPinState(LPC_GPIO, portNum, bitPosi);
    return gpio_get(bitPosi);
}

void gpio_SetDir( uint32_t bitPosi, uint32_t dir )
{
	//Chip_GPIO_SetDir(LPC_GPIO, portNum, 1<<bitPosi, dir);
    gpio_set_dir(bitPosi, dir);
}