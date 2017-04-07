/*=====================================================================================*/
/**
 * tb_mail.cpp
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
#include "tb_mail.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Local X-Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Define Macros
 *=====================================================================================*/
#define TB_MAIL_SET_DATA_PARAMS(PARAM) ,PARAM(void const *, data),PARAM(size_t const, data_size)

Define_Class(TB_Mail, TB_MAIL_CTOR)
/*=====================================================================================* 
 * Local Type Definitions
 *=====================================================================================*/
 
/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/

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
void TB_Mail_Ctor(TB_Mail this, TB_Mail_Id_T const mail_id, TB_Task_Id_T const sender_task,
      TB_Task_Id_T const receiver_task, void const * data, size_t const data_size)
{
   Acc_Member(Object, this)->vtable = (struct TB_Mail_VTable_T *)&TB_Mail_VTable_Obj;
   Acc_Method(Object, this)->destroy = TB_Mail_Dtor;
   Acc_Member(TB_Mail, this)->mail_id = mail_id;
   Acc_Member(TB_Mail, this)->mail_id = sender_task;
   Acc_Member(TB_Mail, this)->mail_id = receiver_task;
   Acc_Member(TB_Mail, this)->is_dumpable = false;

   TB_Mail_set_data(this, data, data_size);
}

void TB_Mail_Dtor(Object this)
{
   TB_Mail mail = Downcast(TB_Mail, this);
   Isnt_Nullptr(mail, );
   free(mail->data);
}

void TB_Mail_set_data(TB_Mail this, void const * data, size_t const data_size)
{
   Isnt_Nullptr(this,);
   Isnt_Nullptr(data,);

   if(NULL != this->data)
   {
      if(this->data_size != data_size)
      {

         free(this->data);
      }
   }

   this->data_size = data_size;
   this->data = malloc(this->data_size);
   memcpy(this->data, data, data_size);
}

void const * TB_Mail_get_data(TB_Mail this)
{
   Isnt_Nullptr(this, NULL);
   return this->data;
}

size_t TB_Mail_get_data_size(TB_Mail this)
{
   Isnt_Nullptr(this, 0);
   return this->data_size;
}


void TB_Mail_dump(TB_Mail this)
{
   Isnt_Nullptr(this, );
   this->is_dumpable = true;
}
/*=====================================================================================* 
 * tb_mail.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
