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
#define CLASS_IMPLEMENTATION
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

/*=====================================================================================* 
 * Local Type Definitions
 *=====================================================================================*/
 struct Dr_HID_Handler_T
 {
    IPC_Mail_Id_T mail_id;
    void (*process)(Dr_HID_Server_T * const server, void const * data, size_t const data_size);
 };
/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/
static void Dr_HID_Worker_on_start(Worker_T * const super);
static void Dr_HID_Worker_on_loop(Worker_T * const super);
static void Dr_HID_Worker_on_stop(Worker_T * const super);
static int Dr_HID_Handler_Compare(void const * a, void const * b);
/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
CLASS_DEFINITION
static struct Dr_HID_Handler_T Dr_HID_Handler[] =
{

};
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

int Dr_HID_Handler_Compare(void const * a, void const * b)
{
   IPC_Mail_Id_T const * hid_a = (IPC_Mail_Id_T const *) a;
   IPC_Mail_Id_T const * hid_b = (IPC_Mail_Id_T const *) b;
   Isnt_Nullptr(a, 1);
   Isnt_Nullptr(b, -1);
   return (*hid_a - * hid_b);
}
/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
void Dr_HID_Worker_on_start(Worker_T * const super)
{
   Dr_HID_Worker_T * const this = _dynamic_cast(Dr_HID_Worker, super);
   Isnt_Nullptr(this,);
   qsort(&Dr_HID_Handler, Num_Elems(Dr_HID_Handler), sizeof(*Dr_HID_Handler),
         Dr_HID_Handler_Compare);
}

void Dr_HID_Worker_on_loop(Worker_T * const super)
{
   Dr_HID_Worker_T * const this = _dynamic_cast(Dr_HID_Worker, super);
   Mail_T * const mail = IPC_retreive_mail(IPC_RETRIEVE_TOUT_MS);
   Isnt_Nullptr(this, );
   Isnt_Nullptr(mail, );
   struct Dr_HID_Handler_T * handle = (struct Dr_HID_Handler_T *)bsearch(&mail->mail_id,
         Dr_HID_Handler, Num_Elems(Dr_HID_Handler), sizeof(*Dr_HID_Handler),
         Dr_HID_Handler_Compare);
   Isnt_Nullptr(handle,);

   handle->process(&this->hid_server, mail->data, mail->data_size);
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
