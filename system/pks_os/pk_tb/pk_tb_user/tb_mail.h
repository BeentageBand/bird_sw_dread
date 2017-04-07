/*=====================================================================================*/
/**
 * tb_mail.h
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#ifndef TB_MAIL_H_
#define TB_MAIL_H_
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "object.h"
#include "tb_types.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Define Macros
 *=====================================================================================*/
#ifdef __cplusplus
extern "C" {
#endif
#define TB_MAIL_CTOR(PARAM) \
   PARAM(TB_Mail_Id_T const, mail_id), \
   PARAM(TB_Task_Id_T const, sender_task), \
   PARAM(TB_Task_Id_T const, receiver_task), \
   PARAM(void const * , data), \
   PARAM(size_t const, data_size) \
/*=====================================================================================* 
 * Exported Type Declarations
 *=====================================================================================*/
Declare_Class(
      TB_Mail,
      TB_MAIL_CTOR,
      TB_Mail_Id_T mail_id;
      TB_Task_Id_T sender_task;
      TB_Task_Id_T receiver_task;
      void * data;
      size_t data_size;
      bool_t is_dumpable;
      ,
      );
/*=====================================================================================* 
 * Exported Object Declarations
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Function Prototypes
 *=====================================================================================*/
extern void TB_Mail_set_data(TB_Mail obj, void const * data, size_t const data_size);
extern void const * TB_Mail_get_data(TB_Mail obj);
extern size_t TB_Mail_get_data_size(TB_Mail obj);
extern void TB_Mail_dump(TB_Mail obj);
/*=====================================================================================* 
 * Exported Function Like Macros
 *=====================================================================================*/
#define TB_Mail_set_mail_id(obj, _mail_id) Acc_Member(TB_Mail, obj)->mail_id = _mail_id
#define TB_Mail_set_sender_task(obj, _sender_task) Acc_Member(TB_Mail, obj)->sender_task = _sender_task
#define TB_Mail_set_receiver_task(obj, _receiver_task) Acc_Member(TB_Mail, obj)->receiver_task = _receiver_task
#define TB_Mail_get_mail_id(obj) Acc_Member(TB_Mail, obj)->mail_id
#define TB_Mail_get_sender_task(obj) Acc_Member(TB_Mail, obj)->sender_task
#define TB_Mail_get_receiver_task(obj) Acc_Member(TB_Mail, obj)->receiver_task

#ifdef __cplusplus
}
#endif
/*=====================================================================================* 
 * tb_mail.h
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
#endif /*TB_MAIL_H_*/
