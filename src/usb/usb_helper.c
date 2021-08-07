// usb_helper.c
//
// Daniel Dreise

#include <stdio.h>
#include <stdint.h>
#include "usb_helper.h"

uint8_t *pFile = 0;
uint32_t FileSize;
uint8_t temp = 0;
uint8_t logic_addr = 0;

/* Check if new file is received into USB memory */
uint8_t checkfileReceived(void){
  // keep track of current file pointer
  // keep track of current file size (because they go in chunks)
  // when the file pointer changes, set return to TRUE

  if(logic_addr !=  temp){
    printf("New location of file: %x\n", pFile);
    printf("Size of file: %d\n", FileSize);
    printf("Contents of file: ");
    for(int i = 0; i < FileSize; i++){
      printf("%c", pFile[i]);
    }
    printf("\n");
    temp = logic_addr;
    return TRUE;
  }
  else return FALSE;

}
