/*=====================================================================================*/
/**
 * vector_it.cpp
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
#include "vector_it.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Local X-Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Define Macros
 *=====================================================================================*/
#define VECTOR_IT_VIRTUAL_METHOD_PARAMS(PARAM)
#define VECTOR_IT_VIRTUAL_AT_PARAMS(PARAM) ,PARAM(uint32_t, i)
/*=====================================================================================* 
 * Local Type Definitions
 *=====================================================================================*/
 
/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/
static Iterator VectorIt_v_copy_it(Iterator super);
static void * VectorIt_v_access_it(Iterator super);
static void VectorIt_v_increment_it(Iterator super);
static bool_t VectorIt_v_has_next(Iterator super);
static void VectorIt_v_get_next(Iterator super);
static void VectorIt_v_set_it(Iterator super, void const * data);
static void VectorIt_v_rm_it(Iterator super);
/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
Define_Class(VectorIt, VECTOR_IT_CTOR)
/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/
Iterator VectorIt_v_copy_it(Iterator super)
{
   Iterator copy = Iterable_create_it(super->iterable);
   copy->i = super->i;
   return copy;
}

void * VectorIt_v_access_it(Iterator super)
{
   Vector vector = Downcast(Vector, super->iterable);
   uint8_t * access = (super->i < vector->heap) ? vector->data : NULL;
   Isnt_Nullptr(vector, NULL);
   Isnt_Nullptr(access, NULL);
   return (void *) &access[super->i * super->iterable->elem_size];
}

void VectorIt_v_increment_it(Iterator super)
{
   Vector vector = Downcast(Vector, super->iterable);
   Isnt_Nullptr(vector, NULL);
   ++super->i;
}

bool_t VectorIt_v_has_next(Iterator super)
{
   Vector vector = Downcast(Vector, super->iterable);
   return  ((super->i + 1)< vector->heap);
}
void VectorIt_v_get_next(Iterator super)
{
   Iterator_increment_it(super);
}

void VectorIt_v_set_it(Iterator super, void const * data)
{
   memcpy(Iterator_access_it(super), data, super->iterable->elem_size);
}

void VectorIt_v_rm_it(Iterator super)
{

}
/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
void VectorIt_Ctor(VectorIt this, size_t const elem_size, void * (*alloc)(Iterable))
{
   Iterable_Ctor(&this->super, elem_size);
   Acc_Member(Object, this)->vtable = (struct Object_VTable_T *)&VectorIt_VTable_Obj;
   Acc_Method(Object, this)->destroy = VectorIt_Dtor;
   Acc_Method(Iterator, this)->access_it = VectorIt_v_access_it;
   Acc_Method(Iterator, this)->copy_it = VectorIt_v_copy_it;
   Acc_Method(Iterator, this)->get_next = VectorIt_v_get_next;
   Acc_Method(Iterator, this)->has_next = VectorIt_v_has_next;
   Acc_Method(Iterator, this)->increment_it = VectorIt_v_increment_it;
   Acc_Method(Iterator, this)->rm_it = VectorIt_is_v_rm_it;
   Acc_Method(Iterator, this)->set_it = VectorIt_is_v_set_it;
   this->heap = 0;
   this->alloc_space = 0;
   this->alloc = alloc;
}

void VectorIt_Dtor(Object obj)
{
   VectorIt this = Downcast(VectorIt, obj);
   Isnt_Nullptr(this,);
   free(this->data);
}

void VectorIt_push(VectorIt this, void const * pushed_data)
{
   size_t used_space;
   void * data;
   Isnt_Nullptr(this,);
   Isnt_Nullptr(pushed_data,);

   used_space = this->heap * Acc_Member(Iterable, this)->elem_size;
   if(used_space >= this->alloc_space)
   {
      data = this->data;
      this->alloc_space <<= 1;
      this->alloc(&this->super);
      memcpy(this->data, data, used_space);
      free(data);
   }
   Iterator_set_it(Acc_Member(Iterable, this)->end, pushed_data);
   Iterator_get_next(Acc_Member(Iterable, this)->end);
}

void * VectorIt_pop(VectorIt this)
{
   void * pop;
   Isnt_Nullptr(pop, NULL);
   return Ierator_access_it(Iterable_at(&this->super, Acc_Member(Iterable, this)->end->i - 1));
}

void * VectorIt_peek(VectorIt this)
{
   void * peek;
   Iterator it = Iterable_at(&this->super, Acc_Member(Iterable, this)->end->i - 1)
   peek = VectorIt_p_alloc(it);
   Iterator_rm_it(it);
   Iterator_delete(it);
   return peek;
}

Define_Virtual_VTable_Inherits(Iterator, NULL, VectorIt, Iterable, at, VECTOR_IT_VIRTUAL_AT_PARAMS)
Define_Virtual_VTable_Inherits(Iterator, NULL, VectorIt, Iterable, begin, VECTOR_IT_VIRTUAL_METHOD_PARAMS)
Define_Virtual_VTable_Inherits(Iterator, NULL, VectorIt, Iterable, create_it, VECTOR_IT_VIRTUAL_METHOD_PARAMS)
Define_Virtual_VTable_Inherits(Iterator, NULL, VectorIt, Iterable, end, VECTOR_IT_VIRTUAL_METHOD_PARAMS)
Define_Virtual_VTable_Inherits(uint32_t, 0, VectorIt, Iterable, size, VECTOR_IT_VIRTUAL_METHOD_PARAMS)
Define_Virtual_VTable_Inherits(bool_t, false, VectorIt, Iterable, is_empty, VECTOR_IT_VIRTUAL_METHOD_PARAMS)
/*=====================================================================================* 
 * vector_it.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
