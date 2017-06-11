/*=====================================================================================*/
/**
 * dread_hid_task.c
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#define CLASS_DEFINITION
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "ipc.h"
#include "dread_hid_task.h"
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
static void Dr_HID_Worker_on_start(Worker_T * const super);
static void Dr_HID_Worker_on_loop(Worker_T * const super);
static void Dr_HID_Worker_on_stop(Worker_T * const super);
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
void Dr_HID_Worker_init(void)
{
   printf("%s \n", __FUNCTION__);
   Dr_HID_Worker_Obj.Worker = Worker();

   memcpy(&Dr_HID_Worker_Vtbl.Worker, Dr_HID_Worker_Obj.Worker.vtbl, sizeof(Dr_HID_Worker_Vtbl.Worker));
   Dr_HID_Worker_Vtbl.Worker.Task.Object.rtti = &Dr_HID_Worker_Rtti;
   Dr_HID_Worker_Vtbl.Worker.Task.Object.destroy = Dr_HID_Worker_Dtor;
   Dr_HID_Worker_Vtbl.Worker.on_start = Dr_HID_Worker_on_start;
   Dr_HID_Worker_Vtbl.Worker.on_loop = Dr_HID_Worker_on_loop;
   Dr_HID_Worker_Vtbl.Worker.on_stop = Dr_HID_Worker_on_stop;

   Dr_HID_Worker_Obj.vtbl = &Dr_HID_Worker_Vtbl;

   Object_update_info(&Dr_HID_Worker_Obj.Worker.Task.Object, Worker().rtti->rtti);
}
void Dr_HID_Worker_shut(void) {}

void Dr_HID_Worker_Dtor(Object_T * const obj)
{
}
/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
void Dr_HID_Worker_on_start(Worker_T * const super)
{
   /*TODO start hid */
}

void Dr_HID_Worker_on_loop(Worker_T * const super)
{
   Mail_T * const mail = IPC_retreive_mail(IPC_RETRIEVE_TOUT_MS);
   Isnt_Nullptr(mail,);
   /* TODO hsm event handler */
}

void Dr_HID_Worker_on_stop(Worker_T * const super)
{
   /*TODO stop hid */
}
/*=====================================================================================* 
 * dread_hid_task.c
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
