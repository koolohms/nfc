// ndef_message_setup.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ndef_message_setup.h"
#include "FreeRTOS.h"
#include "task.h"


#define SIZEOF_TNF 2
#define SIZEOF_PAYLOAD_SIZE 4
#define SIZEOF_TYPE 10
#define SIZEOF_STATUS 1

char* pRecord;

// Create NDEF record to send to NFC
uint32_t create_NDEFRecord(char* pMessage, unsigned int MessageSize){
    
    int sz, tot_sz, Record_sz, index = 0;

    // Beginning of ndef header
    const char NDEF_HEADER_TNF[SIZEOF_TNF] = {
        0xC2,
        0x0A
    };

    // Getting payload size type
    sz = MessageSize;

    // Setting payload length
    const char ndef_header_payload_size[SIZEOF_PAYLOAD_SIZE] = {
        sz >> 24,
        sz >> 16,
        sz >> 8,
        sz & 0xFF
    };
    
    // Setting type
    const char ndef_header_type[SIZEOF_TYPE] = {
        't','e','x','t','/','p','l','a','i','n'
    };

    // Setting status
    char ndef_header_status[SIZEOF_STATUS] = {0x02};

    // Total size
    tot_sz = SIZEOF_TNF + SIZEOF_PAYLOAD_SIZE + SIZEOF_TYPE + SIZEOF_STATUS + sz;

    pRecord = (char*)malloc(tot_sz * sizeof(char));

    // Populate newly allocated memory with contents
    memcpy(pRecord, NDEF_HEADER_TNF, SIZEOF_TNF); 
    index = index + SIZEOF_TNF; 

    memcpy(pRecord + index, ndef_header_payload_size, SIZEOF_PAYLOAD_SIZE);
    index = index + SIZEOF_PAYLOAD_SIZE;

    memcpy(pRecord + index, ndef_header_type, SIZEOF_TYPE);
    index = index + SIZEOF_TYPE;

    memcpy(pRecord + index, ndef_header_status, SIZEOF_STATUS);
    index = index + SIZEOF_STATUS;

    memcpy(pRecord + index, pMessage, MessageSize);
    index = index + MessageSize;

    Record_sz = index; // Since we kept track using index, it can be used for size

    // Print out contents of pRecord
    printf("\nContents of pRecord: ");
    for (int i = 0; i < index; i++){
      printf("%x\n", pRecord[i]);
    }
    printf("\nSize of pRecord: %d\n" ,Record_sz);

    return Record_sz;
}

void free_NDEFRecord(){
  free(pRecord);
}
