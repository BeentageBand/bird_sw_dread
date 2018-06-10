#ifndef DATA_COLLECTOR_H_
#define DATA_COLLECTOR_H_

#include "fsm.h"

#ifdef __cplusplus
extern "C"{
#endif
typedef enum DC_ERR
{
   DC_OK,
   DC_DATA_TIMEOUT_ERR,
   DC_INVALID_DATA_ERR,
   DC_INVALID
}DC_ERR_T;

typedef enum
{
   DC_STATE_IDLE,
   DC_STATE_WAIT_DATA,
   DC_STATE_VALIDATE_DATA,
   DC_STATE_STORAGE,
   DC_STATE_MAX
} DC_STATE_T;

typedef union DCFSM_Class
{
   struct
   {
      FSM_Class_T FSM;
      void (*_private init)(union DCFSM * const);
      void (*_private done)(union DCFSM * const);
   };
   struct State_Machine_Class State_Machine;
   struct Class Class;
}DCFSM_Class_T;

typedef union DCFSM
{
   DCFSM_Class_T _private * _private vtbl;
   union FSM FSM;
   union State_Machine State_Machine;
   struct Object Object;
}DCFSM_T;

extern DCFSM_Class_T _private DCFSM_Class;

extern union DCFSM * Alloc_Data_Collector(void);

#define DCFSM_FSM(cb) \
   FSM_STATE_DEF(cb, DC_STATE_IDLE, \
         FSM_TRANSITION_DEF(cb, DC_INT_POLL_DATA_MID, DC_STATE_WAIT_DATA, dcfsm_req_stdin_data) \
         ) \
   FSM_STATE_DEF(cb, DC_STATE_WAIT_DATA, \
         FSM_TRANSITION_DEF(cb, STDIN_PBC_INCOMING_DATA_MID, DC_STATE_VALIDATE_DATA, dcfsm_validate_stdin_data) \
         FSM_TRANSITION_DEF(cb, DC_INT_STDIN_DATA_TIMEOUT_MID, DC_STATE_IDLE, dcfsm_handle_stdin_err) \
         ) \
   FSM_STATE_DEF(cb, DC_STATE_VALIDATE_DATA, \
         FSM_TRANSITION_DEF(cb, DC_INT_VALID_DATA_MID, DC_STATE_STORAGE, dcfsm_store_data) \
         FSM_TRANSITION_DEF(cb, DC_INT_INVALID_DATA_MID, DC_STATE_IDLE, dcfsm_handle_stdin_err) \
         ) \
   FSM_STATE_DEF(cb, DC_STATE_STORAGE, \
         FSM_TRANSITION_DEF(cb, DC_INT_COMPLETED_STORAGE_MID, DC_STATE_IDLE, dcfsm_completed) \
         FSM_TRANSITION_DEF(cb, DC_INT_STORAGE_ERROR_MID, DC_STATE_IDLE, dcfsm_handle_stdin_err) \
         ) \

#ifdef __cplusplus
}
#endif
#endif /*DATA_COLLECTOR_H_*/
