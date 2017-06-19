/*=====================================================================================*/
/**
 * sw_dread_launcher.cpp
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#define CLASS_IMPLEMENTATION
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "ipc_ext.h"
#include "ipc_light.h"
#include "ipc_linux_task.h"
#include "ipc_linux_timestamp.h"
#include "publisher_ext.h"
#include "hamatora_sched_def.h"
#include "dread_hid_task.h"
#include "dread_stdin_worker.h"
#include "hamatora_sched.h"

/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Local X-Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Define Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Type Definitions
 *=====================================================================================*/
 
/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
static IPC_Linux_Task_T * linux_task = NULL;
static IPC_Linux_Timestamp_T * linux_timestamp = NULL;
static IPC_Light_T * light = NULL;
static bool_t Is_Singleton = false;
static Dr_Stdin_Worker_T Dr_Stdin = Dr_Stdin_Worker();
static Dr_HID_Worker_T Dr_HID = Dr_HID_Worker();
/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
void Singleton_Publisher(Publisher_T * const singleton)
{

}

void Singleton_IPC(IPC_T ** singleton)
{
   if(!Is_Singleton)
   {
      linux_task = IPC_Linux_Task_new();
      linux_timestamp = IPC_Linux_Timestamp_new();
      light = IPC_Light_new();

      light->vtbl->ctor(light, IPC_SINGLE_PROCESS, 10);
      linux_timestamp->vtbl->ctor(linux_timestamp, IPC_SINGLE_PROCESS, 10 , &light->IPC);
      linux_task->vtbl->ctor(linux_task, IPC_SINGLE_PROCESS, 10, &linux_timestamp->IPC_Decorator.IPC);
   }

   *singleton = &linux_task->IPC_Decorator.IPC;
}

int main(void)
{
   Dr_Stdin.Worker.vtbl->ctor(&Dr_Stdin.Worker, DREAD_STDIN_WORKER, IPC_self_pid());
   Dr_Stdin.Worker.vtbl->ctor(&Dr_Stdin.Worker, DREAD_HID_WORKER, IPC_self_pid());
   Hama_Sched_run_all_apps();
   return 0;
}
/*=====================================================================================* 
 * sw_dread_launcher.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
