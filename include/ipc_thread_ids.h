#ifndef IPC_USET_H_
#define IPC_USET_H_
 
#define IPC_THREAD_LIST(TASK_ID) \
TASK_ID(APP_WORKER_TID,      "APP") \
TASK_ID(HID_WORKER_TID,      "HID") \

#endif /*IPC_USET_H_*/
