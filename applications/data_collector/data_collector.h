#ifndef DATA_COLLECTOR_H_
#define DATA_COLLECTOR_H_

#include "fsm.h"

typedef enum DC_ERR
{
	DC_OK,
	DC_DATA_TIMEOUT_ERR,
	DC_INVALID_DATA_ERR,
	DC_INVALID
}DC_ERR_T;

typedef union FSM DCFSM_T;
typedef struct FSM_Class DCFSM_Class_T;

extern DCFSM_Class_T _private DCFSM_Class;

extern void Alloc_Data_Collector(union FSM ** const fsm);

#endif /*DATA_COLLECTOR_H_*/
