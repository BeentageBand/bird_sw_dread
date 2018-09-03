/*
 * data_reg_worker.h
 *
 *  Created on: Aug 31, 2018
 *      Author: uids6144
 */

#ifndef DATA_REG_WORKER_H_
#define DATA_REG_WORKER_H_

#include "worker.h"
#include "state_machine.h"

typedef union Data_Reg_Worker
{
        union Data_Reg_Worker_Class _private * _private vtbl;
        struct Object Object;
        union Thread Thread;
        struct
        {
                union Worker Worker;
                union State_Machine _private * _private st_m;
        };
}Data_Reg_Worker_T;

typedef union Data_Reg_Worker_Class
{
        struct Class Class;
        struct Thread_Class Thread;
        union Worker_Class Worker;
}Data_Reg_Worker_Class_T;

extern union Data_Reg_Worker_Class _private Data_Reg_Worker_Class;

extern void Populate_Data_Reg_Worker(union Data_Reg_Worker * const data_reg);

#endif /* DATA_REG_WORKER_H_ */
