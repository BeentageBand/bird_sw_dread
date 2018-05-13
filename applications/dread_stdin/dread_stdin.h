#ifndef DREAD_STDIN_H_
#define DREAD_STDIN_H_

#include "std_reuse.h"

#define STDIN_REG_SIZE (16UL)

struct STDIN_Reg
{
   uint8_t raw[STDIN_REG_SIZE];
};

#endif /*DREAD_STDIN_H_*/
