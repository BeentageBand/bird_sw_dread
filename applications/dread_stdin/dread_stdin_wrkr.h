#ifndef DREAD_STDIN_WRKR_H
#define DREAD_STDIN_WRKR_H

#include "worker.h"
typedef union Dread_StdIn_Wrkr
{
	union Dread_StdIn_Wrkr_Class _private * _private vtbl;
	struct Object Object;
	union Thread Thread;
	union Worker Worker;
}Dread_StdIn_Wrkr_T;

typedef union Dread_StdIn_Wrkr_Class
{
	union Worker_Class Worker;
	struct Class Class;
	struct Thread_Class Thread;
}Dread_StdIn_Wrkr_Class_T;

extern Dread_StdIn_Wrkr_Class_T _private Dread_StdIn_Wrkr_Class;

extern union Dread_StdIn_Wrkr * Alloc_Dread_StdIn_Wrkr(void);

#endif /*DREAD_STDIN_WRKR_H*/
