/*
*         Copyright (c), NXP Semiconductors Caen / France
*
*                     (C)NXP Semiconductors
*       All rights are reserved. Reproduction in whole or in part is
*      prohibited without the written consent of the copyright owner.
*  NXP reserves the right to make changes without notice at any time.
* NXP makes no warranty, expressed, implied or statutory, including but
* not limited to any implied warranty of merchantability or fitness for any
*particular purpose, or that the use will not infringe any third party patent,
* copyright or trademark. NXP must not be liable for any loss or damage
*                          arising from its use.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pico.h>
#include <time.h>
#include "include/tml.h"
#include "include/driver.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "../gpio/gpio.h"
#include "driver.h"
#include "tool.h"
#include "NxpNci.h"


static uint8_t tml_Init(void) {
	
	//gpios_init(); already initialized
	//printf("tml initialized\n");
    
	return PICO_OK;
}

static uint8_t tml_Reset(void) {
	/* Apply VEN reset */
    gpio_put(GPIO_VEN_PIN, HIGH);
	sleep_ms(10);
	//PRINTF("VEN Pin State: %d\n", gpio_get(GPIO_VEN_PIN));
	gpio_put(GPIO_VEN_PIN, LOW);
	sleep_ms(10);
	//PRINTF("VEN Pin State: %d\n", gpio_get(GPIO_VEN_PIN));
    gpio_put(GPIO_VEN_PIN, HIGH);
	//sleep_ms(10);
	//PRINTF("VEN Pin State: %d\n", gpio_get(GPIO_VEN_PIN));


	//printf("tml reset\n");

	return PICO_OK;
}

static uint8_t tml_Tx(uint8_t *pBuff, uint16_t buffLen) {

    // Attempt transmission twice, if second attempt fails then flag error
    if (i2c_write_blocking(i2c0, BOARD_NXPNCI_I2C_ADDR, pBuff, buffLen, false) != PICO_OK)
    {
        sleep_ms(10);
        if (i2c_write_blocking(i2c0, BOARD_NXPNCI_I2C_ADDR, pBuff, buffLen, false) != PICO_OK)
        {
            return PICO_ERROR_GENERIC;
        }
    }

    return PICO_OK;
}

static uint8_t tml_Rx(uint8_t *pBuff, uint16_t buffLen, uint16_t *pBytesRead) {
	uint8_t ret;

	ret = i2c_read_blocking(i2c0, BOARD_NXPNCI_I2C_ADDR, pBuff, 3, false);
    NCI_PRINT_BUF("NCI << ", pBuff, 3);

	if (ret != PICO_ERROR_GENERIC) {
		if (pBuff[2] != 0) {
			ret = i2c_read_blocking(i2c0, BOARD_NXPNCI_I2C_ADDR, &pBuff[3], pBuff[2], false);
			if (ret != PICO_ERROR_GENERIC) {
				*pBytesRead = pBuff[2] + 3;
			} else {
				*pBytesRead = 0;
			}
		} else {
			*pBytesRead = 3;
		}
	} else {
		*pBytesRead = 0;
	}

	return ret;

}

static uint8_t tml_WaitForRx(uint16_t timeout) {
	if (timeout == 0) {
		while (gpio_get(GPIO_IRQ_PIN) == LOW);
	} else {
		int16_t to = timeout;
		while (gpio_get(GPIO_IRQ_PIN) == LOW) {
			sleep_ms(10);
			to -= 10;
			if (to <= 0) return PICO_ERROR_GENERIC;
		}
	}
	return PICO_OK;
}

void tml_Connect(void) {
	tml_Init();
	tml_Reset();
}

void tml_Disconnect(void) {
	return;
}

void tml_Send(uint8_t *pBuffer, uint16_t BufferLen, uint16_t *pBytesSent) {
	if(tml_Tx(pBuffer, BufferLen) == PICO_ERROR_TIMEOUT)
	{
		*pBytesSent = 0;
	}
	else
	{
		*pBytesSent = BufferLen;
	}
}

void tml_Receive(uint8_t *pBuffer, uint16_t BufferLen, uint16_t *pBytes,
		uint16_t timeout) {
	if (tml_WaitForRx(timeout) == PICO_ERROR_TIMEOUT){
		//printf("Timeout\n");
		*pBytes = 0;
	}
	else
		tml_Rx(pBuffer, BufferLen, pBytes);
		//printf("Received\n");
}

