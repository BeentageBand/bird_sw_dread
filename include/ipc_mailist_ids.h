#ifndef IPC_MAIL_LIST_H_
#define IPC_MAIL_LIST_H_

#include "data_collector_evs.h" 
#include "dread_stdin_evs.h"
#include "user_feedback_evs.h" 
#include "worker_evs.h"

#define IPC_INTERNAL_MAILIST(X) \
   DATA_COLLECTOR_INT_MAILIST(X)\
   STDIN_INT_MAILIST(X) \
   UF_INT_MAILIST(X) \
   WORKER_INT_MAILIST(X)  \

#define IPC_PUBLIC_MAILIST(X) \
   DATA_COLLECTOR_PBC_MAILIST(X)\
   STDIN_PBC_MAILIST(X) \
   UF_PBC_MAILIST(X) \
   WORKER_PBC_MAILIST(X)  \

#define IPC_RETRIEVE_TOUT_MS (500U)

#endif /*IPC_MAIL_LIST_H_*/
