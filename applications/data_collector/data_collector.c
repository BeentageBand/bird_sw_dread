#define COBJECT_IMPLEMENTATION
#include "data_collector.h"
#include "dread_stdin.h"
#include "ipc.h"

typedef enum
{
   DC_STATE_IDLE,
   DC_STATE_WAIT_DATA,
   DC_STATE_VALIDATE_DATA,
   DC_STATE_STORAGE,
   DC_STATE_MAX
} DC_STATE_T;

static bool dc_is_valid(uint8_t const * raw, size_t const size);
static void dcfsm_delete(struct Object * const obj);
static void dcfsm_init(union FSM * const fsm);
static void dcfsm_done(union FSM * const fsm);
static bool dcfsm_req_stdin_data(union FSM * const fsm, union Mail * const mail);
static bool dcfsm_validate_stdin_data(union FSM * const fsm, union Mail * const mail);
static bool dcfsm_handle_stdin_err(union FSM * const fsm, union Mail * const mail);
static bool dcfsm_store_data(union FSM * const fsm, union Mail * const mail);
static bool dcfsm_completed(union FSM * const fsm, union Mail * const mail);

DCFSM_Class_T DCFSM_Class = 
{//FSM
  {dcfsm_delete, &FSM_Class.Class},
  NULL,
  NULL,
  NULL
};

static DCFSM_T DCFSM = {NULL};

static struct FSM_Statechart DC_Statechart[] =
{
   {DC_STATE_IDLE, DC_INT_POLL_DATA_MID, DC_STATE_WAIT_DATA, dcfsm_req_stdin_data},

   {DC_STATE_WAIT_DATA, STDIN_PBC_INCOMING_DATA_MID, DC_STATE_VALIDATE_DATA, dcfsm_validate_stdin_data},
   {DC_STATE_WAIT_DATA, DC_INT_STDIN_DATA_TIMEOUT_MID, DC_STATE_IDLE, dcfsm_handle_stdin_err},

   {DC_STATE_VALIDATE_DATA, DC_INT_VALID_DATA_MID, DC_STATE_STORAGE, dcfsm_store_data},
   {DC_STATE_VALIDATE_DATA, DC_INT_INVALID_DATA_MID, DC_STATE_IDLE, dcfsm_handle_stdin_err},

   {DC_STATE_STORAGE, DC_INT_COMPLETED_STORAGE_MID, DC_STATE_IDLE, dcfsm_completed},
   {DC_STATE_STORAGE, DC_INT_STORAGE_ERROR_MID, DC_STATE_IDLE, dcfsm_handle_stdin_err}
};

static IPC_MID_T DCFSM_Mailist[] = 
{
   STDIN_PBC_INCOMING_DATA_MID
};

bool dc_is_valid(uint8_t const * raw, size_t const size)
{
	//TODO
	return false;
}

void dcfsm_delete(struct Object * const obj)
{
	DCFSM_T * const this = (DCFSM_T *) Object_Cast(&DCFSM_Class.Class, obj);
	this->vtbl->done(this);
}

void dcfsm_init(union FSM * const fsm)
{
	IPC_Subscribe_Mailist(DCFSM_Mailist, Num_Elems(DCFSM_Mailist));
}

void dcfsm_done(union FSM * const fsm)
{
	IPC_Unsubscribe_Mailist(DCFSM_Mailist, Num_Elems(DCFSM_Mailist));
}

bool dcfsm_req_stdin_data(union FSM * const fsm, union Mail * const mail)
{
//TODO   DC_Timer_Poll_Data.vtbl->stop(&DC_Timer_Poll_Data);
   //TODO DC_Timer_Wait_Data.vtbl->start(&DC_Timer_Wait_Data);
   IPC_Send(STDIN_TID, STDIN_PBC_REQ_DATA_MID, NULL, 0UL);
   return true;
}

bool dcfsm_validate_stdin_data(union FSM * const fsm, union Mail * const mail)
{
   struct STDIN_Reg * stdin_reg = mail->payload;
   if(STDIN_REG_SIZE == mail->pay_size)
   {
      if(dc_is_valid(stdin_reg->raw, STDIN_REG_SIZE))
      {
         IPC_Send_Self(DC_INT_VALID_DATA_MID, stdin_reg->raw, STDIN_REG_SIZE);
      }
   } 

   //TODO
   return true;
}

bool dcfsm_handle_stdin_err(union FSM * const fsm, union Mail * const mail)
{
   DC_ERR_T stdin_err = *((DC_ERR_T *)mail->payload);
   switch(stdin_err)
   {
      case DC_DATA_TIMEOUT_ERR:
      {
         break;
      }
      case DC_INVALID_DATA_ERR:
      {
          IPC_Send(USER_FEEDBACK_TID, UF_PBC_INVALID_STDIN_MID, NULL, 0);
          break;
      }
      default: break;
   }
   //TODO DC_Timer_Poll_Data.vtbl->start(&DC_Timer_Poll_Data);
   return DC_OK == stdin_err;
}

bool dcfsm_store_data(union FSM * const fsm, union Mail * const mail)
{
//TODO  static char datetime[] = {"dd/mm/yyy hh:mm:ss"};
//TODO  sprintf(datetime, "%2d/%2d/%4d %2d:%2d:%2d",
//      DC_Datetime.day, DC_Datetime.month, DC_Datetime.year,
//      DC_Datetime.hour, DC_Datetime.minutes, DC_Datetime.seconds);
   uint32_t rc = 0;
   //TODO uint32_t rc = DStorage_File.vtbl->append(&DStorage_File, mail->payload, mail->pay_size);
   if( 0 != rc)
   {
      IPC_Send_Self(DC_INT_COMPLETED_STORAGE_MID, NULL, 0);
   }
   else
   {
      //TODO IPC_Send_Self(DC_INT_INVALID_DATA_MID, reg->raw, 16U);
   }
   //TODO DC_Timer_Poll_Data.vtbl->start(&DC_Timer_Poll_Data);
   return true;
}

bool dcfsm_completed(union FSM * const fsm, union Mail * const mail)
{
	return true;
}

void Alloc_Data_Collector(union FSM ** const fsm)
{
   if(NULL == DCFSM.vtbl)
   {
      Populate_FSM(&DCFSM, DC_Statechart, Num_Elems(DC_Statechart));
      Object_Init(&DCFSM.Object, &DCFSM_Class.Class, sizeof(DCFSM_Class));
      DCFSM_Class.init = dcfsm_init;
      DCFSM_Class.done = dcfsm_done;
   }
   *fsm = &DCFSM;
}
