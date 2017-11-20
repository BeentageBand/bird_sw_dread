/*=====================================================================================*/
/**
 * ipc_uset.h
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#ifndef IPC_USET_H_
#define IPC_USET_H_

#ifdef __cplusplus
extern "C" {
#endif

#define IPC_WORKERS_IDS(TASK_ID) \
TASK_ID(SINGLE, DREAD_DC_TID,    "STD INPUT FOR DREAD SW") \
TASK_ID(SINGLE, DREAD_STORAGE_TID, "STD INPUT FOR DREAD SW") \
TASK_ID(SINGLE, DREAD_HID_TID,      "STD INPUT FOR DREAD SW") \


#undef TASK_ID
#define TASK_ID(pid, task, description) task,

#undef IPC_TASK_ID
#define IPC_TASK_ID(task, description) task,
enum
{
   IPC_BEGIN_TASK_ID = 0,
   IPC_WORKERS_IDS(TASK_ID)
   IPC_TOTAL_TASK_IDS_ITEMS
};

#undef PROCESS_ID
#define PROCESS_ID(pid, task, description) task##_PROCESS = IPC_##pid##_PROCESS,
enum
{
   IPC_SINGLE_PROCESS,
   IPC_WORKERS_IDS(PROCESS_ID)
   IPC_TOTAL_PROCESS_IDS_ITEMS
};

#ifdef __cplusplus
}
#endif

#endif /*IPC_TASK_IDS_H_*/
