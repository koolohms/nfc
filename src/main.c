/* 
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bsp/board.h"
#include "tusb.h"
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "hardware/clocks.h"
#include "hardware/structs/pll.h"
#include "hardware/structs/clocks.h"
#include "led.h"
#include "tusb_config.h"
#include "usb_helper.h"
#include "test.h"
#include "nfc_task.h"
#include "ndef_message_setup.h"
#include "gpio.h"
#include "i2c.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

#define TRUE 1
#define FALSE 0

uint8_t received = FALSE;

void vUSBTask(void* pvParameters);
void vLEDTask(void* pvParameters);
void vNFCTask(void* pvParameters);


/*------------- MAIN -------------*/
int main(void)
{
  // Initialization
  stdio_init_all();
  board_init();             // Initialize the board for led and uart
  gpios_init();             // Initialize GPIOs

  i2c_Init();  
  tusb_init();            // Initialize TinyUSB

  // Create RTOS handles
  BaseType_t xReturned;

  TaskHandle_t xUSBHandle = NULL;
  TaskHandle_t xLEDHandle = NULL;
  TaskHandle_t xNFCHandle = NULL;

  // Store the handle
   xReturned = xTaskCreate(
    vUSBTask,         // Pointer to function that implements the task
    "USB Task",       // Not used by FreeRTOS. Mostly for debugging.
    512,             // Stack size in words (not bytes)
    NULL,             // Value to pass into the task function
    tskIDLE_PRIORITY + 1,   // Task priority
    &xUSBHandle             // Handle to pass out to the task being created
  );
 

  xReturned = xTaskCreate(
    vLEDTask,
    "LED Task",
    512,
    NULL,
    tskIDLE_PRIORITY + 1,
    &xLEDHandle
  );

  xReturned = xTaskCreate(
    vNFCTask,
    "NFC Task",
    512,
    NULL,
    tskIDLE_PRIORITY + 1,
    &xNFCHandle
  );
  vTaskStartScheduler();


  printf("\n--------------------- NEW LOG ---------------------\n");
  //i2c_test();

   while (1)
  {
    //tud_task();             // usb task
    //led_blinking_task();    // led task
    //task_nfc();             // nfc task


    configASSERT(0);  // We should never get here
  } 
    
  return 0;
}

// Callbacks
void vUSBTask(void* pvParameters){

  const char *pcTaskName = "USB Task is running\r\n";
  printf(pcTaskName);

  while(1){

    // Put here a conditional if statement that will create a new record if new
    // file received in USB memory

    //unsigned char test_message[] = "this is a test";
    if(checkfileReceived()){
      Record_sz = create_NDEFRecord(pFile, FileSize);
      received = TRUE;
    }

    taskENTER_CRITICAL();
    tud_task();
    taskEXIT_CRITICAL();  
    vTaskDelay(10);
  }
} 

void vLEDTask(void* pvParameters){

  const char *pcTaskName = "LED Task is running\r\n";
  printf(pcTaskName);

  while(1){
    led_blinking_task();
    vTaskDelay(10);
  }
} 

void vNFCTask(void* pvParameters){

  const char *pcTaskName = "NFC Task is running\r\n";
  printf(pcTaskName);

  
  while(1){
    if(received == TRUE){
      received = FALSE;
      task_nfc();
    }
    vTaskDelay(10);   // There is another task delay in 
  }
}
