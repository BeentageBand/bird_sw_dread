/*=====================================================================================*/
/**
 * dread_stdin_hdr_server.cpp
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
#include "dread_stdin_hdr_ext.h"
#include "dread_stdin_hdr_server.h"
#include "dread_stdin_hdr_set.h"
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
static void Dr_Stdin_Hdr_Server_v_send_info(Dr_Stdin_Hdr super, uint8_t const * info , size_t const info_size);
static bool_t  Dr_Stdin_Hdr_Server_v_is_connection_ready(Dr_Stdin_Hdr super);
/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
Define_Class(Dr_Stdin_Hdr_Server, DREAD_STDIN_HDR_SERVER_CTOR)
/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/
static char Dread_Stdin_Buffer[] = "0123456789 00/00/0000 00:00:00";
/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/
void Dr_Stdin_Hdr_Server_v_send_info(Dr_Stdin_Hdr super, uint8_t const * info , size_t const info_size)
{
   Dr_Stdin_Hdr_Server this = Downcast(Dr_Stdin_Hdr_Server, super);
   uint32_t info_id;
   bool_t successful_sent_info = false;
   Isnt_Nullptr(this, );
   Isnt_Nullptr(info, );

   if((DREAD_STDIN_INFO_SIZE == info_size)&& this->is_connection_ready)
   {
      info_id = Big_Endian_get_u32(info);
      Str_Trait_write_number(Dread_Stdin_Buffer, info, DREAD_STDIN_STR_INFO_SIZE, 10);

      TB_put_date_string(&Dread_Stdin_Buffer[DREAD_STDIN_STR_INFO_SIZE]);
      if(Dr_Stdin_Hdr_Cbk_backup_info(Dread_Stdin_Buffer, sizeof(Dread_Stdin_Buffer)) )
      {
         successful_sent_info = true;
      }
   }

   Dr_Stdin_Cbk_notify_info_result(successful_sent_info);
}

bool_t  Dr_Stdin_Hdr_Server_v_is_connection_ready(Dr_Stdin_Hdr super)
{
   Dr_Stdin_Hdr_Server this = Downcast(Dr_Stdin_Hdr_Server, super);
   Isnt_Nullptr(this, false);
   return this->is_connection_ready;
}
/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
void Dr_Stdin_Hdr_Server_Ctor(Dr_Stdin_Hdr_Server this, uint8_t const id)
{
   Dr_Stdin_Hdr_Ctor(&this->super, id);
   Acc_Member(Object, this)->vtable = (struct Object_VTable_T *)&Dr_Stdin_Hdr_Server_VTable_Obj;
   Acc_Method(Object, this)->destroy = Dr_Stdin_Hdr_Server_Dtor;
   Acc_Method(Dr_Stdin_Hdr, this)->send_info = Dr_Stdin_Hdr_Server_v_send_info;
   Acc_Method(Dr_Stdin_Hdr, this)->is_connection_ready = Dr_Stdin_Hdr_Server_v_is_connection_ready;
}

Define_Virtual_Void_VTable_Inherits(Dr_Stdin_Hdr_Server, Dr_Stdin_Hdr, send_info, DREAD_STDIN_SEND_INFO_PARAMS)
Define_Virtual_VTable_Inherits(bool_t, false, Dr_Stdin_Hdr_Server, Dr_Stdin_Hdr, is_connection_ready, DREAD_STDIN_NO_PARAMS);
/*=====================================================================================* 
 * dread_stdin_hdr_server.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
