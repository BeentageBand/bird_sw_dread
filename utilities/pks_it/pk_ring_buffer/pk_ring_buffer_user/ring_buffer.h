/*=====================================================================================*/
/**
 * ring_buffer.h
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#ifndef RING_BUFFER_H_
#define RING_BUFFER_H_
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "iterable.h"
#include "iterator.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Define Macros
 *=====================================================================================*/
#ifdef __cplusplus
extern "C" {
#endif

#define RING_BUFFER_CTOR(PARAM) PARAM(size_t const, elem_size),PARAM(uint32_t const, max_elems)
/*=====================================================================================* 
 * Exported Type Declarations
 *=====================================================================================*/
Declare_Class_Inherits(
      Ring_Buffer, Iterable,
      RING_BUFFER_CTOR,
      void * data;
      uint32_t h;
      uint32_t t;
      uint32_t max_elems;
      ,);
/*=====================================================================================* 
 * Exported Object Declarations
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Function Prototypes
 *=====================================================================================*/
uint32_t Ring_Buffer_size(Ring_Buffer obj);
bool_t Ring_Buffer_is_empty(Ring_Buffer obj);
Iterator Ring_Buffer_create_it(Ring_Buffer obj);
Iterator Ring_Buffer_at(Ring_Buffer obj, uint32_t i);
Iterator Ring_Buffer_begin(Ring_Buffer obj);
Iterator Ring_Buffer_end(Ring_Buffer obj);
void Ring_Buffer_push_front(Ring_Buffer obj, void const * data);
void * Ring_Buffer_pop_back(Ring_Buffer obj);
void * Ring_Buffer_peek_back(Ring_Buffer obj);
/*=====================================================================================* 
 * Exported Function Like Macros
 *=====================================================================================*/
#ifdef __cplusplus
}
#endif
/*=====================================================================================* 
 * ring_buffer.h
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
#endif /*RING_BUFFER_H_*/
