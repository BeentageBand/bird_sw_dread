/*=====================================================================================*/
/**
 * object.h
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#ifndef OBJECT_H_
#define OBJECT_H_
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "std_reuse.h"
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
struct Object_T
{
   struct Object_VTable_T * vtable;
};

typedef struct Object_T * Object;

struct Object_VTable_T
{
   void (*destroy)(Object);
};
/*=====================================================================================* 
 * Exported Object Declarations
 *=====================================================================================*/
#define Declare_Class(_class, _ctor, _members, _virtuals) \
Declare_Class_Inherits(_class, Object, _ctor, _members, _virtuals)

#define Declare_Class_Inherits(_class, _base, _ctor, _members, _virtuals) \
struct _class##_T                                                         \
{                                                                         \
   struct _base##_T super;                                                \
   _members                                                               \
};                                                                        \
                                                                          \
typedef struct _class##_T * _class;                                       \
                                                                          \
struct _class##_VTable_T                                                  \
{                                                                         \
   struct _base##_VTable_T super;                                         \
   _virtuals                                                              \
};                                                                        \
                                                                          \
extern _class _class##_New(_ctor(Parameter));                             \
extern void _class##_Ctor(_class obj, _ctor(Parameter));                  \
extern void _class##_Dtor(Object obj);                                       \
extern void _class##_delete(_class obj);                                  \

#define Declare_Class_Void(_class, _members, _virtuals) \
Declare_Class_Void_Inherits(_class, Object, _members, _virtuals)

#define Declare_Class_Void_Inherits(_class, _base, _members, _virtuals)   \
struct _class##_T                                                         \
{                                                                         \
   struct _base##_T super;                                                \
   _members                                                               \
};                                                                        \
                                                                          \
typedef struct _class##_T * _class;                                       \
                                                                          \
struct _class##_VTable_T                                                  \
{                                                                         \
   struct _base##_VTable_T super;                                         \
   _virtuals                                                              \
};                                                                        \
                                                                          \
extern _class _class##_New(void);                                         \
extern void _class##_Ctor(_class obj);                                    \
extern void _class##_Dtor(Object obj);                                       \
extern void _class##_delete(_class obj);                                  \

#define Define_Class(_class, _ctor)                         \
static struct _class##_VTable_T _class##_VTable_Obj;        \
                                                            \
_class _class##_New(_ctor(Parameter))                       \
{                                                           \
   _class obj = (_class) malloc(sizeof(struct _class##_T)); \
   Isnt_Nullptr(obj, NULL);                                 \
   _class##_Ctor(obj, _ctor(Parameter_val));                \
   return obj;                                              \
}                                                           \
void _class##_delete(_class obj)                            \
{                                                           \
   Acc_Method(Object, obj)->destroy((Object)obj);                 \
   free(obj);                                               \
}                                                           \

/*=====================================================================================* 
 * Exported Function Prototypes
 *=====================================================================================*/
#define Define_Virtual_Void_VTable(_class, _method, _params) \
Define_Virtual_Void_VTable_Inherits(_class, _class, _method, _params)

#define Define_Virtual_VTable(_return, _retval, _class, _method, _params) \
Define_Virtual_VTable_Inherits(_return, _retval, _class, _class, _method, _params)

#define Define_Virtual_Void_VTable_Inherits(_class, _base, _method, _params)  \
void _class##_##_method(_class obj _params(Parameter))                 \
{                                                                      \
	Isnt_Nullptr(obj, );                                                \
   Acc_Method(_base, obj)->_method((_base)obj _params(Parameter_val)); \
}                                                                      \

#define Define_Virtual_VTable_Inherits(_return, _retval, _class, _base, _method, _params) \
_return _class##_##_method(_class obj _params(Parameter))                                 \
{                                                                                         \
   Isnt_Nullptr(obj, _retval);                                                            \
   return (_return)Acc_Method(_base, obj)->_method((_base)obj _params(Parameter_val));    \
}                                                                                         \

/*=====================================================================================* 
 * Exported Function Like Macros
 *=====================================================================================*/
#define Acc_Member(_class, obj) ((_class)obj)
#define Acc_Method(_class, obj) ((struct _class##_VTable_T *)Acc_Member(Object, obj)->vtable)
#define Downcast(_child, obj) (_child##_Dtor == Acc_Method(Object, obj)->destroy)? (_child) obj : NULL
#define Parameter(t, val) t val
#define Parameter_val(t, val) val

#ifdef __cplusplus
}
#endif
/*=====================================================================================* 
 * object.h
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
#endif /*OBJECT_H_*/
