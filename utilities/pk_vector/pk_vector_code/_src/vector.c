/*=====================================================================================*/
/**
 * vector.cpp
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
#include "vector.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Local X-Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Define Macros
 *=====================================================================================*/
#define VECTOR_VIRTUAL_METHOD_PARAMS(PARAM)
#define VECTOR_VIRTUAL_AT_PARAMS(PARAM) ,PARAM(uint32_t, i)
/*=====================================================================================* 
 * Local Type Definitions
 *=====================================================================================*/
 
/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/
static uint32_t Vector_v_size(Iterable super);
static bool_t Vector_is_v_empty(Iterable super);
static Iterator Vector_v_create_it(Iterable super);
static Iterator Vector_v_at(Iterable super, uint32_t i);
static Iterator Vector_v_begin(Iterable super);
static Iterator Vector_v_end(Iterable super);
static void * Vector_p_alloc(Iterator alloc);
/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
Define_Class(Vector, VECTOR_CTOR)
/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/
uint32_t Vector_v_size(Iterable super)
{
   Vector this = Downcast(Vector, super);
   Isnt_Nullptr(this,0);
   return this->heap;
}

bool_t Vector_is_v_empty(Iterable super)
{
   return (0 != Iterable_size(super));
}

Iterator Vector_v_create_it(Iterable super)
{
   Vector this = Downcast(Vector, super);
   Isnt_Nullptr(this, NULL);
   return VectorIt_New(this);
}

Iterator Vector_v_at(Iterable super, uint32_t i)
{
   Vector this = Downcast(Vector, super);
   Iterator it = Vector_create_it(this);
   Isnt_Nullptr(this, NULL);
   Isnt_Nullptr(it, NULL);
   while(i--)
   {
      Iterator_get_next(it);
   }
   return it;
}

Iterator Vector_v_begin(Iterable super)
{
   return Iterator_copy_it(super->begin);
}

Iterator Vector_v_end(Iterable super)
{
   return Iterator_copy_it(super->end);
}

void * Vector_p_alloc(Iterator alloc)
{
   void * elem_alloc = malloc(alloc->iterable->elem_size);
   Isnt_Nullptr(elem_alloc, NULL);
   memcpy(elem_alloc, Iterator_access_it(alloc), alloc->iterable->elem_size);
   return elem_alloc;
}
/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
void Vector_Ctor(Vector this, size_t const elem_size, void * (*alloc)(Iterable))
{
   Iterable_Ctor(&this->super, elem_size);
   Acc_Member(Object, this)->vtable = (struct Object_VTable_T *)&Vector_VTable_Obj;
   Acc_Method(Object, this)->destroy = Vector_Dtor;
   Acc_Method(Iterable, this)->at = Vector_v_at;
   Acc_Method(Iterable, this)->begin = Vector_v_begin;
   Acc_Method(Iterable, this)->create_it = Vector_v_create_it;
   Acc_Method(Iterable, this)->end = Vector_v_end;
   Acc_Method(Iterable, this)->size = Vector_v_size;
   Acc_Method(Iterable, this)->is_empty = Vector_is_v_empty;
   this->heap = 0;
   this->alloc_space = 0;
   this->alloc = alloc;
}

void Vector_Dtor(Object obj)
{
   Vector this = Downcast(Vector, obj);
   Isnt_Nullptr(this,);
   free(this->data);
}

void Vector_push(Vector this, void const * pushed_data)
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

void * Vector_pop(Vector this)
{
   void * pop;
   Isnt_Nullptr(pop, NULL);
   return Ierator_access_it(Iterable_at(&this->super, Acc_Member(Iterable, this)->end->i - 1));
}

void * Vector_peek(Vector this)
{
   void * peek;
   Iterator it = Iterable_at(&this->super, Acc_Member(Iterable, this)->end->i - 1)
   peek = Vector_p_alloc(it);
   Iterator_rm_it(it);
   Iterator_delete(it);
   return peek;
}

Define_Virtual_VTable_Inherits(Iterator, NULL, Vector, Iterable, at, VECTOR_VIRTUAL_AT_PARAMS)
Define_Virtual_VTable_Inherits(Iterator, NULL, Vector, Iterable, begin, VECTOR_VIRTUAL_METHOD_PARAMS)
Define_Virtual_VTable_Inherits(Iterator, NULL, Vector, Iterable, create_it, VECTOR_VIRTUAL_METHOD_PARAMS)
Define_Virtual_VTable_Inherits(Iterator, NULL, Vector, Iterable, end, VECTOR_VIRTUAL_METHOD_PARAMS)
Define_Virtual_VTable_Inherits(uint32_t, 0, Vector, Iterable, size, VECTOR_VIRTUAL_METHOD_PARAMS)
Define_Virtual_VTable_Inherits(bool_t, false, Vector, Iterable, is_empty, VECTOR_VIRTUAL_METHOD_PARAMS)
/*=====================================================================================* 
 * vector.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
