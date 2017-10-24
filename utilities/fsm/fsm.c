#define COBJECT_IMPL
#include "fsm.h"

static void fsm_delete(struct Object * const obj);
static void fsm_init(union FSM * const this);
static void fsm_done(union FSM * const this);
static void fsm_dispatch(union FSM * const this);

union FSM_Class FSM_Class = 
{
   {NULL, fsm_delete},
   fsm_init,
   fsm_done,
   fsm_dispatch,
};


static union FSM FSM = {NULL};

void fsm_delete(struct Object * const obj)
{
 
}

void fsm_init(union FSM * const this)
{
    
}

void fsm_done(union FSM * const this)
{}

void fsm_dispatch(union FSM * const this, union Mail * const mail)
{

   struct FSM_Statechart st = this->statechart;
   for(; st != (this->statechart + this->stchrt_size); ++st)
   {
      if(this->state == st->curr_state)
      {
         if(mail->mid == st->signal)
         {
            st->transition_to(fsm, mail);
            this->state = st->next_state;
            break;
         }
      }
   }
}

void Populate_FSM(union FSM * const this,
   struct FSM_Statechart * const statechart, uint32_t const stchrt_size)
{
   if(NULL == FSM.vtbl)
   {
      FSM.state = 0;
      FSM.statechart = statechart;
      FSM.stchrt_size = stchrt_size;
      FSM.vtbl = &FSM_Class;
   }
   memcpy(this, &FSM, sizeof(FSM));
}

#endif /*FSM_H_*/
