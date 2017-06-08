/*=====================================================================================*/
/**
 * ring_buff_it.cpp
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
#include "ring_buff_it.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Local X-Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Define Macros
 *=====================================================================================*/
#define RING_BUFFER_IT_VIRTUAL_METHOD_PARAMS(PARAM)
#define RING_BUFFER_IT_VIRUTAL_SET_IT_PARAMS(PARAM) ,PARAM(void const *, data)
/*=====================================================================================* 
 * Local Type Definitions
 *=====================================================================================*/
 
/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/
static Iterator RingBuffIt_v_copy_it(Iterator super);
static void * RingBuffIt_v_access_it(Iterator super);
static void RingBuffIt_v_increment_it(Iterator super);
static bool_t RingBuffIt_v_has_next(Iterator super);
static void RingBuffIt_v_get_next(Iterator super);
static void RingBuffIt_v_set_it(Iterator super, void const * data);
static void RingBuffIt_v_rm_it(Iterator super);
static bool_t RingBuffIt_p_is_in_range(RingBuffIt rbi, Ring_Buffer rb);
/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
Define_Class(RingBuffIt, RING_BUFFER_IT_CTOR)
/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/
Iterator RingBuffIt_v_copy_it(Iterator super)
{
   Ring_Buffer rb = Downcast(Ring_Buffer, super->iterable);
   RingBuffIt copy_it = NULL;

   Isnt_Nullptr(rb, NULL);
   copy_it = RingBuffIt_New(rb);

   Isnt_Nullptr(copy_it, NULL);
   Acc_Member(Iterator, copy_it)->i = super->i;

   return (Iterator) copy_it;
}

void * RingBuffIt_v_access_it(Iterator super)
{
   Ring_Buffer rb = Downcast(Ring_Buffer, super->iterable);
   RingBuffIt this = Downcast(RingBuffIt, super);
   uint8_t * access = NULL;

   Isnt_Nullptr(rb, NULL);
   Isnt_Nullptr(this, NULL);

   if(RingBuffIt_p_is_in_range(this, rb))
   {
      Isnt_Nullptr(rb->data, NULL);
      access = (uint8_t *) rb->data;
      access = &access[rb->super.elem_size * super->i];
   }

   return (void *) access;
}

void RingBuffIt_v_increment_it(Iterator super)
{
   Ring_Buffer rb = Downcast(Ring_Buffer, super->iterable);

   Isnt_Nullptr(rb,);
   ++super->i;
   super->i = (super->i < rb->max_elems)? super->i : 0;
}

bool_t RingBuffIt_v_has_next(Iterator super)
{
   Ring_Buffer rb = Downcast(Ring_Buffer, super->iterable);

   Isnt_Nullptr(rb, false);
   return rb->is_full;
}

void RingBuffIt_v_get_next(Iterator super)
{
   Iterator_increment_it(super);
}

void RingBuffIt_v_set_it(Iterator super, void const * data)
{
   Ring_Buffer rb = Downcast(Ring_Buffer, super->iterable);
   RingBuffIt this = Downcast(RingBuffIt, super);

   Isnt_Nullptr(rb, );
   Isnt_Nullptr(this,);

   if(RingBuffIt_p_is_in_range(this, rb))
   {
      memcpy(Iterator_access_it(super), data, super->iterable->elem_size);
   }
}

void RingBuffIt_v_rm_it(Iterator super)
{
   Ring_Buffer rb = Downcast(Ring_Buffer, super->iterable);
   RingBuffIt this = Downcast(RingBuffIt, super);

   Isnt_Nullptr(rb, );
   Isnt_Nullptr(this,);

   if(RingBuffIt_p_is_in_range(this, rb))
   {
      Iterable_erase(super->iterable, super, super->iterable->end);
   }
}

bool_t RingBuffIt_p_is_in_range(RingBuffIt rbi, Ring_Buffer rb)
{
   bool_t is_inrange = false;

   if(rb->h > rb->t) /* head gt tail */
   {
      is_inrange = Acc_Member(Iterator, rbi)->i < rb->h && Acc_Member(Iterator,rbi)->i >= rb->t;
   }
   else if (rb->h < rb->t)
   {
      is_inrange = (Acc_Member(Iterator, rbi)->i <= rb->t && Acc_Member(Iterator, rbi)->i < rb->max_elems) ||
            (Acc_Member(Iterator, rbi)->i < rb->h);
   }
   else
   {
      /* do nothing */
   }

   return is_inrange;
}
/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
void RingBuffIt_Ctor(RingBuffIt this, Ring_Buffer rb)
{
   Iterator_Ctor(&this->super, &rb->super);

   Acc_Member(Object, this)->vtable = (struct RingBuffIt_VTable_T *)&RingBuffIt_VTable_Obj;
   Acc_Method(Object, this)->destroy = RingBuffIt_Dtor;

   Acc_Method(Iterator, this)->access_it = RingBuffIt_v_access_it;
   Acc_Method(Iterator, this)->copy_it = RingBuffIt_v_copy_it;
   Acc_Method(Iterator, this)->get_next = RingBuffIt_v_get_next;
   Acc_Method(Iterator, this)->has_next = RingBuffIt_v_has_next;
   Acc_Method(Iterator, this)->increment_it = RingBuffIt_v_increment_it;
   Acc_Method(Iterator, this)->rm_it = RingBuffIt_v_rm_it;
   Acc_Method(Iterator, this)->set_it = RingBuffIt_v_set_it;
}

void RingBuffIt_Dtor(Object obj)
{
   Iterator_Dtor(obj);
}

Define_Virtual_VTable_Inherits(bool_t, false, RingBuffIt, Iterator, has_next, RING_BUFFER_IT_VIRTUAL_METHOD_PARAMS)
Define_Virtual_VTable_Inherits(void *, NULL, RingBuffIt, Iterator, access_it, RING_BUFFER_IT_VIRTUAL_METHOD_PARAMS);
Define_Virtual_VTable_Inherits(RingBuffIt, NULL, RingBuffIt, Iterator, copy_it, RING_BUFFER_IT_VIRTUAL_METHOD_PARAMS)
Define_Virtual_Void_VTable_Inherits(RingBuffIt, Iterator, increment_it, RING_BUFFER_IT_VIRTUAL_METHOD_PARAMS)
Define_Virtual_Void_VTable_Inherits(RingBuffIt, Iterator, get_next, RING_BUFFER_IT_VIRTUAL_METHOD_PARAMS)
Define_Virtual_Void_VTable_Inherits(RingBuffIt, Iterator, set_it, RING_BUFFER_IT_VIRUTAL_SET_IT_PARAMS)
Define_Virtual_Void_VTable_Inherits(RingBuffIt, Iterator, rm_it, RING_BUFFER_IT_VIRTUAL_METHOD_PARAMS)
/*=====================================================================================* 
 * ring_buff_it.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
