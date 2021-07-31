// tusb_config.h
//
// Purpose: To configure the USB driver
//
// Majority of code taken from TinyUSB, but configured to specifics by Daniel Dreise

#ifndef _TUSB_CONFIG_H_
#define _TUSB_CONFIG_H_

#ifdef __cplusplus
 extern "C" {
#endif

//--------------------------------------------------------------------
// COMMON CONFIGURATION
//--------------------------------------------------------------------


// RHPort number used. Pico has 2, we only need one so set to "0"
#ifndef BOARD_DEVICE_RHPORT_NUM
  #define BOARD_DEVICE_RHPORT_NUM     0
#endif

// Set to fastest Pico's USB can manage
#ifndef BOARD_DEVICE_RHPORT_SPEED
  #define BOARD_DEVICE_RHPORT_SPEED   OPT_MODE_HIGH_SPEED
#endif

// Device mode with rhport and speed defined by board.mk
#if   BOARD_DEVICE_RHPORT_NUM == 0
  #define CFG_TUSB_RHPORT0_MODE     (OPT_MODE_DEVICE | BOARD_DEVICE_RHPORT_SPEED)
#else
  #error "Incorrect RHPort configuration"
#endif

// Pico does not use an Operating System
#ifndef CFG_TUSB_OS 
#define CFG_TUSB_OS               OPT_OS_FREERTOS
#endif

// CFG_TUSB_DEBUG is defined by compiler in DEBUG build
// #define CFG_TUSB_DEBUG           0

/* USB DMA on some MCUs can only access a specific SRAM region with restriction on alignment.
 * Tinyusb use follows macros to declare transferring memory so that they can be put
 * into those specific section.
 * e.g
 * - CFG_TUSB_MEM SECTION : __attribute__ (( section(".usb_ram") ))
 * - CFG_TUSB_MEM_ALIGN   : __attribute__ ((aligned(4)))
 */
#ifndef CFG_TUSB_MEM_SECTION
#define CFG_TUSB_MEM_SECTION        
#endif

#ifndef CFG_TUSB_MEM_ALIGN
#define CFG_TUSB_MEM_ALIGN          __attribute__ ((aligned(4)))
#endif

//--------------------------------------------------------------------
// DEVICE CONFIGURATION
//--------------------------------------------------------------------

#ifndef CFG_TUD_ENDPOINT0_SIZE
#define CFG_TUD_ENDPOINT0_SIZE    64
#endif

//------------- CLASS -------------//
#define CFG_TUD_CDC               0
#define CFG_TUD_MSC               1     // Setup as Mass Storage Device so Splitter can easily access
#define CFG_TUD_HID               0
#define CFG_TUD_MIDI              0
#define CFG_TUD_VENDOR            0

// MSC Buffer size of Device Mass storage
#define CFG_TUD_MSC_EP_BUFSIZE    512   // This is a standard size buffer.

#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_CONFIG_H_ */
