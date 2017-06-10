/*=====================================================================================*/
/**
 * dread_hid_types.h
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#ifndef DREAD_HID_TYPES_H_
#define DREAD_HID_TYPES_H_
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "std_reuse.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Define Macros
 *=====================================================================================*/
#ifdef __cplusplus
extern "C" {
#endif
/*=====================================================================================* 
 * Exported Type Declarations
 *=====================================================================================*/
typedef enum
{
   DR_HID_ERROR_INVALID_CARD,
   DR_HID_ERROR_NO_REGISTERS
}Dr_HID_Error_T;

typedef enum
{
   DR_HID_SUCCESS_VALID_CARD
}Dr_HID_Success_T;

typedef struct
{
   uint8_t signal;
   uint8_t type;
}Dr_HID_HSM_Signal_T;
/*=====================================================================================* 
 * Exported Object Declarations
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Function Prototypes
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Function Like Macros
 *=====================================================================================*/
#ifdef __cplusplus
}
#endif
/*=====================================================================================* 
 * dread_hid_types.h
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
#endif /*DREAD_HID_TYPES_H_*/