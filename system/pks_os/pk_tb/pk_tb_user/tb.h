/*=====================================================================================*/
/**
 * tb.h
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#ifndef TB_H_
#define TB_H_
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "tb_mail_list.h"
#include "tb_task_ids.h"
#include "tb_mail.h"
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

/*=====================================================================================* 
 * Exported Object Declarations
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Function Prototypes
 *=====================================================================================*/
/**
 * TB Task Handling
 * This apis should be used in task running
 */
extern TB_Task_Id_T TB_self_task_id(void);

extern TB_Process_Id_T TB_self_pid(void);

extern void TB_task_ready(void);

extern void TB_create_mailbox(uint32_t const max_mails, size_t const mail_size);

/**
 * TB Mail Comm
 */
extern bool_t TB_subscribe_mail_list(TB_Mail_Id_T const * mail_list, uint32_t const mail_elems);

extern bool_t TB_unsubscribe_mail_list(TB_Mail_Id_T const * mail_list, uint32_t const mail_elems);

extern void TB_send(TB_Task_Id_T const receiver_task, TB_Process_Id_T const receiver_pid,
      TB_Mail_Id_T mail_id, void const * data, size_t const data_size);

extern void TB_publish(TB_Mail_Id_T const mail_id, void const * data, size_t const data_size);

extern void TB_broadcast(TB_Mail_Id_T const mail_id, void const * data, size_t const data_size);

extern const TB_Mail TB_retreive_from_mail_list(TB_Mail_Id_T const * mail_list, uint32_t const mail_elems,
      uint32_t const timeout_ms);

extern const TB_Mail TB_retreive_mail(uint32_t const timeout_ms);

/**
 * TB Miscellaneous
 */
extern void TB_put_date_string(char * date_str);
/*=====================================================================================* 
 * Exported Function Like Macros
 *=====================================================================================*/
#ifdef __cplusplus
}
#endif
/*=====================================================================================* 
 * tb.h
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
#endif /*TB_H_*/
