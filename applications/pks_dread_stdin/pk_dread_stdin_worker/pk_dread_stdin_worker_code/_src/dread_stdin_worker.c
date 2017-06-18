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

/*=====================================================================================* 
 * Local Type Definitions
 *=====================================================================================*/
struct Dr_Stdin_Handler_T
{
   IPC_Mail_Id_T id;
   void (*process)(Dr_Stdin_Server_T * const, void const * data, size_t const size);
};
/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/
static void Dr_Stdin_Worker_on_start(Worker_T * const super);
static void Dr_Stdin_Worker_on_loop(Worker_T * const super);
static void Dr_Stdin_Worker_on_stop(Worker_T * const super);

static int Dr_Stdin_Handler_Sort(void const * a, void const * b)
{
   return 0;
}
/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
CLASS_DEFINITION

struct Dr_Stdin_Handler_T Dr_Stdin_Handler[] =
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
void Dr_Stdin_Worker_init(void)
{
   printf("%s \n", __FUNCTION__);
   Dr_Stdin_Worker_Obj.Worker = Worker();
   Dr_Stdin_Worker_Obj.stdin_server = Dr_Stdin_Server();

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
   Dr_Stdin_Worker_T * const this = _dynamic_cast(Dr_Stdin_Worker, super);
   Isnt_Nullptr(this, );
   this->stdin_server.vtbl->ctor(this, 0);
   qsort(Dr_Stdin_Handler,Num_Elems(Dr_Stdin_Handler), sizeof(*Dr_Stdin_Handler), Dr_Stdin_Handler_Sort);
}

void Dr_Stdin_Worker_on_loop(Worker_T * const super)
{
   Mail_T * const mail = IPC_retreive_mail(IPC_RETRIEVE_TOUT_MS);
   Isnt_Nullptr(mail,);
   Dr_Stdin_Worker_T * const this = _dynamic_cast(Dr_Stdin_Worker, super);
   Isnt_Nullptr(this, );

   struct Dr_Stdin_Handler_T * handle = (struct Dr_Stdin_Handler_T * )bsearch(&mail->mail_id,
         Dr_Stdin_Handler, Num_Elems(Dr_Stdin_Handler), sizeof(*Dr_Stdin_Handler), Dr_Stdin_Handler_Sort);

   Isnt_Nullptr(handle,);
   handle->process(&this->stdin_server, mail->data, mail->data_size);
}

void Dr_Stdin_Worker_on_stop(Worker_T * const super)
{
   Dr_Stdin_Worker_T * const this = _dynamic_cast(Dr_Stdin_Worker, super);
   Isnt_Nullptr(this, );
}
/*=====================================================================================* 
 * dread_stdin_worker.c
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
