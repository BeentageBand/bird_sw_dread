#define COBJECT_IMPLEMENTATION
#undef Dbg_FID
#define Dbg_FID DBG_FID_DEF(DREAD_DC_FID, 1)

#include "data_collector.h"
#include "data_collector_wrkr.h"
#include "data_collector_wrkr_cfg.h"
#include "dbg_log.h"
#include "ipc.h"

#define DATA_COLLECTOR_SUB_EV(ad, desc) ad,

static void data_collector_wrkr_init(void);
static void data_collector_wrkr_delete(struct Object * const obj);
static void data_collector_wrkr_on_start(union Worker * const super);
static void data_collector_wrkr_on_loop(union Worker * const super);
static void data_collector_wrkr_on_mail(union Worker * const super, union Mail * const mail);
static void data_collector_wrkr_on_stop(union Worker * const super);

Data_Collector_Wrkr_Class_T Data_Collector_Wrkr_Class =
    {{//Worker
   {//Thread
       {data_collector_wrkr_delete, &Worker_Class.Class},
       NULL,
       NULL,
       NULL
   },
   data_collector_wrkr_on_mail,
   data_collector_wrkr_on_start,
   data_collector_wrkr_on_loop,
   data_collector_wrkr_on_stop
    }};

static DCFSM_T * DCFSM; 
static union Worker Data_Collector_Wrkr = {NULL};
static uint32_t const Data_Collector_Sub_List[] =
    {
   DATA_COLLECTOR_SUB_LIST(DATA_COLLECTOR_SUB_EV)
    };
static union Mail DC_Mailbox_Buff[64] = {0};

void data_collector_wrkr_init(void)
{
  Data_Collector_Wrkr_Class.on_start = data_collector_wrkr_on_start;
  Data_Collector_Wrkr_Class.on_loop = data_collector_wrkr_on_loop;
  Data_Collector_Wrkr_Class.on_mail = data_collector_wrkr_on_mail;
  Data_Collector_Wrkr_Class.on_stop = data_collector_wrkr_on_stop;
}

void data_collector_wrkr_delete(struct Object * const obj)
{
}

void data_collector_wrkr_on_start(union Worker * const super)
{
  union Worker * const this = _cast(Data_Collector_Wrkr, super);
  Isnt_Nullptr(this,);

  Dbg_Info("%s: Worker", __func__);
  DCFSM->vtbl->init(DCFSM);
}

void data_collector_wrkr_on_loop(union Worker * const super)
{
  union Worker * const this = _cast(Data_Collector_Wrkr, super);
  Isnt_Nullptr(this,);
}

void data_collector_wrkr_on_mail(union Worker * const super, union Mail * const mail)
{
  union Worker * const this = _cast(Data_Collector_Wrkr, super);
  Isnt_Nullptr(this,);

  //   Pair_Mail_Router_T * const pmr = DC_MR.vtbl->find(&DC_MR, mail->mid);
  //
  //   if(pmr != DC_MR.vtbl->end(&DCMR))
  //   {
  //pmr->object(mail);
  //}
  DCFSM->vtbl->dispatch(DCFSM, mail);
}

void data_collector_wrkr_on_stop(union Worker * const super)
{
  union Worker * const this = _cast(Data_Collector_Wrkr, super);
  Isnt_Nullptr(this,);

  DCFSM->vtbl->done(DCFSM);
}

union Data_Collector_Wrkr * Allocate_Data_Collector_Wrkr(void)
{
  if(NULL == Data_Collector_Wrkr.vtbl)
    {
      Alloc_Data_Collector(&DCFSM);
      Populate_Worker(&Data_Collector_Wrkr, DREAD_DC_TID, DC_Mailbox_Buff, Num_Elems(DC_Mailbox_Buff));
      Object_Init(&Data_Collector_Wrkr.Object, &Data_Collector_Wrkr_Class.Class,
        sizeof(Data_Collector_Wrkr_Class));
      data_collector_wrkr_init();
      IPC_Subscribe_Mailist(Data_Collector_Sub_List,
             Num_Elems(Data_Collector_Sub_List));
    }
  return &Data_Collector_Wrkr;
}
