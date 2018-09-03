#define COBJECT_IMPLEMENTATION
#include "data_post_set.h"
#include "data_post_cbk.h"
#include "data_post_process.h"
#include "ipc.h"

#define CHash_Map_Params IPC_MID, Data_Post_Process
#include "chash_map.c"
#undef CHash_Map_Params

#define DATA_POST_PROCESS_MAILIST(X) \
DATA_POST_SUBSCRIPTION_MAILIST(X) \

#define DATA_POST_PROCESS(mid, proc) {mid, proc},

static Data_Post_Process_MID_T Data_Post_Dispatcher_Mailist[] =
{
    DATA_POST_PROCESS_MAILIST(DATA_POST_PROCESS)
};

static union Data_Post_Cbk Data_Post_Stdin = {NULL};

void Populate_Data_Post_Dispatcher(Data_Post_Dispatcher_T * const dispatcher)
{
    if(NULL == dispatcher->vtbl)
    {
        Populate_CHash_Map_IPC_MID_Data_Post_Process(dispatcher,
        Data_Post_Dispatcher_Mailist, Num_Elems(Data_Post_Dispatcher_Mailist), NULL);
        Populate_Data_Post_Cbk(&Data_Post_Stdin);
    }
}
