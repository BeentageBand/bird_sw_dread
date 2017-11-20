#define OBJECT_IMPLEMENTATION

#include "data_collector.h"
#include "data_collector_wrkr.h"
#include "data_collector_wrkr_cfg.h"

static void data_collector_wrkr_init(void);
static void data_collector_wrkr_delete(struct Object * const obj);
static void data_collector_wrkr_on_start(union Worker * const super);
static void data_collector_wrkr_on_loop(union Worker * const super);
static void data_collector_wrkr_on_mail(union Worker * const super, union Mail * const mail);
static void data_collector_wrkr_on_stop(union Worker * const super);

union Worker_Class Data_Collector_Wrkr_Class =
{
   {{&Worker_Class.Class, data_collector_wrkr_delete}},
};

static union Data_Collector * DCFSM; 
static union Worker Data_Collector_Wrkr = {NULL};
static uint32_t const Data_Collector_Sub_List[] =
{
   DATA_COLLECTOR_SUB_LIST(DATA_COLLECTOR_SUB_EV)
};

void data_collector_wrkr_init(void)
{
   Data_Collector_Class.on_start = data_collector_wrkr_on_start;
   Data_Collector_Class.on_loop = data_collector_wrkr_on_loop;
   Data_Collector_Class.on_mail = data_collector_wrkr_on_mail;
   Data_Collector_Class.on_stop = data_collector_wrkr_on_stop;
}

void data_collector_wrkr_delete(struct Object * const obj)
{}

void data_collector_wrkr_on_start(union Worker * const super)
{
   union Worker * const this = _cast(Data_Collector_Wrkr, super);
   Isnt_Nullptr(this,);

   DCFSM->vtbl->init(&DCFSM);
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
   Pair_Mail_Router_T * const pmr = DC_MR.vtbl->find(&DC_MR, mail->mid);

   if(pmr != DC_MR.vtbl->end(&DCMR))
   {
      pmr->object(mail);
   }
   DCFSM->vtbl->wrkratch(&DCFSM, mail->mid, mail->data, mail->data_size);
}

void data_collector_wrkr_on_stop(union Worker * const super)
{
   union Worker * const this = _cast(Data_Collector_Wrkr, super);
   Isnt_Nullptr(this,);

   DCFSM->vtbl->done(&DCFSM);
}

void Allocate_Data_Collector_Wrkr(union Worker ** const this)
{
   if(NULL == Data_Collector_Wrkr.vtbl)
   {
      Populate_Data_Collector(&DCFSM);
      Populate_Worker(&Data_Collector_Wrkr, DREAD_DC_TID);
      Object_Init(&Data_Collector_Wrkr.Object, &Data_Collector_Class.Class,
         sizeof(Data_Collector_Class));
      data_collector_wrkr_init();
      Data_Collector_Wrkr.vtbl->subscribe(Data_Collector_Sub_List,
         Num_Elems(Data_Collector_Sub_List));
   }
   *this = &Data_Collector_Wrkr;
}


