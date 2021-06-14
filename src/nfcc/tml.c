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

#include "driver_config.h"
#include <stdint.h>
#include "types.h"
#include "gpio.h"
#include "i2c.h"
#include "tool.h"
#include "pico.h"


static uint8_t tml_Init(void) {
	
	/* Configure GPIO for IRQ pin */
	gpio_SetDir(PIN_IRQ, SET_IN);
	/* Configure GPIO for VEN pin */
	gpio_SetDir(PIN_VEN, SET_OUT);
	return SUCCESS;
}

static uint8_t tml_Reset(void) {
	/* Apply VEN reset */
	gpio_SetValue(PIN_VEN, HIGH);
	Sleep(10);
	gpio_SetValue(PIN_VEN, LOW);
	Sleep(10);
	gpio_SetValue(PIN_VEN, HIGH);
	Sleep(10);
	return SUCCESS;
}

static uint8_t tml_Tx(uint8_t *pBuff, uint16_t buffLen) {

    if (i2c_Write(BOARD_NXPNCI_I2C_ADDR, pBuff, buffLen) != SUCCESS)
    {
    	Sleep(10);
    	if(i2c_Write(BOARD_NXPNCI_I2C_ADDR, pBuff, buffLen) != SUCCESS)
    	{
    		return ERROR;
    	}
    }
	return SUCCESS;
}

static uint8_t tml_Rx(uint8_t *pBuff, uint16_t buffLen, uint16_t *pBytesRead) {
	uint8_t ret;

	ret = i2c_Read(BOARD_NXPNCI_I2C_ADDR, pBuff, 3);
	if (ret == SUCCESS) {
		if (pBuff[2] != 0) {
			ret = i2c_Read(BOARD_NXPNCI_I2C_ADDR, &pBuff[3], pBuff[2]);
			if (ret == SUCCESS) {
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
		while ((gpio_GetValue(PIN_IRQ) == LOW));
	} else {
		int16_t to = timeout;
		while ((gpio_GetValue(PIN_IRQ) == LOW)) {
			Sleep(10);
			to -= 10;
			if (to <= 0) return ERROR;
		}
	}
	return SUCCESS;
}

void tml_Connect(void) {
	tml_Init();
	tml_Reset();
}

void tml_Disconnect(void) {
	return;
}

void tml_Send(uint8_t *pBuffer, uint16_t BufferLen, uint16_t *pBytesSent) {
	if(tml_Tx(pBuffer, BufferLen) == ERROR)
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
		*pBytes = 0;
	}
	else
		tml_Rx(pBuffer, BufferLen, pBytes);
}

