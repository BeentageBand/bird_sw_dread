#ifndef IPC_MAIL_LIST_H_
#define IPC_MAIL_LIST_H_

#include "application_mailist.h"
#include "data_reg_mailist.h"
#include "hid_mailist.h"
#include "worker_mailist.h"

#define IPC_INTERNAL_MAILIST(X) \
   APP_INT_MAILIST(X) \
   DATA_REG_INT_MAILIST(X) \
   DATA_POST_INT_MAILIST(X) \
   HID_INT_MAILIST(X) \
   WORKER_INT_MAILIST(X) \

#define IPC_PUBLIC_MAILIST(X) \
   APP_PBC_MAILIST(X) \
   DATA_REG_PBC_MAILIST(X) \
   DATA_POST_PBC_MAILIST(X) \
   WORKER_PBC_MAILIST(X)  \

#define IPC_RETRIEVE_TOUT_MS (500U)

#endif /*IPC_MAIL_LIST_H_*/
