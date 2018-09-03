/*
 * data_post.h
 *
 *  Created on: Sep 1, 2018
 *      Author: uids6144
 */

#ifndef DATA_POST_WORKER_H_
#define DATA_POST_WORKER_H_

#include "worker.h"
#include "state_machine.h"

typedef union Data_Post_Worker
{
        union Data_Post_Worker_Class _private * _private vtbl;
        struct Object Object;
        union Thread Thread;
        struct
        {
                union Worker Worker;
                union State_Machine _private * _private st_m;
        };
}Data_Post_Worker_T;

typedef union Data_Post_Worker_Class
{
        struct Class Class;
        struct Thread_Class Thread;
        union Worker_Class Worker;
}Data_Post_Worker_Class_T;

extern union Data_Post_Worker_Class _private Data_Post_Worker_Class;

extern void Populate_Data_Post_Worker(union Data_Post_Worker * const data_reg);

#endif /* DATA_POST_WORKER_H_ */
