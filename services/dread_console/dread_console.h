#ifndef DREAD_CONSOLE_H_
#define DREAD_CONSOLE_H_
#include "console_composite.h"

#ifdef __cplusplus
extern "C"{
#endif
typedef union Dread_Console
{
    struct Dread_Console_Class _private * _private vtbl;
    struct Object Object;
    union Console Console;
    union Console_Composite Console_Composite;
}Dread_Console_T;

typedef struct Dread_Console_Class
{
    struct Class Class;
    struct Console_Class Console;
    union Console_Composite_Class Console_Composite;
}Dread_Console_Class_T;

extern struct Dread_Console_Class _private Dread_Console_Class;

extern void Populate_Dread_Console(union Dread_Console * const dread_console);

#ifdef __cplusplus
}
#endif
#endif /*DREAD_CONSOLE_H_*/