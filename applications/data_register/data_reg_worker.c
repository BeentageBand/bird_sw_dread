#define COBJECT_IMPLEMENTATION
#define Dbg_FID DATA_REG_FID, 0

#include "application.h"
#include "data_reg_process.h"
#include "data_reg_set.h"
#include "data_reg_worker.h"
#include "dbg_log.h"
#include "ipc.h"

#define Data_Reg_MID_Subcription(mid, proc) mid,

static void data_reg_worker_delete(struct Object * const obj);
static void data_reg_worker_on_start(union Worker * const super);
static void data_reg_worker_on_mail(union Worker * const super, union Mail * const mail);
static void data_reg_worker_on_loop(union Worker * const super);
static void data_reg_worker_on_stop(union Worker * const super);

static union Data_Reg_Worker Data_Reg_Worker = {NULL};
static union Mail Data_Reg_Worker_Mailbox[64] = {0};
static Data_Reg_Dispatcher_T Data_Reg_Dispatcher = {NULL};

static IPC_MID_T Data_Reg_Mailist []=
{
        DATA_REG_SUBSCRIPTION_MAILIST(Data_Reg_MID_Subcription)
};

union Data_Reg_Worker_Class Data_Reg_Worker_Class =
{
        {data_reg_worker_delete, NULL}
};

void data_reg_worker_delete(struct Object * const obj)
{}

void data_reg_worker_on_start(union Worker * const super)
{
    if(IPC_Subscribe_Mailist(Data_Reg_Mailist, Num_Elems(Data_Reg_Mailist)))
    {

    }
    Application_initialized();
}

void data_reg_worker_on_mail(union Worker * const super, union Mail * const mail)
{
    union Data_Reg_Worker * const this = _cast(Data_Reg_Worker, super);
    Isnt_Nullptr(this, );
    Data_Reg_Process_MID_T mid_pair = {mail->mid, NULL};
    Dbg_Info("%s:mail mid %d", __func__, mail->mid);
    Data_Reg_Process_MID_T * const process = Data_Reg_Dispatcher.DATA_REG_CSET.vtbl->find(&Data_Reg_Dispatcher.DATA_REG_CSET, mid_pair);
    if(Data_Reg_Dispatcher.DATA_REG_CSET.vtbl->end(&Data_Reg_Dispatcher.DATA_REG_CSET) != process)
    {
        Dbg_Info("%s:found process for mid %d", __func__, mail->mid);
        process->obj(this, mail);
    }
}

void data_reg_worker_on_loop(union Worker * const super)
{
    IPC_Sleep(200);
    Dbg_Info("%s: is alive", __func__);
}

void data_reg_worker_on_stop(union Worker * const super)
{
    if(IPC_Unsubscribe_Mailist(Data_Reg_Mailist, Num_Elems(Data_Reg_Mailist)))
    {

    }
    Application_terminated();
}

void Populate_Data_Reg_Worker(union Data_Reg_Worker * const this)
{
    if(NULL == Data_Reg_Worker.vtbl)
    {
        Populate_Worker(&Data_Reg_Worker.Worker,
                DATA_REG_WORKER_TID,
                Data_Reg_Worker_Mailbox,
                Num_Elems(Data_Reg_Worker_Mailbox));
        Object_Init(&Data_Reg_Worker.Object,
                &Data_Reg_Worker_Class.Class,
                sizeof(Data_Reg_Worker_Class.Worker));

        Data_Reg_Worker_Class.Worker.on_start = data_reg_worker_on_start;
        Data_Reg_Worker_Class.Worker.on_mail  = data_reg_worker_on_mail;
        Data_Reg_Worker_Class.Worker.on_loop  = data_reg_worker_on_loop;
        Data_Reg_Worker_Class.Worker.on_stop  = data_reg_worker_on_stop;
        Populate_Data_Reg_Dispatcher(&Data_Reg_Dispatcher);
    }
    _clone(this, Data_Reg_Worker);
}
