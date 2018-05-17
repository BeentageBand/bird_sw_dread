#ifndef DATA_COLLECTOR_WRKR_H_
#define DATA_COLLECTOR_WRKR_H_

#include "worker.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef union Data_Collector_Wrkr
{
   union Data_Collector_Wrkr_Class _private * _private vtbl;
   union Worker Worker;
   union Thread Thread;
   struct Object Object;
}Data_Collector_Wrkr_T;

typedef union Data_Collector_Wrkr_Class
{
   union Worker_Class Worker;
   struct Thread_Class Thread;
   struct Class Class;
}Data_Collector_Wrkr_Class_T;

extern Data_Collector_Wrkr_Class_T _private Data_Collector_Wrkr_Class;

extern union Data_Collector_Wrkr * Allocate_Data_Collector_Wrkr(void);

#ifdef __cplusplus
}
#endif

#endif /*DATA_COLLECTOR_WRKR_H_*/
