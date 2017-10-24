#include "data_collector.h"

typedef enum
{
   DC_STATE_IDLE,
   DC_STATE_WAIT_DATA,
   DC_STATE_VALIDATE_DATA,
   DC_STATE_STORAGE,
   DC_STATE_MAX
} DC_STATE_T;

static void dcfsm_delete(struct Object * const obj);
static void dcfsm_req_stdin_data(struct FSM * const fsm, union Mail * const mail);
static void dcfsm_validate_stdin_data(struct FSM * const fsm, union Mail * const mail);
static void dcfsm_handle_stdin_err(struct FSM * const fsm, union Mail * const mail);
static void dcfsm_completed(struct FSM * const fsm, union Mail * const mail);

union FSM_Class DCFSM_Class = 
{
  {&FSM_Class.Class, dcfsm_delete}
}

static union FSM DCFSM = {NULL};

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

void dcfsm_req_stdin_data(struct FSM * const fsm, union Mail * const mail)
{
   DC_Timer_Poll_Data.vtbl->stop(&DC_Timer_Poll_Data);
   DC_Timer_Wait_Data.vtbl->start(&DC_Timer_Wait_Data);
   IPC_Send(STDIN_TID, STDIN_PBC_REQ_DATA_MID, NULL, 0UL);
}

void dcfsm_validate_stdin_data(struct FSM * const fsm, union Mail * const mail)
{
   struct STDIN_Reg * reg = mail->data;
   if(sizeof(struct STDIN_Reg) == mail->data_size)
   {
      if(dc_is_valid(reg.raw, 16U)
      {
         IPC_Send_Self(DC_INT_VALID_DATA_MID, reg.raw, 16U);
      }
   } 
}

void dcfsm_handle_stdin_err(struct FSM * const fsm, union Mail * const mail)

   DC_ERR_T stdin_err = *mail->data;
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
   DC_Timer_Poll_Data.vtbl->start(&DC_Timer_Poll_Data);
}

void dcfsm_store_data(struct FSM * const fsm, union Mail * const mail)
{
   static char datetime[] = {"dd/mm/yyy hh:mm:ss"};
   sprintf(datetime, "%2d/%2d/%4d %2d:%2d:%2d",
      DC_Datetime.day, DC_Datetime.month, DC_Datetime.year,
      DC_Datetime.hour, DC_Datetime.minutes, DC_Datetime.seconds);
   uint32_t rc = DStorage_File.vtbl->append(&DStorage_File, mail->data, mail->data_size);
   if( 0 != rc)
   {
      IPC_Send_Self(DC_INT_COMPLETED_STORAGE_MID, NULL, 0);
   }
   else
   {
      IPC_Send_Self(DC_INT_INVALID_DATA_MID, reg.raw, 16U);
   }

   DC_Timer_Poll_Data.vtbl->start(&DC_Timer_Poll_Data);
}

void dcfsm_completed(struct FSM * const fsm, union Mail * const mail)
{
}

void Alloc_DCFSM(union FSM * const fsm)
{
   if(NULL == DCFSM.vtbl)
   {
      Populate_FSM(&DCFSM, DC_Statechart, Num_Elems(DC_Statechart));
      Object_Init(&DCFSM.Object, &DCFSM_Class.Class, sizeof(DCFSM_Class);
      DCFSM_Class.init = dcfsm_init;
      DCFSM_Class.done = dcfsm_done;
   }
   *fsm = &DCFSM;
}
