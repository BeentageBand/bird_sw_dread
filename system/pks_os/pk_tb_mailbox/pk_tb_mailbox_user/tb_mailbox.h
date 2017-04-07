/*=====================================================================================*/
/**
 * tb_mailbox.h
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#ifndef TB_MAILBOX_H_
#define TB_MAILBOX_H_
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "object.h"
#include "tb_mail.h"
#include "ring_buffer.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Define Macros
 *=====================================================================================*/
#ifdef __cplusplus
extern "C" {
#endif

#define TB_MAILBOX_CTOR(PARAM) ,PARAM(TB_Task, owner),PARAM(uint32_t const, mail_elems),PARAM(size_t const, data_size)
/*=====================================================================================* 
 * Exported Type Declarations
 *=====================================================================================*/
Declare_Class(
      TB_Mailbox,
      TB_MAILBOX_CTOR,
      TB_Task owner;
      Ring_Buffer mailbox;
      size_t data_size;
      ,
      bool_t (*subscribe)(TB_Mailbox, struct TB_Publisher_T *, TB_Mail_Id_T const);
      bool_t (*unsubscribe)(TB_Mailbox, struct TB_Publisher_T *,  TB_Mail_Id_T const);
      void (*push_mail)(TB_Mailbox, TB_Mail);
      const TB_Mail (*pop_mail)(TB_Mailbox);
      void (*dump)(TB_Mailbox);
      );
/*=====================================================================================* 
 * Exported Object Declarations
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Function Prototypes
 *=====================================================================================*/
extern bool_t TB_Mailbox_subscribe(TB_Mailbox obj, struct TB_Publisher_T * publisher, TB_Mail_Id_T const mail_id);
extern bool_t TB_Mailbox_unsubscribe(TB_Mailbox obj, struct TB_Publisher_T * publisher, TB_Mail_Id_T const mail_id);
extern void TB_Mailbox_push_mail(TB_Mailbox obj, TB_Mail mail);
extern const TB_Mail TB_Mailbox_pop_mail(TB_Mailbox obj);
extern void TB_Mailbox_dump(TB_Mailbox obj);
/*=====================================================================================* 
 * Exported Function Like Macros
 *=====================================================================================*/
#ifdef __cplusplus
}
#endif
/*=====================================================================================* 
 * tb_mailbox.h
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
#endif /*TB_MAILBOX_H_*/
