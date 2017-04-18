/*=====================================================================================*/
/**
 * iterable.cpp
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
#include "iterable.h"
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
#define ITERABLE_VIRTUAL_METHOD_PARAMS(PARAM)
#define ITERABLE_VIRTUAL_AT_PARAMS(PARAM) ,PARAM(uint32_t, i)
/*=====================================================================================* 
 * Local Type Definitions
 *=====================================================================================*/
 
/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
Define_Class(Iterable, ITERABLE_CTOR)
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
void Iterable_Ctor(Iterable this, size_t const elem_size)
{
   Acc_Member(Object, this)->vtable = (struct Object_VTable_T *)&Iterable_VTable_Obj;
   Acc_Method(Object, this)->destroy = Iterable_Dtor;
   Acc_Method(Iterable, this)->at = NULL;
   Acc_Method(Iterable, this)->begin = NULL;
   Acc_Method(Iterable, this)->create_it = NULL;
   Acc_Method(Iterable, this)->end = NULL;
   Acc_Method(Iterable, this)->is_empty = NULL;
   Acc_Method(Iterable, this)->size = NULL;

   this->elem_size = elem_size;
}

void Iterable_Dtor(Object obj)
{
   Iterable this = Downcast(Iterable, obj);
   Isnt_Nullptr(this,);
   Iterator_delete(this->begin);
   Iterator_delete(this->end);
}

Define_Virtual_VTable(Iterator, NULL, Iterable, at, ITERABLE_VIRTUAL_AT_PARAMS)
Define_Virtual_VTable(Iterator, NULL, Iterable, begin, ITERABLE_VIRTUAL_METHOD_PARAMS)
Define_Virtual_VTable(Iterator, NULL, Iterable, create_it, ITERABLE_VIRTUAL_METHOD_PARAMS)
Define_Virtual_VTable(Iterator, NULL, Iterable, end, ITERABLE_VIRTUAL_METHOD_PARAMS)
Define_Virtual_VTable(bool_t, false, Iterable, is_empty, ITERABLE_VIRTUAL_METHOD_PARAMS)
Define_Virtual_VTable(uint32_t, 0, Iterable, size, ITERABLE_VIRTUAL_METHOD_PARAMS)
/*=====================================================================================* 
 * iterable.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
