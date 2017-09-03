#ifndef DREAD_STDIN_PROXY_H_
#define DREAD_STDIN_PROXY_H_

#include "dread_stdin_types.h"
#include "dread_stdin.h"
#include "st_machine.h"

#define Dread_Stdin_Proxy_INHERITS Dread_Stdin
#define Dread_Stdin_Proxy_MEMBERS(_member, _class) \
_member(Dread_Stdin_HSM _private, hsm)
#define Dread_Stdin_METHODS(_method, _class)

#define Dread_Stdin_Proxy_CONSTRUCTORS(_ctor, _class) 

#endif /*DREAD_STDIN_PROXY_H_*/
