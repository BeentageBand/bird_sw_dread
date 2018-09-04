#define COBJECT_IMPLEMENTATION
#include "data_post_cbk.h"
#include "data_post_fsm.h"
#include "data_post_process.h"
#include "ipc.h"

#define CHash_Map_Params IPC_MID, Data_Post_Process
#include "chash_map.c"
#undef CHash_Map_Params

#define DATA_POST_PROCESS_MAILIST(X) \
DATA_POST_SUBSCRIPTION_MAILIST(X) \
X(DATA_POST_INT_PACKET_ACK_MID, data_post_on_packet_ack) \

#define DATA_POST_PROCESS(mid, proc) {mid, proc},
#define DATA_POST_PACKET_FRAME_SIZE (500U)

static void data_post_on_packet_ack(union Data_Post_Worker * const this, union Mail * const mail);

static Data_Post_Process_MID_T Data_Post_Dispatcher_Mailist[] =
{
    DATA_POST_PROCESS_MAILIST(DATA_POST_PROCESS)
};

static union Data_Post_Cbk Data_Post_Stdin = {NULL};

void data_post_on_packet_ack(union Data_Post_Worker * const this, union Mail * const mail)
{
    union Data_Post_FSM * const fsm = _cast(Data_Post_FSM, this->st_m);
    Isnt_Nullptr(fsm, );

    fsm->packet->data_left -= (fsm->packet->data_left > DATA_POST_PACKET_FRAME_SIZE)? DATA_POST_PACKET_FRAME_SIZE : 0;
}

void Populate_Data_Post_Dispatcher(Data_Post_Dispatcher_T * const dispatcher)
{
    if(NULL == dispatcher->vtbl)
    {
        Populate_CHash_Map_IPC_MID_Data_Post_Process(dispatcher,
        Data_Post_Dispatcher_Mailist, Num_Elems(Data_Post_Dispatcher_Mailist), NULL);
        Populate_Data_Post_Cbk(&Data_Post_Stdin);
    }
}
