/*=====================================================================================*/
/**
 * tb_uset.h
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#ifndef TB_USET_H_
#define TB_USET_H_
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "dread_stdin_hdr_evs.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Define Macros
 *=====================================================================================*/
#ifdef __cplusplus
extern "C" {
#endif

#define TB_PRIVATE_TASK_IDS \
   DREAD_STDIN_PRIVATE_TASK_IDS  \

#define TB_SUBSCRIBABLE_TASK_IDS \
   DREAD_STDIN_SUBSCRIBABLE_TASK_IDS  \

/*=====================================================================================* 
 * Exported Type Declarations
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Object Declarations
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Function Prototypes
 *=====================================================================================*/
#undef TB_MAIL
#define TB_MAIL(mail, description) mail,

#define PRIVATE_MAIL(mail, desc)      TB_MAIL(mail, desc)
#define SUBSCRIBABLE_MAIL(mail, desc) TB_MAIL(mail, desc)


enum
{
   TB_BEGIN_PRIVATE_LIST_ID = 0,
   TB_PRIVATE_TASK_IDS
   TB_END_PRIVATE_LIST_ID,
   TB_BEGIN_SUBSCRIBABLE_LIST_ID = TB_END_PRIVATE_LIST_ID,
   TB_SUBSCRIBABLE_TASK_IDS
   TB_END_SUBSCRIBABLE_LIST_ID,
   TB_TOTAL_TASK_IDS_ITEMS
};
/*=====================================================================================* 
 * Exported Function Like Macros
 *=====================================================================================*/
#ifdef __cplusplus
}
#endif
/*=====================================================================================* 
 * tb_uset.h
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
#endif /*TB_USET_H_*/
