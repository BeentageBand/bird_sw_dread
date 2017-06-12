/*=====================================================================================*/
/**
 * dread_stdin_worker.c
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
#include "ipc.h"
#include "dread_stdin_worker.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Local X-Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Define Macros
 *=====================================================================================*/
CLASS_DEFINITION
/*=====================================================================================* 
 * Local Type Definitions
 *=====================================================================================*/
 
/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/
static void Dr_Stdin_Worker_on_start(Worker_T * const super);
static void Dr_Stdin_Worker_on_loop(Worker_T * const super);
static void Dr_Stdin_Worker_on_stop(Worker_T * const super);
/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/
void Dr_Stdin_Worker_init(void)
{
   printf("%s \n", __FUNCTION__);
   Dr_Stdin_Worker_Obj.Worker = Worker();

   memcpy(&Dr_Stdin_Worker_Vtbl.Worker, Dr_Stdin_Worker_Obj.Worker.vtbl, sizeof(Dr_Stdin_Worker_Vtbl.Worker));
   Dr_Stdin_Worker_Vtbl.Worker.Task.Object.rtti = &Dr_Stdin_Worker_Rtti;
   Dr_Stdin_Worker_Vtbl.Worker.Task.Object.destroy = Dr_Stdin_Worker_Dtor;
   Dr_Stdin_Worker_Vtbl.Worker.on_start = Dr_Stdin_Worker_on_start;
   Dr_Stdin_Worker_Vtbl.Worker.on_loop = Dr_Stdin_Worker_on_loop;
   Dr_Stdin_Worker_Vtbl.Worker.on_stop = Dr_Stdin_Worker_on_stop;

   Dr_Stdin_Worker_Obj.vtbl = &Dr_Stdin_Worker_Vtbl;

   Object_update_info(&Dr_Stdin_Worker_Obj.Worker.Task.Object, Worker().rtti->rtti);
}
void Dr_Stdin_Worker_shut(void) {}

void Dr_Stdin_Worker_Dtor(Object_T * const obj)
{
}
/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
void Dr_Stdin_Worker_on_start(Worker_T * const super)
{
   /*TODO start stdin */
}

void Dr_Stdin_Worker_on_loop(Worker_T * const super)
{
   Mail_T * const mail = IPC_retreive_mail(IPC_RETRIEVE_TOUT_MS);
   Isnt_Nullptr(mail,);
   /* TODO hsm event handler */
}

void Dr_Stdin_Worker_on_stop(Worker_T * const super)
{
   /*TODO stop stdin */
}
/*=====================================================================================* 
 * dread_stdin_worker.c
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
