#define COBJECT_IMPLEMENTATION
#define Dbg_FID DATA_REG_FID, 3

#include "data_reg_cbk.h"
#include "data_reg_fsm.h"
#include "dbg_log.h"
#include "ipc.h"

#define CQueue_Params Data_Register_Token
#include "cqueue.c"
#undef CQueue_Params

static void data_reg_delete(struct Object * const obj);

static bool data_reg_queue_guard(union State_Machine * const st_m, union St_Machine_State * const state);
static bool data_reg_status_guard(union State_Machine * const st_m, union St_Machine_State * const state);
static bool data_reg_saved_guard(union State_Machine * const st_m, union St_Machine_State * const state);
static void data_reg_dequeue_msg(union State_Machine * const st_m);
static void data_send_status_req(union State_Machine * const st_m);
static void data_reg_discard_msg(union State_Machine * const st_m);
static void data_reg_save_nvm(union State_Machine * const st_m);
static void data_reg_enqueue_msg(union State_Machine * const st_m);
static void data_reg_success(union State_Machine * const st_m);

FSM_Declare_Chart(DATA_REG_FSM, Data_Reg_St_Chart)

static union Data_Reg_FSM Data_Reg_FSM = {NULL};
static union Data_Reg_Cbk Data_Reg_Cbk = {NULL};
static CQueue_Data_Register_Token_T Data_Reg_Queue = {NULL};
static struct Data_Register_Token Data_Reg_Queue_Buff[32] = {NULL};
static char Date_Buff[DATA_REG_DATE_MMDDYYYY_HHMM_LENGTH] = {0};
static union St_Machine_State Data_Reg_States[DATA_REG_MAX_STID] = {0};

union Data_Reg_FSM_Class Data_Reg_FSM_Class =
{
        {{data_reg_delete, NULL}}
};

static struct Data_Register_Token Current_Proc_Token = {0};
extern union Data_Reg_FSM_Class _private Data_Reg_FSM_Class;

void data_reg_delete(struct Object * const obj){}

bool data_reg_queue_guard(union State_Machine * const st_m, union St_Machine_State * const state)
{
    union Data_Reg_FSM * const this = _cast(Data_Reg_FSM, st_m);
    Isnt_Nullptr(this, false);
    bool rc = false;
    return 0 != this->register_queue->i;
}

bool data_reg_status_guard(union State_Machine * const st_m, union St_Machine_State * const state)
{
    bool is_empty = 0 == Date_Buff[0] &&
            0 == memcmp(Date_Buff, Date_Buff + 1, sizeof(Date_Buff) - 1);
    return !is_empty;
}

bool data_reg_saved_guard(union State_Machine * const st_m, union St_Machine_State * const state)
{
    union Data_Reg_FSM * const this = _cast(Data_Reg_FSM, st_m);
    Isnt_Nullptr(this, false);
    bool is_saved = this->is_data_saved;
    if(!is_saved)
    {
        data_send_status_req(st_m);
    }
    return is_saved;
}

void data_reg_dequeue_msg(union State_Machine * const st_m)
{
    union Data_Reg_FSM * const this = _cast(Data_Reg_FSM, st_m);
    Isnt_Nullptr(this, );
    Current_Proc_Token = this->register_queue->vtbl->back(this->register_queue);
    this->register_queue->vtbl->pop_back(this->register_queue);
}

void data_send_status_req(union State_Machine * const st_m)
{
    Data_Reg_Cbk.vtbl->req_status(&Data_Reg_Cbk);
    memset(Date_Buff, 0, sizeof(Date_Buff));
}

void data_reg_discard_msg(union State_Machine * const st_m)
{
    memset(&Current_Proc_Token, 0, sizeof(Current_Proc_Token));
    Data_Reg_Cbk.vtbl->notify_failure(&Data_Reg_Cbk);
}

void data_reg_save_nvm(union State_Machine * const st_m)
{
    union Data_Reg_FSM * const this = _cast(Data_Reg_FSM, st_m);
    Isnt_Nullptr(this, );
    memcpy(Current_Proc_Token.date, this->date, sizeof(Current_Proc_Token.date));
    Data_Reg_Cbk.vtbl->backup(&Data_Reg_Cbk, &Current_Proc_Token);
}

void data_reg_enqueue_msg(union State_Machine * const st_m)
{
    union Data_Reg_FSM * const this = _cast(Data_Reg_FSM, st_m);
    Isnt_Nullptr(this, );
    if (0 == this->register_queue->i) return ;
    Current_Proc_Token =  this->register_queue->vtbl->back(this->register_queue);
    this->register_queue->vtbl->pop_back(this->register_queue);
    memset(Date_Buff, 0, sizeof(Date_Buff));
}

void data_reg_success(union State_Machine * const st_m)
{
    Data_Reg_Cbk.vtbl->notify_success(&Data_Reg_Cbk);
    memset(Date_Buff, 0, sizeof(Date_Buff));
}

void Populate_Data_Reg_FSM(union Data_Reg_FSM * const this)
{
    if(NULL == Data_Reg_FSM.vtbl)
    {
        Populate_FSM(&Data_Reg_FSM.FSM,
                Data_Reg_St_Chart, Num_Elems(Data_Reg_St_Chart),
                Data_Reg_States, Num_Elems(Data_Reg_States));
        Object_Init(&Data_Reg_FSM.Object,
                &Data_Reg_FSM_Class.Class,
                sizeof(Data_Reg_FSM_Class.FSM));
        Populate_Data_Reg_Cbk(&Data_Reg_Cbk);
        Data_Reg_FSM.date = Date_Buff;
        Data_Reg_FSM.register_queue = &Data_Reg_Queue;
        Populate_CQueue_Data_Register_Token(&Data_Reg_Queue,
                Data_Reg_Queue_Buff,
                Num_Elems(Data_Reg_Queue_Buff));
    }
    _clone(this, Data_Reg_FSM);
}
