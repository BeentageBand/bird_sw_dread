#define COBJECT_IMPLEMENTATION
#include "hid_process.h"
#include "hid_worker.h"
#include "ipc.h"

#define HID_MID_Subcription(mid, proc) mid,

static void hid_worker_delete(struct Object * const obj);
static void hid_worker_on_start(union Worker * const super);
static void hid_worker_on_mail(union Worker * const super, union Mail * const mail);
static void hid_worker_on_loop(union Worker * const super);
static void hid_worker_on_stop(union Worker * const super);

static union HID_Worker HID_Worker = {NULL};
static union Mail HID_Worker_Mailbox[64] = {0};
static HID_Dispatcher_T HID_Dispatcher = {NULL};

static IPC_MID_T HID_Mailist []=
{
    HID_SUBSCRIPTION_MAILIST(HID_MID_Subcription)
};

union HID_Worker_Class HID_Worker_Class =
{
    {{hid_worker_delete, NULL}}
};

void hid_worker_delete(struct Object * const obj)
{}

void hid_worker_on_start(union Worker * const super)
{
    if(IPC_Subscribe(HID_Mailist, Num_Elems(HID_Mailist)))
    {

    }
}

void hid_worker_on_mail(union Worker * const super, union Mail * const mail)
{
    HID_Process_MID_T mid_pair = {mail->mid, NULL};
    HID_Process_MID_T * const process = HID_Dispatcher.HID_CSET.vtbl->find(&HID_Dispatcher, mid_pair);
    if(HID_Dispatcher.HID_CSET.vtbl->end(&HID_Dispatcher) != process)
    {
        process->obj(super, mail);
    }
}

void hid_worker_on_loop(union Worker * const super)
{
    HID_Process_Blinks();
    IPC_Sleep(HID_SHORT_TIME_MS);
}


void hid_worker_on_stop(union Worker * const super)
{
    if(IPC_Unsubscribe(HID_Mailist, Num_Elems(HID_Mailist)))
    {

    }
}

void Populate_HID_Worker(union HID_Worker * const this)
{
    if(NULL == HID_Worker.vtbl)
    {
        Populate_Worker(&HID_Worker.Worker, 
        HID_WORKER_TID,
        HID_Worker_Mailbox,
        Num_Elems(HID_Worker_Mailbox));
        Object_Init(&HID_Worker.Object,
        &HID_Worker_Class.Class,
        sizeof(HID_Worker_Class.Worker));

        HID_Worker_Class.Worker.on_start = hid_worker_on_start;
        HID_Worker_Class.Worker.on_mail  = hid_worker_on_mail;
        HID_Worker_Class.Worker.on_loop  = hid_worker_on_loop;
        HID_Worker_Class.Worker.on_stop  = hid_worker_on_stop;
        Populate_HID_Dispatcher(&Populate_HID_Dispatcher);
    }
    _clone(this, HID_Worker);
}
