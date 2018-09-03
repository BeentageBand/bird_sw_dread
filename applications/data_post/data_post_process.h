/*
 * data_post_process.h
 *
 *  Created on: Sep 1, 2018
 *      Author: uids6144
 */

#ifndef DATA_POST_PROCESS_H_
#define DATA_POST_PROCESS_H_

#include "data_post_types.h"
#include "data_post_worker.h"

#define DATA_POST_CSET CHash_Set_Pair_IPC_MID_Data_Post_Process

typedef void (*Data_Post_Process_T)(union Data_Post_Worker * const, union Mail * const);

#define CHash_Map_Params IPC_MID, Data_Post_Process
#include "chash_map.h"
#undef CHash_Map_Params

typedef CHash_Map_IPC_MID_Data_Post_Process_T Data_Post_Dispatcher_T;
typedef Pair_IPC_MID_Data_Post_Process_T Data_Post_Process_MID_T;

extern void Populate_Data_Post_Dispatcher(Data_Post_Dispatcher_T * const dispatcher);

#endif /* DATA_POST_PROCESS_H_ */
