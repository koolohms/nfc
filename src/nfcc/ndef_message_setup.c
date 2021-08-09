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
#define SIZEOF_LANG 2 

unsigned char pRecord[MAX_RECEIPT_SIZE] = {0};
uint32_t Record_sz;

// Create NDEF record to send to NFC
uint32_t create_NDEFRecord(unsigned char* pMessage, unsigned int MessageSize){
    
    uint32_t tot_sz, index = 0, i;

    // Total size
    tot_sz = SIZEOF_TNF + SIZEOF_PAYLOAD_SIZE + SIZEOF_TYPE + SIZEOF_STATUS + SIZEOF_LANG + MessageSize;

    // Beginning of ndef header
    char NDEF_HEADER_TNF[SIZEOF_TNF] = {
        0xC2,
        0x0A
    };
    for(i = 0; i < SIZEOF_TNF; i++){
      pRecord[index] = NDEF_HEADER_TNF[i];
      index++;
    }

    // Setting payload length
    char ndef_header_payload_size[SIZEOF_PAYLOAD_SIZE] = {
        (MessageSize + 3) >> 24,  // Add +1 for status, and 2 for language
        (MessageSize + 3) >> 16,
        (MessageSize + 3) >> 8,
        (MessageSize + 3) & 0xFF
    };
    
    for(i = 0; i < SIZEOF_PAYLOAD_SIZE; i++){
      pRecord[index] = ndef_header_payload_size[i];
      index++;
    }

    // Setting type
    char ndef_header_type[SIZEOF_TYPE] = {
        't','e','x','t','/','p','l','a','i','n'
    };

    for(i = 0; i < SIZEOF_TYPE; i++){
      pRecord[index] = ndef_header_type[i];
      index++;
    }

    // Setting status
    char ndef_header_status[SIZEOF_STATUS] = {0x02};

    for(i = 0; i < SIZEOF_STATUS; i++){
      pRecord[index] = ndef_header_status[i];
      index++;
    }

    // Setting language
    char ndef_language[SIZEOF_LANG] = {'e','n'}; 

    for(i = 0; i < SIZEOF_LANG; i++){
      pRecord[index] = ndef_language[i];
      index++;
    }

    for(i = 0; i < MessageSize; i++){
      pRecord[index] = pMessage[i];
      index++;
    }


    // Populate newly allocated memory with contents
    //memcpy(pRecord, NDEF_HEADER_TNF, SIZEOF_TNF); 
    //index = index + SIZEOF_TNF; 

    //memcpy(pRecord + index, ndef_header_payload_size, SIZEOF_PAYLOAD_SIZE);
    //index = index + SIZEOF_PAYLOAD_SIZE;

    //memcpy(pRecord + index, ndef_header_type, SIZEOF_TYPE);
    //index = index + SIZEOF_TYPE;

    //memcpy(pRecord + index, ndef_header_status, SIZEOF_STATUS);
    //index = index + SIZEOF_STATUS;

    //memcpy(pRecord + index, pMessage, MessageSize);
    //index = index + MessageSize;

    Record_sz = index; // Since we kept track using index, it can be used for size

    /*
    // Print out contents of pMessage
    printf("\nContents of pMessage: ");
    for (int i = 0; i < MessageSize; i++){
      printf("%c", pMessage[i]);
      printf("\n");
    } 
    printf("Size of pMessage: %d", MessageSize);

    // Print out contents of pRecord
    printf("\nContents of pRecord: ");
    for (int i = 0; i < index; i++){
      printf("%.2x\n", pRecord[i]);
    }
    printf("\nSize of pRecord: %d\n" ,Record_sz);
    */
    // populate array with pointer values
    //for (int i = 0; i < tot_sz; i++){
    //  pRecord_array[i] = pRecord[i];
    //}
    return index; // return size of record
}
