// mem_helper.h

#ifndef MEM_HELPER_H
#define MEM_HELPER_H

struct Receipts {
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
} receipts;

int32_t get_mem_info(char* pBuffer, int32_t bufsize);
struct Receipts *get_file_info(char* pBuffer, int32_t bufsize);

#endif // MEM_HELPER_H
