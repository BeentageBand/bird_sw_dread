#ifndef HID_PROCESS_H_
#define HID_PROCESS_H_

#include "hid_types.h"
#include "hid_worker.h"

#define HID_CSET CHash_Set_Pair_IPC_MID_HID_Process

typedef void (*HID_Process_T)(union HID_Worker * const, union Mail * const);

#define CHash_Map_Params IPC_MID, HID_Process
#include "chash_map.h"
#undef CHash_Map_Params 

typedef CHash_Map_IPC_MID_HID_Process_T HID_Dispatcher_T;
typedef Pair_IPC_MID_HID_Process_T HID_Process_MID_T;

extern void Populate_HID_Dispatcher(HID_Dispatcher_T * const dispatcher);

extern void HID_Process_Blinks(void);

#endif /*HID_PROCESS_H_*/
