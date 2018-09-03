/*
 * data_reg_process.h
 *
 *  Created on: Sep 1, 2018
 *      Author: uids6144
 */

#ifndef DATA_REG_PROCESS_H_
#define DATA_REG_PROCESS_H_

#include "data_reg_types.h"
#include "data_reg_worker.h"

#define DATA_REG_CSET CHash_Set_Pair_IPC_MID_Data_Reg_Process

typedef void (*Data_Reg_Process_T)(union Data_Reg_Worker * const, union Mail * const);

#define CHash_Map_Params IPC_MID, Data_Reg_Process
#include "chash_map.h"
#undef CHash_Map_Params

typedef CHash_Map_IPC_MID_Data_Reg_Process_T Data_Reg_Dispatcher_T;
typedef Pair_IPC_MID_Data_Reg_Process_T Data_Reg_Process_MID_T;

extern void Populate_Data_Reg_Dispatcher(Data_Reg_Dispatcher_T * const dispatcher);

#endif /* DATA_REG_PROCESS_H_ */
