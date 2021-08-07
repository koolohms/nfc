// ndef_message_setup.h

#ifndef NDEF_MESSAGE_SETUP_H
#define NDEF_MESSAGE_SETUP_H

//#include "tusb.h"

#define MAX_RECEIPT_SIZE  100000 

extern uint8_t* addr;
extern unsigned char pRecord[MAX_RECEIPT_SIZE];
extern uint32_t Record_sz;

uint32_t create_NDEFRecord(unsigned char* pMessage, unsigned int MessageSize);

#endif // NDEF_MESSAGE_SETUP_H
