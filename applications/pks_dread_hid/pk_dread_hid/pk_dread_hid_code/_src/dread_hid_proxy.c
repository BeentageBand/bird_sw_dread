/*=====================================================================================*/
/**
 * dread_hid.c
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#define CLASS_IPLEMENTATION
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
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
 
/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/
static void Dr_HID_Proxy_Ctor(Dr_HID_Proxy_T * const this, uint8_t const id);
static void Dr_HID_Proxy_success(Dr_HID_T * const super, Dr_HID_Success_T const success_type);
static void Dr_HID_Proxy_error(Dr_HID_T * const super, Dr_HID_Error_T const error_type);
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
void Dr_HID_Proxy_init(void)
{
   printf("%s \n", __FUNCTION__);

   Dr_HID_Proxy_Obj.Dr_HID = Dr_HID();

   memcpy(&Dr_HID_Proxy_Vtbl.Dr_HID, Dr_HID_Proxy_Obj.vtbl,
         sizeof(Dr_HID_Proxy_Vtbl.Dr_HID));

   Dr_HID_Proxy_Vtbl.Dr_HID.Object.rtti = &Dr_HID_Proxy_Rtti;
   Dr_HID_Proxy_Vtbl.Dr_HID.Object.destroy = Dr_HID_Proxy_Dtor;

   Dr_HID_Proxy_Vtbl.Dr_HID.success = Dr_HID_Proxy_success;
   Dr_HID_Proxy_Vtbl.Dr_HID.error = Dr_HID_Proxy_error;

   Dr_HID_Proxy_Vtbl.ctor = Dr_HID_Proxy_Ctor;

   Dr_HID_Proxy_Obj.vtbl = &Dr_HID_Proxy_Vtbl;
   Object_update_info(&Dr_HID_Proxy_Obj.Dr_HID.Object, Dr_HID().rtti->rtti);

}
void Dr_HID_Proxy_shut(void) {}

void Dr_HID_Proxy_Dtor(Object_T * const obj)
{
}

/*=====================================================================================*
 * Exported Function Definitions
 *=====================================================================================*/
void Dr_HID_Proxy_Ctor(Dr_HID_Proxy_T * const this, uint8_t const id)
{
   this->Dr_HID.vtbl->ctor(&this->Dr_HID, id);
}

void Dr_HID_Proxy_success(Dr_HID_T * const super, Dr_HID_Success_T const success_type)
{
   IPC_send(DREAD_HID_WORKER, DREAD_HID_PROCESS, DREAD_HID_SUCCESS, &success_type, sizeof(success_type));
}

void Dr_HID_Proxy_error(Dr_HID_T * const super, Dr_HID_Error_T const error_type)
{
   IPC_send(DREAD_HID_WORKER, DREAD_HID_PROCESS, DREAD_HID_ERROR, &error_type, sizeof(error_type));
}
/*=====================================================================================* 
 * dread_hid.c
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
