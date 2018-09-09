#define COBJECT_IMPLEMENTATION
#define Dbg_FID CONSOLE_FID, 3

#include "application.h"
#include "dread_console_worker.h"
#include "dbg_log.h"
#include "ipc.h"

#define Dread_Console_MID_Subcription(mid, proc) mid,

static void dread_console_worker_delete(struct Object * const obj);
static void dread_console_worker_on_start(union Worker * const super);
static void dread_console_worker_on_mail(union Worker * const super, union Mail * const mail);
static void dread_console_worker_on_loop(union Worker * const super);
static void dread_console_worker_on_stop(union Worker * const super);

static union Dread_Console_Worker Dread_Console_Worker = {NULL};
static union Mail Dread_Console_Worker_Mailbox[64] = {0};
static char StdIn_Buff[8][]
union Dread_Console_Worker_Class Dread_Console_Worker_Class =
{
        {dread_console_worker_delete, NULL}
};

void dread_console_worker_delete(struct Object * const obj)
{}

void dread_console_worker_on_start(union Worker * const super)
{
    if(IPC_Subscribe_Mailist(Dread_Console_Mailist, Num_Elems(Dread_Console_Mailist)))
    {

    }
    Application_initialized();
}

void dread_console_worker_on_mail(union Worker * const super, union Mail * const mail)
{
    union Dread_Console_Worker * const this = _cast(Dread_Console_Worker, super);
}

void dread_console_worker_on_loop(union Worker * const super)
{
    union Dread_Console_Worker * const this = _cast(Dread_Console_Worker, super);
    Isnt_Nullptr(this, );
    //TODO read stdin
    int argc = 1;
    this->dread_console.vtbl->on_call(&this->dread_console, argc, argv);
}

void dread_console_worker_on_stop(union Worker * const super)
{
    if(IPC_Unsubscribe_Mailist(Dread_Console_Mailist, Num_Elems(Dread_Console_Mailist)))
    {

    }
    Application_terminated();
}

void Populate_Dread_Console_Worker(union Dread_Console_Worker * const this)
{
    if(NULL == Dread_Console_Worker.vtbl)
    {
        Populate_Worker(&Dread_Console_Worker.Worker,
                DATA_POST_WORKER_TID,
                Dread_Console_Worker_Mailbox,
                Num_Elems(Dread_Console_Worker_Mailbox));
        Object_Init(&Dread_Console_Worker.Object,
                &Dread_Console_Worker_Class.Class,
                sizeof(Dread_Console_Worker_Class.Worker));

        Dread_Console_Worker_Class.Worker.on_start = dread_console_worker_on_start;
        Dread_Console_Worker_Class.Worker.on_mail  = dread_console_worker_on_mail;
        Dread_Console_Worker_Class.Worker.on_loop  = dread_console_worker_on_loop;
        Dread_Console_Worker_Class.Worker.on_stop  = dread_console_worker_on_stop;
        Populate_Dread_Console_Dispatcher(&Dread_Console_Dispatcher);
    }
    _clone(this, Dread_Console_Worker);
}
