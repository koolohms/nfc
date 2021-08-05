// mem_helper.c
//

#include <stdint.h>
#include "mem_helper.h"
#include "tusb.h"


// Used to get the fat12 file information stored in the directory table
// Returns number of bytes received
// Directory Table:
//  Offset  Length  Description
//  0x00    8       file name
//  0x08    3       file extension
//  0x0b    1       file attributes (read-only, hidden, label, etc) 
//                  0x0F == long-file entry
//  0x0c    1       reserved
//  0x0d    1       time created in fine resolution (1 == 10ms)
//  0x0e    2       time created in hours/minutes/seconds (resolution 2s)
//  0x10    2       date created
//  0x12    2       last access date
//  0x14    2       EA-index...?
//  0x16    2       last modified time
//  0x18    2       last modified date
//  0x1a    2       first cluster (location?)
//  0x1c    4       file size (bytes)

#define LUN 0 
#define LBA 0
#define OFFSET 0

int32_t get_mem_info(char* pBuffer, int32_t bufsize){

  int32_t bytes_read = tud_msc_read10_cb(LUN, LBA, OFFSET, pBuffer, bufsize);

  return bytes_read;
}


