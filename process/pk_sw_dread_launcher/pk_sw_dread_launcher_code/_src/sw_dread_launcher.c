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

/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "ipc_ext.h"
#include "ipc_light.h"
#include "ipc_linux_task.h"
#include "ipc_linux_timestamp.h"
#include "publisher_ext.h"
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
      linux_task->vtbl->ctor(linux_task, IPC_SINGLE_PROCESS, 10, &linux_timestamp->IPC_Decorator);
   }

   *singleton = linux_task;
}

int main(void)
{
   IPC_self_pid();

   _delete(light);
   _delete(linux_task);
   _delete(linux_timestamp);
   return 0;
}
/*=====================================================================================* 
 * sw_dread_launcher.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
