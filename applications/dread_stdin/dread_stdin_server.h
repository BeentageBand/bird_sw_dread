#ifndef DREAD_STDIN_SERVER_H_
#define DREAD_STDIN_SERVER_H_

#include "dispatcher.h"
#include "dread_stdin_handler.h"

#define Dread_Stdin_Server_INHERITS Dispatcher
#define Dread_Stdin_Server_MEMBERS(_member, _class) \
_member(Dread_Stdin_Handler _private, dread_stdin)

#define Dread_Stdin_METHODS(_method, _class)

#define Dread_Stdin_Server_CONSTRUCTORS(_ctor, _class) 

#endif /*DREAD_STDIN_SERVER_H_*/
