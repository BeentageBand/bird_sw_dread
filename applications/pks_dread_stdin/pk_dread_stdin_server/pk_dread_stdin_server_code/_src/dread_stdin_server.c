/*=====================================================================================*/
/**
 * dread_stdin_server.c
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
#include "dread_stdin_ext.h"
#include "dread_stdin_set.h"
#include "convert_endianess.h"
#include "convert_str.h"
#include "ipc.h"
#include "dread_stdin_server.h"
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
static void Dr_Stdin_Server_Ctor(Dr_Stdin_Server_T * const this, uint8_t const id);
static void Dr_Stdin_Server_send_info(Dr_Stdin_T * const super, uint8_t const * info , size_t const info_size);
static bool_t  Dr_Stdin_Server_is_connection_ready(Dr_Stdin_T * const super);
/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
CLASS_DEFINITION
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
void Dr_Stdin_Server_init(void)
{
   printf("%s \n", __FUNCTION__);

   Dr_Stdin_Server_Obj.Dr_Stdin = Dr_Stdin();
   Dr_Stdin_Server_Obj.hsm = Hama_HSM();
   Dr_Stdin_Server_Obj.is_connection_ready = false;

   memcpy(&Dr_Stdin_Server_Vtbl.Dr_Stdin, Dr_Stdin_Server_Obj.vtbl,
         sizeof(Dr_Stdin_Server_Vtbl.Dr_Stdin));

   Dr_Stdin_Server_Vtbl.Dr_Stdin.Object.rtti = &Dr_Stdin_Server_Rtti;
   Dr_Stdin_Server_Vtbl.Dr_Stdin.Object.destroy = Dr_Stdin_Server_Dtor;

   Dr_Stdin_Server_Vtbl.Dr_Stdin.send_info = Dr_Stdin_Server_send_info;
   Dr_Stdin_Server_Vtbl.Dr_Stdin.is_connection_ready = Dr_Stdin_Server_is_connection_ready;

   Dr_Stdin_Server_Vtbl.ctor = Dr_Stdin_Server_Ctor;

   Dr_Stdin_Server_Obj.vtbl = &Dr_Stdin_Server_Vtbl;
   Object_update_info(&Dr_Stdin_Server_Obj.Dr_Stdin.Object, Dr_Stdin().rtti->rtti);

}
void Dr_Stdin_Server_shut(void) {}

void Dr_Stdin_Server_Dtor(Object_T * const obj)
{
}

/*=====================================================================================*
 * Exported Function Definitions
 *=====================================================================================*/
void Dr_Stdin_Server_Ctor(Dr_Stdin_Server_T * const this, uint8_t const id)
{
   this->Dr_Stdin.vtbl->ctor(&this->Dr_Stdin, id);
   this->hsm.vtbl->ctor(&this->hsm, 0, NULL, 0, NULL, 0);
}

void Dr_Stdin_Server_send_info(Dr_Stdin_T * const super, uint8_t const * info , size_t const info_size)
{
   Dr_Stdin_Server_T * const this = _dynamic_cast(Dr_Stdin_Server, super);
   uint32_t info_id;
   bool_t successful_sent_info = false;
   Isnt_Nullptr(this, );
   Isnt_Nullptr(info, );

   if((DREAD_STDIN_INFO_SIZE == info_size)&& this->is_connection_ready)
   {
      info_id = Big_Endian_get_u32(info);
      Str_Trait_write_number(Dread_Stdin_Buffer, info_id, DREAD_STDIN_STR_INFO_SIZE, 10);

      IPC_put_date_string(&Dread_Stdin_Buffer[DREAD_STDIN_STR_INFO_SIZE]);
      if(Dr_Stdin_Cbk_backup_info(Dread_Stdin_Buffer, sizeof(Dread_Stdin_Buffer)) )
      {
         successful_sent_info = true;
      }
   }

   Dr_Stdin_Cbk_notify_info_result(successful_sent_info);
}

bool_t  Dr_Stdin_Server_is_connection_ready(Dr_Stdin_T * const super)
{
   Dr_Stdin_Server_T * const this = _dynamic_cast(Dr_Stdin_Server, super);
   Isnt_Nullptr(this, false);
   return this->is_connection_ready;
}
/*=====================================================================================* 
 * dread_stdin_server.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
