/*=====================================================================================*/
/**
 * iterable.h
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#ifndef ITERABLE_H_
#define ITERABLE_H_
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "object.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Define Macros
 *=====================================================================================*/
#ifdef __cplusplus
extern "C" {
#endif

#define ITERABLE_CTOR(PARAM) PARAM(size_t const, elem_size)
/*=====================================================================================* 
 * Exported Type Declarations
 *=====================================================================================*/
Declare_Class(
      Iterable,
      ITERABLE_CTOR,
      size_t elem_size;
      struct Iterator_T * begin;
      struct Iterator_T * end;
      ,
      uint32_t (*size)(Iterable);
      bool_t (*is_empty)(Iterable);
      void (*erase)(Iterable, struct Iterator_T *, struct Iterator_T *);
      void (*assign)(Iterable, struct Iterator_T *, struct Iterator_T *);
      struct Iterator_T * (*create_it)(Iterable);
      struct Iterator_T * (*at)(Iterable, uint32_t);
      struct Iterator_T * (*begin)(Iterable);
      struct Iterator_T * (*end)(Iterable);
      );
/*=====================================================================================* 
 * Exported Object Declarations
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Function Prototypes
 *=====================================================================================*/
extern uint32_t Iterable_size(Iterable obj);
extern bool_t Iterable_is_empty(Iterable obj);
extern struct Iterator_T * Iterable_create_it(Iterable obj);
extern struct Iterator_T * Iterable_at(Iterable obj, uint32_t i);
extern struct Iterator_T * Iterable_begin(Iterable obj);
extern struct Iterator_T * Iterable_end(Iterable obj);
extern void Iterable_assign(Iterable obj, struct Iterator_T * begin, struct Iterator_T * end);
extern void Iterable_erase(Iterable obj, struct Iterator_T * begin, struct Iterator_T * end);
/*=====================================================================================* 
 * Exported Function Like Macros
 *=====================================================================================*/
#ifdef __cplusplus
}
#endif
/*=====================================================================================* 
 * iterable.h
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
#endif /*ITERABLE_H_*/
