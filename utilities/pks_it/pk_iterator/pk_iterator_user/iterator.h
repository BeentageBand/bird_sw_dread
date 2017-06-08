/*=====================================================================================*/
/**
 * iterator.h
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#ifndef ITERATOR_H_
#define ITERATOR_H_
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "object.h"
#include "iterable.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Exported Define Macros
 *=====================================================================================*/
#ifdef __cplusplus
extern "C" {
#endif
/*=====================================================================================* 
 * Exported Type Declarations
 *=====================================================================================*/
#define ITERATOR_CTOR(PARAM) PARAM(Iterable, iterable)
/*=====================================================================================* 
 * Exported Object Declarations
 *=====================================================================================*/
Declare_Class(
      Iterator,
      ITERATOR_CTOR,
      Iterable iterable;
      uint32_t i;
      ,
      Iterator (*copy_it)(Iterator);
      void * (*access_it)(Iterator);
      void (*increment_it)(Iterator);
      bool_t (*has_next)(Iterator);
      void (*get_next)(Iterator);
      void (*set_it)(Iterator, void const *);
      void (*rm_it)(Iterator);
      );
/*=====================================================================================* 
 * Exported Function Prototypes
 *=====================================================================================*/
extern Iterator Iterator_copy_it(Iterator obj);
extern void * Iterator_access_it(Iterator obj);
extern void Iterator_incremente_it(Iterator obj);
extern bool_t Iterator_has_next(Iterator obj);
extern void Iterator_get_next(Iterator obj);
extern void Iterator_set_it(Iterator obj, void const * data);
extern void Iterator_rm_it(Iterator obj);
/*=====================================================================================* 
 * Exported Function Like Macros
 *=====================================================================================*/
#ifdef __cplusplus
}
#endif
/*=====================================================================================* 
 * iterator.h
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
#endif /*ITERATOR_H_*/
