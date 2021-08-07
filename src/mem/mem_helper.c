// mem_helper.c
//

#include <stdio.h>
#include <string.h>
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
#define LBA 2 
#define OFFSET 0
#define NAMESIZE 7    // "RECEIPT" is 7 chars long

struct Receipt {
  char file_name[8];            // Offset 0x00
  char file_ext[3];             //        0x08
  char file_attr[1];            //        0x0B
  char reserved[1];             //        0x0C
  char create_time_fine[1];     //        0x0D
  char create_time[2];          //        0x0E
  char create_date[2];          //        0x10
  char last_accessed[2];        //        0x12
  char ea_index[2];             //        0x14
  char last_modified_time[2];   //        0x16
  char last_modified_date[2];   //        0x18
  char file_location[2];        //        0x1A
  char file_size[4];            //        0x0C
} receipt;

int32_t get_mem_info(char* pBuffer, int32_t bufsize){

  int32_t bytes_read = tud_msc_read10_cb(LUN, LBA, OFFSET, pBuffer, bufsize);

  return bytes_read;
}

/* get_file_info()
 * Purpose: Gets file that was just added to fat12 directory table and populates the
 * struct
 *
 * params:
 * pBuffer --> buffer that points to the fat12 directory table
 * bufsize --> size of the fat12 directory table (or however much we want to
 * read)
 *
 * returns --> pointer to structure 
 * table
 */
uint32_t get_file_info(char* pBuffer, int32_t bufsize){
  
  int16_t i = 0;
  const char name[8] = "RECEIPT";
  char temp[8] = {0};
  
  // Look for "RECEIPT" file name
  // Loop through directory entries (32 bytes each)
  
  for (i = 0; i < 4; i++){

    memcpy(temp, pBuffer + (i*32), strlen(name));  // Copy directory entry filename into temporary array
    temp[sizeof(name)] = '\0';                  // Add null terminator after to make it a string

    if (!strcmp(name, temp)){   // Compare the two strings
      printf("<%s> == <%s>\n", name, temp);
    }
    else printf("<%s> != <%s>\n", name, temp);
  }

  return 0;
}
