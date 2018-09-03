#ifndef DATA_REG_FSM_H_
#define DATA_REG_FSM_H_

#include "data_reg_types.h"
#include "fsm.h"
#define DATA_REG_FSM(cb) \
FSM_STATE_DEF(cb, DATA_REG_IDLE_STID, \
    FSM_TRANSITION_DEF(cb, DATA_REG_INT_INCOMING_MSG_MID,      DATA_REG_VALIDATION_STID, data_reg_queue_guard,  data_reg_dequeue_msg) \
) \
FSM_STATE_DEF(cb, DATA_REG_VALIDATION_STID, \
    FSM_TRANSITION_DEF(cb, DATA_REG_INT_VALID_DATA_MID,        DATA_REG_RESPONSE_STID,   data_reg_status_guard, data_send_status_req) \
    FSM_TRANSITION_DEF(cb, DATA_REG_INT_INVALID_DATA_MID,      DATA_REG_IDLE_STID,       NULL,                  data_reg_discard_msg) \
) \
FSM_STATE_DEF(cb, DATA_REG_RESPONSE_STID , \
    FSM_TRANSITION_DEF(cb, DATA_REG_INT_STATUS_RES_MID,        DATA_REG_SAVED_STID,      data_reg_status_guard, data_reg_save_nvm) \
    FSM_TRANSITION_DEF(cb, DATA_REG_INT_RES_TOUT_MID,          DATA_REG_IDLE_STID,       NULL,                  data_reg_enqueue_msg) \
) \
FSM_STATE_DEF(cb, DATA_REG_SAVED_STID, \
    FSM_TRANSITION_DEF(cb, DATA_REG_INT_NOTIFY_SAVED_MID,      DATA_REG_IDLE_STID,       data_reg_saved_guard,  data_reg_success) \
    FSM_TRANSITION_DEF(cb, DATA_REG_INT_SAVED_TOUT_MID,        DATA_REG_IDLE_STID,       NULL,                  data_reg_enqueue_msg) \
)

#define CQueue_Params Data_Register_Token
#include "cqueue.h"
#undef CQueue_Params

typedef union Data_Reg_FSM
{
        union Data_Reg_FSM_Class _private * _private vtbl;
        struct Object Object;
        union State_Machine State_Machine;
        struct
        {
                union FSM FSM;
                CQueue_Data_Register_Token_T _private * _private register_queue;
                char _private * _private date;
                bool _private is_data_saved;
        };
}Data_Reg_FSM_T;

typedef union Data_Reg_FSM_Class
{
        struct Class Class;
        struct State_Machine_Class State_Machine;
        union FSM_Class FSM;
}Data_Reg_FSM_Class_T;

extern union Data_Reg_FSM_Class _private Data_Reg_FSM_Class;

extern void Populate_Data_Reg_FSM(union Data_Reg_FSM * const data_reg_fsm);

#endif /* DATA_REG_FSM_H_ */
