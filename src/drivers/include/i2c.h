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

#include <stdint.h>

extern void i2c_Init(void);
extern uint8_t i2c_Read(uint8_t add, uint8_t *pRsp, uint16_t Rsp_size);
extern uint8_t i2c_Write(uint8_t add, uint8_t *pCmd, uint16_t Cmd_size);