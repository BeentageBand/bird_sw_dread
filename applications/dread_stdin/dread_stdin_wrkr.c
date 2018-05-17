#define COBJECT_IMPLEMENTATION
#include "dread_stdin_wrkr.h"
#include "ipc.h"

static void dread_stdin_wrkr_delete(struct Object * const obj);
static void dread_stdin_wrkr_on_mail(union Worker * const, union Mail * const);
static void dread_stdin_wrkr_on_start(union Worker * const);
static void dread_stdin_wrkr_on_loop(union Worker * const);
static void dread_stdin_wrkr_on_stop(union Worker * const);


Dread_StdIn_Wrkr_Class_T Dread_StdIn_Wrkr_Class  = 
{// StdIn
{// Worker
   {// Thread
      {dread_stdin_wrkr_delete, NULL},
      NULL,
      NULL,
   }, // Thread
   dread_stdin_wrkr_on_mail,
   dread_stdin_wrkr_on_start,
   dread_stdin_wrkr_on_loop,
   dread_stdin_wrkr_on_stop,
}//Worker
};// StdIn

static Dread_StdIn_Wrkr_T Dread_StdIn_Wrkr = {NULL};
static union Mail Dread_StdIn_Mailbox_Buff[64] = {0};

void dread_stdin_wrkr_delete(struct Object * const obj)
{

}

void dread_stdin_wrkr_on_mail(union Worker * const worker, union Mail * const mail)
{
}

void dread_stdin_wrkr_on_start(union Worker * const worker)
{
   Dbg_Info("Dread StdIn started %d secs", IPC_Clock());
}

void dread_stdin_wrkr_on_loop(union Worker * const worker)
{
   IPC_Sleep(1000);
   Dbg_Info("Watchdog %s", __func__);
}

void dread_stdin_wrkr_on_stop(union Worker * const worker)
{
}


union Dread_StdIn_Wrkr * Alloc_Dread_StdIn_Wrkr(void)
{
   if(NULL == Dread_StdIn_Wrkr.vtbl)
   {
      Populate_Worker(&Dread_StdIn_Wrkr.Worker, 
            DREAD_DS_TID,
            Dread_StdIn_Mailbox_Buff,
            Num_Elems(Dread_StdIn_Mailbox_Buff));
      Dread_StdIn_Wrkr.vtbl = &Dread_StdIn_Wrkr_Class;

   }
   return &Dread_StdIn_Wrkr;
}
