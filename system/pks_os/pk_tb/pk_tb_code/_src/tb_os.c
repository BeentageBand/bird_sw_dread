/*=====================================================================================*/
/**
 * tb_os.cpp
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
#define TB_OS_VIRTUAL_METHOD_PARAMS(PARAM)
#define TB_OS_VIRTUAL_SET_MAILBOX_PARAMS(PARAM) ,PARAM(uint32_t const, task_id),PARAM(uint32_t const, pid)
#define TB_OS_VIRTUAL_NOTIFY_READY_PARAMS(PARAM) ,PARAM(uint32_t const, task_id)
/*=====================================================================================* 
 * Local Type Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/
static TB_Task_Id_T TB_OS_v_search_task(TB_OS obj);
static TB_Process_Id_T TB_OS_v_search_pid(TB_OS obj);
static void TB_OS_v_set_mailbox(TB_OS obj, uint32_t const task_id, uint32_t const pid);
 /*=====================================================================================*
 * Local Object Definitions
 *=====================================================================================*/
static TB_OS TB_OS_Singleton = NULL;

Define_Class(TB_OS, TB_OS_CTOR)
/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/
TB_Task_Id_T TB_OS_v_search_task(TB_OS obj)
{}

TB_Process_Id_T TB_OS_v_search_pid(TB_OS obj)
{}

void TB_OS_v_set_mailbox(TB_OS obj, uint32_t const task_id, uint32_t const pid)
{}

/*=====================================================================================*
 * Exported Function Definitions
 *=====================================================================================*/
TB_OS TB_OS_get_instance(TB_Process_Id_T const pid, uint32_t const max_tasks)
{
   if(NULL == TB_OS_Singleton)
   {
      TB_OS_Singleton = TB_OS_New(pid, max_tasks);
   }
   return TB_OS_Singleton;
}

void TB_OS_Ctor(TB_OS this, TB_Process_Id_T const pid, uint32_t const max_tasks)
{
   Acc_Member(Object, this)->vtable = (struct Object_VTable_T *)&TB_OS_VTable_Obj;
   Acc_Method(Object, this)->destroy = TB_OS_Dtor;
   Acc_Method(TB_OS, this)->search_pid = NULL;
   Acc_Method(TB_OS, this)->search_task = NULL;
   Acc_Method(TB_OS, this)->set_mailbox = NULL;
   this->pid = pid;
}

void TB_OS_Dtor(Object obj)
{

}

Define_Virtual_VTable(TB_Task_Id_T, 0, TB_OS, search_task, TB_OS_VIRTUAL_METHOD_PARAMS)
Define_Virtual_VTable(TB_Task_Id_T, 0, TB_OS, search_pid, TB_OS_VIRTUAL_METHOD_PARAMS)
Define_Virtual_Void_VTable(TB_OS, set_mailbox, TB_OS_VIRTUAL_SET_MAILBOX_PARAMS)
Define_Virtual_VTable(TB_Mailbox, NULL, TB_OS, search_mailbox, TB_OS_VIRTUAL_SET_MAILBOX_PARAMS)
Define_Virtual_Void_VTable(TB_OS, notify_ready, TB_OS_VIRTUAL_NOTIFY_READY_PARAMS)
/*=====================================================================================* 
 * tb_os.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
