#ifndef DREAD_STDIN_H_
#define DREAD_STDIN_H_

#include "object.h"

#define Dread_Stdin_INHERITS BASE_CLASS
#define Dread_Stdin_MEMBERS(_member, _class) 
#define Dread_Stind_METHODS(_method, _class) \
_method(void, _class, on_reading, void const * const, size_t const) \
_method(void, _class, on_connection_established, void) \
_method(void, _class, on_disconnection, void) \

#define Dread_Stdin_CONSTRUCTORS(_ctor, _class) 

#endif /*DREAD_STDIN_H_*/
