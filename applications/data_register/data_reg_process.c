#define COBJECT_IMPLEMENTATION
#include "data_reg_set.h"
#include "data_reg_cbk.h"
#include "data_reg_process.h"
#include "ipc.h"

#define CHash_Map_Params IPC_MID, Data_Reg_Process
#include "chash_map.c"
#undef CHash_Map_Params

#define DATA_REG_PROCESS_MAILIST(X) \
DATA_REG_SUBSCRIPTION_MAILIST(X) \

#define DATA_REG_PROCESS(mid, proc) {mid, proc},

static Data_Reg_Process_MID_T Data_Reg_Dispatcher_Mailist[] =
{
    DATA_REG_PROCESS_MAILIST(DATA_REG_PROCESS)
};

static union Data_Reg_Cbk Data_Reg_Stdin = {NULL};

void Populate_Data_Reg_Dispatcher(Data_Reg_Dispatcher_T * const dispatcher)
{
    if(NULL == dispatcher->vtbl)
    {
        Populate_CHash_Map_IPC_MID_Data_Reg_Process(dispatcher,
        Data_Reg_Dispatcher_Mailist, Num_Elems(Data_Reg_Dispatcher_Mailist), NULL);
        Populate_Data_Reg_Cbk(&Data_Reg_Stdin);
    }
}
