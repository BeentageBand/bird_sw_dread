#define COBJECT_IMPLEMENTATION
#define Dbg_FID DATA_POST_FID, 0

#include "application.h"
#include "data_post_process.h"
#include "data_post_set.h"
#include "data_post_worker.h"
#include "dbg_log.h"
#include "ipc.h"

#define Data_Post_MID_Subcription(mid, proc) mid,

static void data_post_worker_delete(struct Object * const obj);
static void data_post_worker_on_start(union Worker * const super);
static void data_post_worker_on_mail(union Worker * const super, union Mail * const mail);
static void data_post_worker_on_loop(union Worker * const super);
static void data_post_worker_on_stop(union Worker * const super);

static union Data_Post_Worker Data_Post_Worker = {NULL};
static union Mail Data_Post_Worker_Mailbox[64] = {0};
static Data_Post_Dispatcher_T Data_Post_Dispatcher = {NULL};

static IPC_MID_T Data_Post_Mailist []=
{
        DATA_POST_SUBSCRIPTION_MAILIST(Data_Post_MID_Subcription)
};

union Data_Post_Worker_Class Data_Post_Worker_Class =
{
        {data_post_worker_delete, NULL}
};

void data_post_worker_delete(struct Object * const obj)
{}

void data_post_worker_on_start(union Worker * const super)
{
    if(IPC_Subscribe_Mailist(Data_Post_Mailist, Num_Elems(Data_Post_Mailist)))
    {

    }
    Application_initialized();
}

void data_post_worker_on_mail(union Worker * const super, union Mail * const mail)
{
    union Data_Post_Worker * const this = _cast(Data_Post_Worker, super);
    Isnt_Nullptr(this, );
    Data_Post_Process_MID_T mid_pair = {mail->mid, NULL};
    Dbg_Info("%s:mail mid %d", __func__, mail->mid);
    Data_Post_Process_MID_T * const process = Data_Post_Dispatcher.DATA_POST_CSET.vtbl->find(&Data_Post_Dispatcher.DATA_POST_CSET, mid_pair);
    if(Data_Post_Dispatcher.DATA_POST_CSET.vtbl->end(&Data_Post_Dispatcher.DATA_POST_CSET) != process)
    {
        Dbg_Info("%s:found process for mid %d", __func__, mail->mid);
        process->obj(this, mail);
    }
}

void data_post_worker_on_loop(union Worker * const super)
{
    IPC_Sleep(200);
    Dbg_Info("%s: is alive", __func__);
}

void data_post_worker_on_stop(union Worker * const super)
{
    if(IPC_Unsubscribe_Mailist(Data_Post_Mailist, Num_Elems(Data_Post_Mailist)))
    {

    }
    Application_terminated();
}

void Populate_Data_Post_Worker(union Data_Post_Worker * const this)
{
    if(NULL == Data_Post_Worker.vtbl)
    {
        Populate_Worker(&Data_Post_Worker.Worker,
                DATA_POST_WORKER_TID,
                Data_Post_Worker_Mailbox,
                Num_Elems(Data_Post_Worker_Mailbox));
        Object_Init(&Data_Post_Worker.Object,
                &Data_Post_Worker_Class.Class,
                sizeof(Data_Post_Worker_Class.Worker));

        Data_Post_Worker_Class.Worker.on_start = data_post_worker_on_start;
        Data_Post_Worker_Class.Worker.on_mail  = data_post_worker_on_mail;
        Data_Post_Worker_Class.Worker.on_loop  = data_post_worker_on_loop;
        Data_Post_Worker_Class.Worker.on_stop  = data_post_worker_on_stop;
        Populate_Data_Post_Dispatcher(&Data_Post_Dispatcher);
    }
    _clone(this, Data_Post_Worker);
}
