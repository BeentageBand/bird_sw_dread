/*=====================================================================================*/
/**
 * iterator.cpp
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
#include "iterator.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Local X-Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Define Macros
 *=====================================================================================*/
#define ITERATOR_VIRTUAL_METHOD_PARAMS(PARAM)
#define ITERATOR_VIRUTAL_SET_IT_PARAMS(PARAM) ,PARAM(void const *, data)
/*=====================================================================================* 
 * Local Type Definitions
 *=====================================================================================*/
 
/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
Define_Class(Iterator, ITERATOR_CTOR)
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
void Iterator_Ctor(Iterator this, Iterable iterable)
{
   Acc_Member(Object, this)->vtable = (struct Iterator_VTable_T *)&Iterator_VTable_Obj;
   Acc_Method(Object, this)->destroy = Iterator_Dtor;
   Acc_Method(Iterator, this)->access_it = NULL;
   Acc_Method(Iterator, this)->copy_it = NULL;
   Acc_Method(Iterator, this)->get_next = NULL;
   Acc_Method(Iterator, this)->has_next = NULL;
   Acc_Method(Iterator, this)->increment_it = NULL;
   Acc_Method(Iterator, this)->rm_it = NULL;
   Acc_Method(Iterator, this)->set_it = NULL;

   this->iterable = iterable;
   this->i = 0;
}

void Iterator_Dtor(Object obj)
{}

Define_Virtual_VTable(bool_t, false, Iterator, has_next, ITERATOR_VIRTUAL_METHOD_PARAMS)
Define_Virtual_VTable(void *, NULL, Iterator, access_it, ITERATOR_VIRTUAL_METHOD_PARAMS);
Define_Virtual_VTable(Iterator, NULL, Iterator, copy_it, ITERATOR_VIRTUAL_METHOD_PARAMS)
Define_Virtual_Void_VTable(Iterator, increment_it, ITERATOR_VIRTUAL_METHOD_PARAMS)
Define_Virtual_Void_VTable(Iterator, get_next, ITERATOR_VIRTUAL_METHOD_PARAMS)
Define_Virtual_Void_VTable(Iterator, set_it, ITERATOR_VIRUTAL_SET_IT_PARAMS)
Define_Virtual_Void_VTable(Iterator, rm_it, ITERATOR_VIRTUAL_METHOD_PARAMS)
/*=====================================================================================* 
 * iterator.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
