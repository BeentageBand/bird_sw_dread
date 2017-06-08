/*=====================================================================================*/
/**
 * ring_buffer.cpp
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
#include "ring_buffer.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Local X-Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Define Macros
 *=====================================================================================*/
#define RING_BUFFER_VIRTUAL_PARAMS(PARAM)
#define RING_BUFFER_AT_PARAMS(PARAM) ,PARAM(uint32_t, i)
/*=====================================================================================* 
 * Local Type Definitions
 *=====================================================================================*/
 
/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/
uint32_t Ring_Buffer_v_size(Iterable super);
bool_t Ring_Buffer_v_is_empty(Iterable super);
Iterator Ring_Buffer_v_create_it(Iterable super);
Iterator Ring_Buffer_v_at(Iterable super, uint32_t i);
Iterator Ring_Buffer_v_begin(Iterable super);
Iterator Ring_Buffer_v_end(Iterable super);
/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
Define_Class(Ring_Buffer, RING_BUFFER_CTOR)
/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/
uint32_t Ring_Buffer_v_size(Iterable super)
{
    Ring_Buffer this = Downcast(Ring_Buffer, super);
    Isnt_Nullptr(this, 0);
    return this->max_elems;
}

bool_t Ring_Buffer_v_is_empty(Iterable super)
{
   Ring_Buffer this = Downcast(Ring_Buffer, super);
   Isnt_Nullptr(this, false);

   return (this->h == this->t);
}

Iterator Ring_Buffer_v_create_it(Iterable super)
{
   Ring_Buffer this = Downcast(Ring_Buffer, super);
   return (Iterator) RingBuffIt_New(this);
}

Iterator Ring_Buffer_v_at(Iterable super, uint32_t i)
{
   Iterator it = Iterable_create_it(super);
   Isnt_Nullptr(it, NULL);

   while(i--)
   {
      Iterator_get_next(it);
   }

   return it;
}

Iterator Ring_Buffer_v_begin(Iterable super)
{
   Ring_Buffer this = Downcast(Ring_Buffer, super);
   Isnt_Nullptr(this, NULL);

   if(NULL == super->end)
   {
      super->end = Iterable_at(super, this->h);
   }
   return super->end;
}

Iterator Ring_Buffer_v_end(Iterable super)
{
   Ring_Buffer this = Downcast(Ring_Buffer, super);
   Isnt_Nullptr(this, NULL);

   if(NULL == super->end)
   {
      super->end = Iterable_at(super, this->t);
   }
   return super->end;
}
/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
void Ring_Buffer_Ctor(Ring_Buffer this, size_t const elem_size, uint32_t max_elems)
{
   Iterable_Ctor(&this->super, elem_size);

   Acc_Member(Object, this)->vtable = (struct Object_VTable_T *)&Ring_Buffer_VTable_Obj;
   Acc_Method(Object, this)->destroy = Ring_Buffer_Dtor;
   Acc_Method(Iterable, this)->at = Ring_Buffer_v_at;
   Acc_Method(Iterable, this)->begin = Ring_Buffer_v_begin;
   Acc_Method(Iterable, this)->create_it = Ring_Buffer_v_create_it;
   Acc_Method(Iterable, this)->end = Ring_Buffer_v_end;
   Acc_Method(Iterable, this)->is_empty = Ring_Buffer_v_is_empty;
   Acc_Method(Iterable, this)->size = Ring_Buffer_v_size;

   this->data = malloc(elem_size * max_elems);
   this->max_elems = max_elems;
   this->h = 0;
   this->t = 0;

   Acc_Member(Iterable, this)->begin = Ring_Buffer_begin(this);
   Acc_Member(Iterable, this)->end = RingBuffIt_end(this);
}

void Ring_Buffer_Dtor(Object obj)
{
   Ring_Buffer this = Downcast(Ring_Buffer, obj);
   Isnt_Nullptr(this,);
   free(this->data);

   Iterable_Dtor(obj);
}
void Ring_Buffer_push_front(Ring_Buffer obj, void const * data)
{

}

void * Ring_Buffer_pop_back(Ring_Buffer obj)
{

}

void * Ring_Buffer_peek_back(Ring_Buffer obj)
{

}

Define_Virtual_VTable_Inherits(uint32_t, 0, Ring_Buffer, Iterable, size, RING_BUFFER_VIRTUAL_PARAMS)
Define_Virtual_VTable_Inherits(bool_t, false, Ring_Buffer, Iterable, is_empty, RING_BUFFER_VIRTUAL_PARAMS)
Define_Virtual_VTable_Inherits(Iterator, NULL, Ring_Buffer, Iterable, create_it, RING_BUFFER_VIRTUAL_PARAMS)
Define_Virtual_VTable_Inherits(Iterator, NULL, Ring_Buffer, Iterable, at, RING_BUFFER_AT_PARAMS)
Define_Virtual_VTable_Inherits(Iterator, NULL, Ring_Buffer, Iterable, begin, RING_BUFFER_VIRTUAL_PARAMS)
Define_Virtual_VTable_Inherits(Iterator, NULL, Ring_Buffer, Iterable, end, RING_BUFFER_VIRTUAL_PARAMS)
/*=====================================================================================* 
 * ring_buffer.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
