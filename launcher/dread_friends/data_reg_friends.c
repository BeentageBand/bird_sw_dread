#define COBJECT_IMPLEMENTATION
#define Dbg_FID DREAD_LAUNCHER_FID,1
#include "dbg_log.h"
#include "data_reg_cbk.h"
#include "ipc.h"

static void data_reg_cbk_delete(struct Object * const obj);
static void data_reg_notify_success(union Data_Reg_Cbk * const this);
static void data_reg_notify_failure(union Data_Reg_Cbk * const this);
static void data_reg_req_status(union Data_Reg_Cbk * const this);
static void data_reg_backup(union Data_Reg_Cbk * const this, struct Data_Register_Token * const token);

static union Data_Reg_Cbk Data_Reg_Cbk = {NULL};
struct Data_Reg_Cbk_Class Data_Reg_Cbk_Class =
{
        {data_reg_cbk_delete, NULL},
        data_reg_notify_success,
        data_reg_notify_failure,
        data_reg_req_status,
        data_reg_backup
};

void data_reg_cbk_delete(struct Object * const obj)
{}

void data_reg_notify_success(union Data_Reg_Cbk * const this)
{
    IPC_Send(HID_WORKER_TID, HID_INT_BUZZ_SUCESS_MID, NULL, 0);

}

void data_reg_notify_failure(union Data_Reg_Cbk * const this)
{
    IPC_Send(HID_WORKER_TID, HID_INT_BUZZ_ERROR_MID, NULL, 0);
}

void data_reg_req_status(union Data_Reg_Cbk * const this)
{
    //TODO
}

void data_reg_backup(union Data_Reg_Cbk * const this, struct Data_Register_Token * const token)
{
    //TODO
}

void Populate_Data_Reg_Cbk(union Data_Reg_Cbk * const this)
{
    if(NULL == Data_Reg_Cbk.vtbl)
    {
        Data_Reg_Cbk.vtbl = &Data_Reg_Cbk_Class;
    }
    _clone(this, Data_Reg_Cbk);
}
void data_reg_on_data_post_error(union Data_Reg_Worker * const this, union Mail * const mail)
{}
