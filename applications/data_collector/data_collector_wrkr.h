#ifndef DATA_COLLECTOR_WRKR_H_
#define DATA_COLLECTOR_WRKR_H_

#include "worker.h"

typedef union Worker Data_Collector_T;

extern union Worker_Class _private Data_Collector_Wrkr_Class;

extern void Allocate_Data_Collector_Wrkr(union Worker * const this);

#endif /*DATA_COLLECTOR_WRKR_H_*/
