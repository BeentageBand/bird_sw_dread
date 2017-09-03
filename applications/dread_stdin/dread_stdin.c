#define OBJECT_IMPLEMENTATION Dread_Stdin

#include "dread_stdin.h"

CLASS_DEF(Dread_Stdin)

void Dread_Stdin_Init(void)
{}

void Dread_Stdin_Delete(struct Object * const obj)
{}

void Dread_Stdin_on_reading(union Dread_Stdin * const this, void const * const data,
size_t const data_size)
{}

void Dread_Stdin_on_connection_established(union Dread_Stdin * const this)
{}

void Dread_Stdin_on_disconnection(union Dread_Stdin * const this)
{}
   
