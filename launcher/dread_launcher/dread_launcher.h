#ifndef DREAD_LAUNCHER_H_
#define DREAD_LAUNCHER_H_

#include "worker.h"

#ifdef __cplusplus
extern "C"{
#endif

extern void Dread_Init(void);
extern union Worker * App_Factory_Method(IPC_TID_T const tid);

#ifdef __cplusplus
}
#endif

#endif /*DREAD_LAUNCHER_H_*/
