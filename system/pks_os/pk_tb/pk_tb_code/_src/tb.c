/*=====================================================================================*/
/**
 * tb.cpp
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
#include "tb.h"
#include "tb_os.h"
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

 /*=====================================================================================*
 * Local Object Definitions
 *=====================================================================================*/
static TB_OS TB_OS_Singleton = NULL;

Define_Class(TB_OS, TB_OBJ_CTOR)
/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/
TB_OS TB_get_instance(TB_Process_Id_T const pid, uint32_t const max_tasks)
{
   if(NULL == TB_OS_Singleton)
   {
      TB_OS_Singleton = TB_OS_New(pid);
   }
}

void TB_OS_Ctor(TB_OS this, TB_Process_Id_T const pid, uint32_t const max_tasks)
{
   Acc_Member(Object, this)->vtable = (struct Object_VTable_T *)&TB_OS_VTable_Obj;
   Acc_Method(Object, this)->destroy = TB_OS_Dtor;
   this->pid = pid;
}

void TB_OS_Dtor(Object obj)
{

}
/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
 TB_Task_Id_T TB_self_task_id(void)
 {
    TB_OS tb = TB_get_instance(0,0);
    Isnt_Nullptr(tb, 0);
    return TB_OS_search_task(tb);
 }


 TB_Process_Id_T TB_self_pid(void)
 {
    TB_OS tb = TB_get_instance(0,0);
    Isnt_Nullptr(tb, 0);
    return TB_OS_search_pid(tb);
 }

 void TB_task_ready(void)
 {
    TB_OS tb = TB_get_instance(0,0);
    TB_OS_notify_ready(tb, TB_self_task_id());
 }

 void TB_create_mailbox(uint32_t const max_mails, size_t const mail_size)
 {
    TB_OS tb = TB_get_instance(0,0);
    TB_set_mailbox(tb, max_mails, mail_size);
 }

/**
 * TB Mail Comm
 */
 bool_t TB_subscribe_mail_list(TB_Mail_Id_T const * mail_list, uint32_t const mail_elems)
 {
    TB_Publisher publisher = TB_Publisher_get_instance(0,0);
    return TB_Publisher_subscribe(publisher,TB_self_task_id(),  mail_list, mail_elems);
 }

 bool_t TB_unsubscribe_mail_list(TB_Mail_Id_T const * mail_list, uint32_t const mail_elems)
 {
    TB_Publisher publisher = TB_Publisher_get_instance(0,0);
    return TB_Publisher_unsubscribe(publisher,TB_self_task_id(),  mail_list, mail_elems);
 }

 void TB_send(TB_Task_Id_T const receiver_task, TB_Process_Id_T const receiver_pid,
      TB_Mail_Id_T mail_id, void const * data, size_t const data_size)
 {
    TB_OS tb = TB_get_instance(0,0);
    TB_Mailbox mailbox = TB_OS_search_mailbox(tb, receiver_task, receiver_pid);
    TB_Mail mail = TB_Mail_New(mail_id, TB_OS_search_task(tb), receiver_task, receiver_pid, data, data_size);
    TB_Mailbox_push_mail(mailbox, mail);
 }

 void TB_publish(TB_Mail_Id_T const mail_id, void const * data, size_t const data_size)
 {
    TB_Publisher publisher = TB_Publisher_get_instance(0,0);
    TB_Mail mail = TB_Mail_New(mail_id, TB_self_task_id(), 0, 0, data, data_size);
    TB_Publisher_publish(publisher, mail);
 }

 void TB_broadcast(TB_Mail_Id_T const mail_id, void const * data, size_t const data_size)
 {
    TB_OS tb = TB_get_instance(0,0);
    TB_Task_Id_T task = 0;
    TB_Process_Id_T process = 0;
    TB_Mailbox mailbox = NULL;
    TB_Mail mail = NULL;

    for(process = 0 ; process < MAX_PROCESSES; ++process)
    {
       for(task = 0 ; task < MAX_TASKS; ++task)
       {
          mailbox = TB_OS_search_mailbox(tb, task, process);
          if(NULL != mailbox)
          {
             mail = TB_Mail_New(mail_id, TB_OS_search_task(tb), task, process, data, data_size);
             TB_Mailbox_push_mail(mailbox, mail);
             TB_Mail_delete(mail);
          }
       }
    }
 }

 const TB_Mail TB_retreive_from_mail_list(TB_Mail_Id_T const * mail_list, uint32_t const mail_elems,
      uint32_t const timeout_ms)
 {
    uint32_t i;
    TB_OS tb = TB_get_instance(0,0);
    TB_Mail mail = NULL;
    TB_Mailbox mailbox = TB_OS_search_mailbox(tb, TB_self_task_id(), TB_self_pid());

    Isnt_Nullptr(mail_list, NULL);

    for(i = 0; i < mail_elems; ++i)
    {
       mail = TB_Mailbox_get_mail_by_mail_id(mailbox, mail_list[i]);
       if(NULL != mail)
       {
          TB_Mail_dump(mail);
          break;
       }
    }
    return mail;
 }

 const TB_Mail TB_retreive_mail(uint32_t const timeout_ms)
 {
    TB_OS tb = TB_get_instance(0,0);
    TB_Mail mail = NULL;
    TB_Mailbox mailbox = TB_OS_search_mailbox(tb, TB_self_task_id(), TB_self_pid());

    mail = TB_Mailbox_get_first_mail(mailbox);
    TB_Mail_dump(mail);

    return mail;
 }
/*=====================================================================================* 
 * tb.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
