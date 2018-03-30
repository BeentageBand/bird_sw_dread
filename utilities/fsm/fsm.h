#ifndef FSM_H_
#define FSM_H_

#include "mail.h"

union FSM;
typedef uint32_t FSM_State_T;
typedef bool_t (*FSM_Transition_Func_T) (union FSM * const, union Mail * const);

struct FSM_Statechart
{
   FSM_State_T curr_state;
   IPC_MID_T signal;
   FSM_State_T next_state;
   FSM_Transition_Func_T transition_to;
}FSM_Statechart_T;

union FSM
{
   struct FSM_Class _private * _private vtbl;
   struct
   {
     struct Object Object;
     FSM_State_T _private state;
     struct FSM_Statechart _private * _private statechart;
     uint32_t _private stchrt_size;
   };
}FSM_T;

struct FSM_Class
{
	struct Class Class;
	void (* _private init)(union FSM * const);
	void (* _private done)(union FSM * const);
	void (* _private dispatch)(union FSM * const this, union Mail * const);
};

extern struct FSM_Class _private FSM_Class;

extern void Populate_FSM(union FSM * const this,
   struct FSM_Statechart * const statechart, uint32_t const stchrt_size);

#endif /*FSM_H_*/
