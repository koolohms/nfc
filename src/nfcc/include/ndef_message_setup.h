// ndef_message_setup.h

#ifndef NDEF_MESSAGE_SETUP_H
#define NDEF_MESSAGE_SETUP_H

//#include "tusb.h"

extern uint8_t* addr;
extern unsigned char* pRecord;
extern uint32_t Record_sz;

uint32_t create_NDEFRecord(unsigned char* pMessage, unsigned int MessageSize);
void free_NDEFRecord();

#endif // NDEF_MESSAGE_SETUP_H
