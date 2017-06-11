/*=====================================================================================*/
/**
 * dread_slv.cpp
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
#include "dread_stdin_set.h"
#include "dread_stdin_ext.h"
#include "ipc.h"
#include "dread_hid_proxy.h"
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
 struct RingBuff
 {
    uint8_t buffer[DR_STDIN_TOTAL_REGISTERS*DR_STDIN_REGISTER_SIZE];
    uint8_t h;
    uint8_t t;
 };
/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/
 static void Ring_Buffer_init(void);
 static size_t Ring_Buffer_size(void);
 static void Ring_Buffer_push(char const * data, size_t const size);
/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
struct RingBuff Dr_Stdin_Buffer;
Dr_HID_T * Dr_Stdin_HID = NULL;
/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/
void Ring_Buffer_init(void)
{
   memset(&Dr_Stdin_Buffer, 0, sizeof(Dr_Stdin_Buffer));
}
size_t Ring_Buffer_size(void)
{
   return Dr_Stdin_Buffer.h>Dr_Stdin_Buffer.t? Dr_Stdin_Buffer.h-Dr_Stdin_Buffer.t: Dr_Stdin_Buffer.t-Dr_Stdin_Buffer.h;
}

void Ring_Buffer_push(char const * data, size_t const size)
{
   if(size <= DR_STDIN_REGISTER_SIZE)
   {
      Dr_Stdin_Buffer.h+=DR_STDIN_REGISTER_SIZE;
      if(sizeof(Dr_Stdin_Buffer.buffer) <= Dr_Stdin_Buffer.h)
      {
         Dr_Stdin_Buffer.h = 0;
      }
      memcpy(&Dr_Stdin_Buffer.buffer[Dr_Stdin_Buffer.h], data, size);
   }
}
/*=====================================================================================*
 * Exported Function Definitions
 *=====================================================================================*/
void Dr_Stdin_Cbk_Init(void)
{
   Ring_Buffer_init();
   Dr_Stdin_HID = &Dr_HID_Proxy_new()->Dr_HID;
   Dr_Stdin_HID->vtbl->ctor(Dr_Stdin_HID, IPC_self_task_id());
}

void Dr_Stdin_Cbk_notify_info_result(bool_t const result)
{
   if(result)
   {
      Dr_Stdin_HID->vtbl->success(Dr_Stdin_HID, DR_HID_SUCCESS_VALID_CARD);
   }
   else
   {
      Dr_Stdin_HID->vtbl->error(Dr_Stdin_HID, DR_HID_ERROR_INVALID_CARD);
   }
}

bool_t Dr_Stdin_Hdr_Cbk_backup_info(char const * info, size_t const info_size)
{
   bool_t retval = false;
   if(DR_STDIN_TOTAL_REGISTERS > Ring_Buffer_size())
   {
      Ring_Buffer_push(info, info_size);
      retval = true;
   }
   else
   {
      Dr_Stdin_HID->vtbl->error(Dr_Stdin_HID, DR_HID_ERROR_NO_REGISTERS);
   }
   return false;
}

void Dr_Stdin_Cbk_Shut(void)
{
   _delete(Dr_Stdin_HID);
}
/*=====================================================================================* 
 * dread_slv.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
