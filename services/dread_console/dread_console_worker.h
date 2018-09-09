#ifndef DREAD_CONSOLE_WORKER_H_
#define DREAD_CONSOLE_WORKER_H_

#include "worker.h"
#include "dread_console.h"

typedef union Dread_Console_Worker
{
        union Dread_Console_Worker_Class _private * _private vtbl;
        struct Object Object;
        union Thread Thread;
        struct
        {
            union Worker Worker;
            union Dread_Console _private dread_console;
        };
}Dread_Console_Worker_T;

typedef union Dread_Console_Worker_Class
{
        struct Class Class;
        struct Thread_Class Thread;
        union Worker_Class Worker;
}Dread_Console_Worker_Class_T;

extern union Dread_Console_Worker_Class _private Dread_Console_Worker_Class;

extern void Populate_Dread_Console_Worker(union Dread_Console_Worker * const dread_console_worker);

#endif /* DREAD_CONSOLE_WORKER_H_ */
