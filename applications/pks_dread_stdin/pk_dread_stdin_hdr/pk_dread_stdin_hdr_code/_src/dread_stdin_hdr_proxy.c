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

/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "dread_stdin_hdr_proxy.h"
#include "tb.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Local X-Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Define Macros
 *=====================================================================================*/
#define DREAD_STDIN_NO_PARAMS(PARAM)
#define DREAD_STDIN_SEND_INFO_PARAMS(PARAM) ,PARAM(uint8_t const *, info),PARAM(size_t const, info_size)
/*=====================================================================================* 
 * Local Type Definitions
 *=====================================================================================*/
 
/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/
static void Dr_Stdin_Hdr_Proxy_v_send_info(Dr_Stdin_Hdr super,  uint8_t const * info , size_t const info_size);
static bool_t  Dr_Stdin_Hdr_Proxy_v_is_connection_ready(Dr_Stdin_Hdr super);
/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
Define_Class(Dr_Stdin_Hdr_Proxy, DREAD_STDIN_HDR_PROXY_CTOR)
/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/
void Dr_Stdin_Hdr_Proxy_v_send_info(Dr_Stdin_Hdr super, uint8_t const * info , size_t const info_size)
{
   Dr_Stdin_Info_T stdin_info;
   stdin_info.id = super->id;
   stdin_info.info = info;
   stdin_info.info_size = info_size;

   TB_send(DREAD_STDIN_WORKER, DREAD_STDIN_PROCESS, DREAD_STDIN_SEND_INFO, &stdin_info, sizeof(stdin_info));
}

bool_t Dr_Stdin_Hdr_Proxy_v_is_connection_ready(Dr_Stdin_Hdr super)
{
   TB_Mail_Id_T mail_list[] = {DREAD_STDIN_IS_CONNECTION_RDY_RPT};
   TB_Mail mail;

   if(TB_subscribe_mail_list(mail_list, Num_Elems(mail_list)))
   {
      TB_send(DREAD_STDIN_WORKER, DREAD_STDIN_PROCESS, DREAD_STDIN_IS_CONNECTION_RDY, NULL, 0);

      mail = TB_retreive_from_mail_list(mail_list, Num_Elems(mail_list), TB_RETRIEVE_TOUT_MS);

      TB_unsubscribe_mail_list(mail_list, Num_Elems(mail_list));
   }
   Isnt_Nullptr(mail, false);
   Isnt_Nullptr(mail->data, false);


   return (bool_t)mail->data;
}
/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
void Dr_Stdin_Hdr_Proxy_Ctor(Dr_Stdin_Hdr_Proxy this, uint8_t const id)
{
   Dr_Stdin_Hdr_Ctor(&this->super, id);
   Acc_Member(Object, this)->vtable = (struct Object_VTable_T *)&Dr_Stdin_Hdr_Proxy_VTable_Obj;
   Acc_Method(Object, this)->destroy = Dr_Stdin_Hdr_Proxy_Dtor;
   Acc_Method(Dr_Stdin_Hdr, this)->send_info = Dr_Stdin_Hdr_Proxy_v_send_info;
   Acc_Method(Dr_Stdin_Hdr, this)->is_connection_ready = Dr_Stdin_Hdr_Proxy_v_is_connection_ready;
}

Define_Virtual_Void_VTable_Inherits(Dr_Stdin_Hdr_Proxy, Dr_Stdin_Hdr, send_info, DREAD_STDIN_SEND_INFO_PARAMS)
Define_Virtual_VTable_Inherits(bool_t, false, Dr_Stdin_Hdr_Proxy, Dr_Stdin_Hdr, is_connection_ready, DREAD_STDIN_NO_PARAMS);
/*=====================================================================================* 
 * dread_stdin_hdr_proxy.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
