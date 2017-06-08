/*=====================================================================================*/
/**
 * tb_publisher.cpp
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
#include "tb_publisher.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Local X-Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Define Macros
 *=====================================================================================*/
#define TB_PUBLISHER_VIRTUAL_PUSH_MAIL_PARAMS(PARAM),PARAM(TB_Mail, mail)
#define TB_PUBLISHER_VIRTUAL_SUBSCRIBE_PARAMS(PARAM),PARAM(TB_Publisher, publisher)
#define TB_PUBLISHER_VIRTUAL_PARAMS(PARAM)
/*=====================================================================================* 
 * Local Type Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
Define_Class(TB_Publisher, TB_PUBLISHER_CTOR)
/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
void TB_Publisher_Ctor(TB_Publisher this, TB_Task owner, uint32_t const mail_elems, size_t const data_size)
{
   Acc_Member(Object, this)->vtable = (struct Object_VTable_T *)&TB_Publisher_VTable_Obj;
   Acc_Method(Object, this)->destroy = TB_Publisher_Dtor;
   Acc_Method(TB_Publisher, this)->super = NULL;
   Acc_Method(TB_Publisher, this)->pop_mail = NULL;
   Acc_Method(TB_Publisher, this)->push_mail = NULL;
   Acc_Method(TB_Publisher, this)->subscribe = NULL;
   Acc_Method(TB_Publisher, this)->unsubscribe = NULL;

   Acc_Member(TB_Publisher, this)->owner = owner;
   Acc_Member(TB_Publisher, this)->publisher = Ring_Buffer_New(mail_elems, sizeof(TB_Mail));
   Acc_Member(TB_Publisher, this)->data_size = data_size;
}

void TB_Publisher_Dtor(Object obj)
{

}

Define_Virtual_Void_VTable(TB_Publisher, push_mail, TB_PUBLISHER_VIRTUAL_PUSH_MAIL_PARAMS)
Define_Virtual_VTable(bool_t, false, TB_Publisher, subscribe, TB_PUBLISHER_VIRTUAL_SUBSCRIBE_PARAMS)
Define_Virtual_VTable(bool_t, false, TB_Publisher, unsubscribe, TB_PUBLISHER_VIRTUAL_SUBSCRIBE_PARAMS)
Define_Virtual_VTable(const TB_Mail, NULL, TB_Publisher, pop_mail, TB_PUBLISHER_VIRTUAL_PARAMS)
/*=====================================================================================* 
 * tb_publisher.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
