#ifndef DREAD_LAUNCHER_H_
#define DREAD_LAUNCHER_H_

#include "worker.h"

extern void Dread_Init(void);
extern union Worker * App_Factory_Method(IPC_TID_T const tid);

#endif /*DREAD_LAUNCHER_H_*/