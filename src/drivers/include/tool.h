// tool.h

#ifndef TOOL_H
#define TOOL_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#define NCI_DEBUG

#ifdef  NCI_DEBUG
#define PRINTF printf
#endif  // DEBUG

extern void Sleep (unsigned int ms);

#endif  // TOOL_H