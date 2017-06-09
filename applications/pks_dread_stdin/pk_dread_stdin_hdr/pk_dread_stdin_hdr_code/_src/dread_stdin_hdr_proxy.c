/*=====================================================================================*/
/**
 * dread_stdin_hdr_proxy.cpp
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
#include "dread_stdin_hdr_proxy.h"
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
static void Dr_Stdin_Hdr_Proxy_send_info(Dr_Stdin_Hdr_T * const super,  uint8_t const * info , size_t const info_size);
static bool_t  Dr_Stdin_Hdr_Proxy_is_connection_ready(Dr_Stdin_Hdr_T * const super);
/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
CLASS_DEFINITION
/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/
void Dr_Stdin_Hdr_Proxy_init(void)
{
   printf("%s \n", __FUNCTION__);

   Dr_Stdin_Hdr_Proxy_Obj.Dr_Stdin_Hdr = Dr_Stdin_Hdr();

   memcpy(&Dr_Stdin_Hdr_Proxy_Vtbl.Dr_Stdin_Hdr, Dr_Stdin_Hdr_Proxy_Obj.vtbl,
         sizeof(Dr_Stdin_Hdr_Proxy_Vtbl.Dr_Stdin_Hdr));

   Dr_Stdin_Hdr_Proxy_Vtbl.Dr_Stdin_Hdr.Object.rtti = &Dr_Stdin_Hdr_Proxy_Rtti;
   Dr_Stdin_Hdr_Proxy_Vtbl.Dr_Stdin_Hdr.Object.destroy = Dr_Stdin_Hdr_Proxy_Dtor;

   Dr_Stdin_Hdr_Proxy_Vtbl.Dr_Stdin_Hdr.send_info = Dr_Stdin_Hdr_Proxy_send_info;
   Dr_Stdin_Hdr_Proxy_Vtbl.Dr_Stdin_Hdr.is_connection_ready = Dr_Stdin_Hdr_Proxy_is_connection_ready;

   Dr_Stdin_Hdr_Proxy_Vtbl.ctor = Dr_Stdin_Hdr_Proxy_Ctor;

   Dr_Stdin_Hdr_Proxy_Obj.vtbl = &Dr_Stdin_Hdr_Proxy_Vtbl;
   Object_update_info(&Dr_Stdin_Hdr_Proxy_Obj.Dr_Stdin_Hdr.Object, Dr_Stdin_Hdr().rtti->rtti);

}
void IPC_shut(void) {}

void IPC_Dtor(Object_T * const obj)
{
}

/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
void Dr_Stdin_Hdr_Proxy_Ctor(Dr_Stdin_Hdr_Proxy_T * const this, uint8_t const id)
{
   this->Dr_Stdin_Hdr.vtbl->ctor(&this->Dr_Stdin_Hdr, id);
}

void Dr_Stdin_Hdr_Proxy_send_info(Dr_Stdin_Hdr_T * const  super, uint8_t const * info , size_t const info_size)
{
   Dr_Stdin_Info_T stdin_info;
   stdin_info.id = super->id;
   stdin_info.info = info;
   stdin_info.info_size = info_size;

   IPC_send(DREAD_STDIN_WORKER, DREAD_STDIN_PROCESS, DREAD_STDIN_SEND_INFO, &stdin_info, sizeof(stdin_info));
}

bool_t Dr_Stdin_Hdr_Proxy_is_connection_ready(Dr_Stdin_Hdr_T * const  super)
{
   IPC_Mail_Id_T mail_list[] = {DREAD_STDIN_IS_CONNECTION_RDY_RPT};
   Mail_T mail;

   if(IPC_subscribe_mail_list(mail_list, Num_Elems(mail_list)))
   {
      IPC_send(DREAD_STDIN_WORKER, DREAD_STDIN_PROCESS, DREAD_STDIN_IS_CONNECTION_RDY, NULL, 0);

      mail = IPC_retreive_from_mail_list(mail_list, Num_Elems(mail_list), IPC_RETRIEVE_TOUT_MS);

      IPC_unsubscribe_mail_list(mail_list, Num_Elems(mail_list));
   }
   Isnt_Nullptr(mail, false);
   Isnt_Nullptr(mail->data, false);


   return (bool_t)mail->data;
}
/*=====================================================================================* 
 * dread_stdin_hdr_proxy.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
