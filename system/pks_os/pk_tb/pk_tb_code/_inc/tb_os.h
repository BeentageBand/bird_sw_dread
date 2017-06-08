/*=====================================================================================*/
/**
 * tb_os.h
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#ifndef TB_OS_H_
#define TB_OS_H_
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "object.h"
#include "tb_mail.h"
#include "tb_mailbox.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Define Macros
 *=====================================================================================*/
#ifdef __cplusplus
extern "C" {
#endif
#define TB_OS_CTOR(PARAM) PARAM(TB_Process_Id_T const, pid),PARAM(uint32_t const, max_tasks)
/*=====================================================================================* 
 * Exported Type Declarations
 *=====================================================================================*/
Declare_Class(
      TB_OS,
      TB_OS_CTOR,
      TB_Process_Id_T pid;
      ,
      TB_Task_Id_T (*search_task)(TB_OS);
      TB_Process_Id_T (*search_pid)(TB_OS);
      void (*set_mailbox)(TB_OS, uint32_t const, uint32_t const);
      TB_Mailbox (*search_mailbox)(TB_OS obj, uint32_t const, uint32_t const);
      void (*notify_ready)(TB_OS, uint32_t const);
      );
/*=====================================================================================* 
 * Exported Object Declarations
 *=====================================================================================*/
extern TB_OS TB_OS_get_instance(TB_Process_Id_T const pid, uint32_t const max_tasks);
extern TB_Task_Id_T TB_OS_search_task(TB_OS obj);
extern TB_Process_Id_T TB_OS_search_pid(TB_OS obj);
extern void TB_OS_set_mailbox(TB_OS obj, uint32_t const task_id, uint32_t const pid);
extern TB_Mailbox TB_OS_search_mailbox(TB_OS obj, uint32_t const task_id, uint32_t const pid);
extern void TB_OS_notify_ready(TB_OS obj, uint32_t const task_id);
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
 * tb_os.h
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
#endif /*TB_OS_H_*/
