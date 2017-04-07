/*=====================================================================================*/
/**
 * tb_mailbox.cpp
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
#include "tb_mailbox.h"
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
#define TB_MAILBOX_VIRTUAL_PUSH_MAIL_PARAMS(PARAM),PARAM(TB_Mail, mail)
#define TB_MAILBOX_VIRTUAL_SUBSCRIBE_PARAMS(PARAM),PARAM(TB_Publisher, publisher),PARAM(TB_Mail_Id_T const, mail_id)
#define TB_MAILBOX_VIRTUAL_PARAMS(PARAM)
/*=====================================================================================* 
 * Local Type Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
Define_Class(TB_Mailbox, TB_MAILBOX_CTOR)
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
void TB_Mailbox_Ctor(TB_Mailbox this, TB_Task owner, uint32_t const mail_elems, size_t const data_size)
{
   Acc_Member(Object, this)->vtable = (struct Object_VTable_T *)&TB_Mailbox_VTable_Obj;
   Acc_Method(Object, this)->destroy = TB_Mailbox_Dtor;
   Acc_Method(TB_Mailbox, this)->dump = NULL;
   Acc_Method(TB_Mailbox, this)->pop_mail = NULL;
   Acc_Method(TB_Mailbox, this)->push_mail = NULL;
   Acc_Method(TB_Mailbox, this)->subscribe = NULL;
   Acc_Method(TB_Mailbox, this)->unsubscribe = NULL;

   Acc_Member(TB_Mailbox, this)->owner = owner;
   Acc_Member(TB_Mailbox, this)->mailbox = Ring_Buffer_New(mail_elems, sizeof(TB_Mail));
   Acc_Member(TB_Mailbox, this)->data_size = data_size;
}

void TB_Mailbox_Dtor(Object obj)
{
   TB_Mailbox this = Downcast(TB_Mailbox, obj);
   TB_Mailbox_unsubscribe(this, TB_Publisher_get_instance(0,0));
   Ring_Buffer_delete(this->mailbox);
}

Define_Virtual_Void_VTable(TB_Mailbox, push_mail, TB_MAILBOX_VIRTUAL_PUSH_MAIL_PARAMS)
Define_Virtual_VTable(bool_t, false, TB_Mailbox, subscribe, TB_MAILBOX_VIRTUAL_SUBSCRIBE_PARAMS)
Define_Virtual_VTable(bool_t, false, TB_Mailbox, unsubscribe, TB_MAILBOX_VIRTUAL_SUBSCRIBE_PARAMS)
Define_Virtual_VTable(const TB_Mail, NULL, TB_Mailbox, pop_mail, TB_MAILBOX_VIRTUAL_PARAMS)
/*=====================================================================================* 
 * tb_mailbox.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
