#ifndef DATA_COLLECTOR_WRKR_H_
#define DATA_COLLECTOR_WRKR_H_

#include "worker.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef union Worker Data_Collector_Wrkr_T;
typedef union Worker_Class Data_Collector_Wrkr_Class_T;

extern Data_Collector_Wrkr_Class_T _private Data_Collector_Wrkr_Class;

extern void Allocate_Data_Collector_Wrkr(union Worker ** const dc);

#ifdef __cplusplus
}
#endif

#endif /*DATA_COLLECTOR_WRKR_H_*/
